#ifndef RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP

/**
 * CuncurrentStreamParser is responsible for parsing Rdfs from stream sources.
 * It also creates its own thread for parsing.
 * It is also responsible for synchronizing between the parsing thread and the triples queue
 * It parse a file as a stream and put the parsed triples increasingly in a tbb::concurrent_bounded_queue
 * It is the best choice for very large files or stream sources.
 */

#include <fstream>
#include <thread>
#include <utility>
#include <iostream>
#include <exception>

#include "AbstractParser.hpp"
#include "Dice/rdf-parser/util/scoped_thread.hpp"
#include "Dice/rdf-parser/Parser/Turtle/Actions/Actions.hpp"
#include "Dice/rdf-parser/Parser/Turtle/States/ConcurrentState.hpp"

#include "../Configurations.hpp"
namespace {
    using namespace tao::pegtl;
}

namespace rdf_parser::Turtle::parsers {

    /*
     *
     */
    class RdfConcurrentStreamParser : public AbstractParser<RdfConcurrentStreamParser,false> {

    private:
        std::shared_ptr<boost::lockfree::spsc_queue<Triple,boost::lockfree::capacity<Configurations::RdfConcurrentStreamParser_QueueCapacity>>> parsedTerms;
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

                States::ConcurrentState<false,boost::lockfree::spsc_queue<Triple,boost::lockfree::capacity<Configurations::RdfConcurrentStreamParser_QueueCapacity>>> state(parsedTerms,
                                                                                   upperThrehold, cv,
                                                                                   m, cv2, m2,
                                                                                   termCountWithinThreholds,
                                                                                   termsCountIsNotEmpty,
                                                                                   parsingIsDone);
                parse<Grammer::grammer<false>, Actions::action>(istream_input(stream, bufferSize, filename), state);
            }
            catch (std::exception &e) {
                throw std::exception(e);
            }
        }

        ~RdfConcurrentStreamParser() override {
            stream.close();
        }


        RdfConcurrentStreamParser(std::string filename) :
                stream{filename},
                upperThrehold(Configurations::RdfConcurrentStreamParser_QueueCapacity),
                lowerThrehold(Configurations::RdfConcurrentStreamParser_QueueCapacity / 10),
                parsedTerms{std::make_shared<boost::lockfree::spsc_queue<Triple,boost::lockfree::capacity<Configurations::RdfConcurrentStreamParser_QueueCapacity>>>()},
                cv{std::make_shared<std::condition_variable>()},
                m{std::make_shared<std::mutex>()},
                cv2{std::make_shared<std::condition_variable>()},
                m2{std::make_shared<std::mutex>()},
                termCountWithinThreholds{std::make_shared<std::atomic_bool>(false)},
                termsCountIsNotEmpty{std::make_shared<std::atomic_bool>(false)},
                parsingIsDone{std::make_shared<std::atomic_bool>(false)} {
            parsingThread = std::make_unique<util::ScopedThread>(
                    std::thread(&RdfConcurrentStreamParser::startParsing, this, filename, Configurations::RdfConcurrentStreamParser_BufferSize));

        }


        void nextTriple() override {
            parsedTerms->pop(*(this->current_triple));
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


        Iterator<RdfConcurrentStreamParser,false> begin_implementation(){
            return Iterator<RdfConcurrentStreamParser,false>(this);
        }
    };
}


#endif //RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP
