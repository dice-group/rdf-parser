#ifndef RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP

/**
 * CuncurrentStreamParser is responsible for parsing triples from stream sources.
 * It also creates its own thread for parsing.
 * It is also responsible for synchronizing between the parsing thread and the triples queue
 * It parse a file as a stream and put the parsed triples increasingly in a tbb::concurrent_bounded_queue
 * It is the best choice for very large files or stream sources.
 */

#include <fstream>
#include <thread>
#include <utility>
#include <iostream>

#include "TriplesParser.hpp"
#include "Dice/rdf_parser/util/scoped_thread.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Actions/Actions.hpp"
#include "Dice/rdf_parser/Parser/Turtle/States/ConcurrentState.hpp"

namespace {
    using namespace tao::pegtl;
}

namespace rdf_parser::Turtle {

    /*
     *
     */
    class CuncurrentStreamParser : public TriplesParser {

    private:
        std::shared_ptr<boost::lockfree::spsc_queue<Triple,boost::lockfree::capacity<100000>>> parsedTerms;
        unsigned int upperThrehold;
        unsigned int lowerThrehold;

        std::ifstream stream;
        std::unique_ptr<util::ScopedThread> parsingThread;
        std::shared_ptr<std::condition_variable> cv;
        std::shared_ptr<std::mutex> m;
        std::shared_ptr<std::condition_variable> cv2;
        std::shared_ptr<std::mutex> m2;
        std::shared_ptr<std::atomic_bool> termCountWithinThreholds;
        std::shared_ptr<std::atomic_bool> termsCountIsNotEmpty;
        std::shared_ptr<std::atomic_bool> parsingIsDone;

    public:

        void startParsing(std::string filename, std::size_t bufferSize) {
            try {

                States::ConcurrentState<false,boost::lockfree::spsc_queue<Triple,boost::lockfree::capacity<100000>>> state(parsedTerms,
                                                                                   upperThrehold, cv,
                                                                                   m, cv2, m2,
                                                                                   termCountWithinThreholds,
                                                                                   termsCountIsNotEmpty,
                                                                                   parsingIsDone);
                parse<Grammer::grammer<>, Actions::action>(istream_input(stream, bufferSize, filename), state);
            }
            catch (std::exception &e) {
                throw e;
            }
        }

        ~CuncurrentStreamParser() override {
            stream.close();
        }


        CuncurrentStreamParser(std::string filename, std::size_t bufferSize = 1024 * 1024,
                               unsigned int queueCapacity = 100000) :
                stream{filename},
                upperThrehold(queueCapacity),
                lowerThrehold(queueCapacity / 10),
                parsedTerms{std::make_shared<boost::lockfree::spsc_queue<Triple,boost::lockfree::capacity<100000>>>()},
                cv{std::make_shared<std::condition_variable>()},
                m{std::make_shared<std::mutex>()},
                cv2{std::make_shared<std::condition_variable>()},
                m2{std::make_shared<std::mutex>()},
                termCountWithinThreholds{std::make_shared<std::atomic_bool>(false)},
                termsCountIsNotEmpty{std::make_shared<std::atomic_bool>(false)},
                parsingIsDone{std::make_shared<std::atomic_bool>(false)} {
            parsingThread = std::make_unique<util::ScopedThread>(
                    std::thread(&CuncurrentStreamParser::startParsing, this, filename, bufferSize));

        }


        void nextTriple() override {
            parsedTerms->pop(current_triple);
            if (parsedTerms->read_available() < lowerThrehold) {
                {
                    std::lock_guard<std::mutex> lk(*m);
                    *termCountWithinThreholds = true;
                }
                cv->notify_one();
            }

        }

        bool hasNextTriple() const override {
            if (parsedTerms->read_available() != 0) {
                return true;
            } else {

                //check if the parsing is done
                if (*parsingIsDone) {
                    std::cout << "from main thread : parsingIsDone " << std::endl;
                    return false;
                } else {
                    std::unique_lock<std::mutex> lk(*m2);
                    *termsCountIsNotEmpty = false;
                    cv2->wait(lk, [&] { return termsCountIsNotEmpty->load(); });

                    if (parsedTerms->read_available() != 0)
                        return true;

                    else if (*parsingIsDone) {
                        std::cout << "from main thread : parsingIsDone " << std::endl;
                        return false;
                    } else {
                        throw std::runtime_error("");
                    }

                }

            };
        };
    };
}


#endif //RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP
