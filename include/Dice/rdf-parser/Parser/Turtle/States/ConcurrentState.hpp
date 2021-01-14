#ifndef RDF_PARSER_CONCURRENTSTATE_HPP
#define RDF_PARSER_CONCURRENTSTATE_HPP

/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <boost/lockfree/spsc_queue.hpp>
#include <utility>

#include "Dice/rdf-parser/Parser/Turtle/States/State.hpp"
#include "Dice/rdf-parser/Parser/Turtle/Configurations.hpp"

namespace Dice::rdf_parser::Turtle::States {

    /*
     * ConcurrentState deal with the logic of Concurrent parsing  (already parsed triples can be accessed during the parsing). It is a base class for SequentialState and ConcurrentState
     */
    template<bool sparqlQuery>
    class ConcurrentState : public State<sparqlQuery> {

        using Term = Dice::rdf::Term;
        using VarOrTerm = Dice::sparql::VarOrTerm;
        using Triple = Dice::rdf::Triple;
        using TriplePattern = Dice::sparql::TriplePattern;
        using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

    private:
        //Defines  threshold for triples in the Queue(should be assigned by the constructor)
        unsigned int upperThreshold;
        std::shared_ptr<std::condition_variable> cv;
        std::shared_ptr<std::mutex> m;
        std::shared_ptr<std::condition_variable> cv2;
        std::shared_ptr<std::mutex> m2;
        std::shared_ptr<std::atomic_bool> termCountWithinThresholds;
        std::shared_ptr<std::atomic_bool> termsCountIsNotEmpty;
        std::shared_ptr<std::atomic_bool> parsingIsDone;

        std::shared_ptr<boost::lockfree::spsc_queue<Triple_t, boost::lockfree::capacity<Configurations::RdfConcurrentStreamParser_QueueCapacity>>> parsed_elements;

    public:
        explicit ConcurrentState(
                std::shared_ptr<boost::lockfree::spsc_queue<Triple_t, boost::lockfree::capacity<Configurations::RdfConcurrentStreamParser_QueueCapacity>>> parsingQueue,
                unsigned int upperThreshold,
                std::shared_ptr<std::condition_variable> cv, std::shared_ptr<std::mutex> m,
                std::shared_ptr<std::condition_variable> cv2, std::shared_ptr<std::mutex> m2,
                std::shared_ptr<std::atomic_bool> termCountWithinThresholds,
                std::shared_ptr<std::atomic_bool> termsCountIsNotEmpty,
                std::shared_ptr<std::atomic_bool> parsingIsDone)
                :
                parsed_elements(parsingQueue),
                upperThreshold(upperThreshold),
                cv(std::move(cv)), m(std::move(m)),
                cv2(std::move(cv2)), m2(std::move(m2)),
                termCountWithinThresholds(std::move(termCountWithinThresholds)),
                termsCountIsNotEmpty(std::move(termsCountIsNotEmpty)),
                parsingIsDone(std::move(parsingIsDone)) {}

        inline void syncWithMainThread() override {
            if (this->parsed_elements->read_available() > upperThreshold) {
                std::unique_lock<std::mutex> lk(*m);
                *termCountWithinThresholds = false;
                //set the parsing thread to sleep
                cv->wait(lk, [&] { return termCountWithinThresholds->load(); });
                //the parsing thread wake from sleeping
            }
        }

        inline void insertTriple(Triple_t triple) override {
            if (not*termsCountIsNotEmpty) {
                {
                    std::lock_guard<std::mutex> lk(*m2);
                    *termsCountIsNotEmpty = true;
                }
                this->parsed_elements->push(std::move(triple));
                cv2->notify_one();
            } else {
                this->parsed_elements->push(std::move(triple));
            }
        }


        void setParsingIsDone() override {
            if (not*termsCountIsNotEmpty) {
                {
                    std::lock_guard<std::mutex> lk(*m2);
                    *termsCountIsNotEmpty = true;
                }
                cv2->notify_one();
            }
            *parsingIsDone = true;
        }
    };

}// namespace Dice::rdf_parser::Turtle::States
#endif//RDF_PARSER_CONCURRENTSTATE_HPP
