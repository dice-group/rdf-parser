#ifndef RDF_PARSER_CONCURRENTSTATE_HPP
#define RDF_PARSER_CONCURRENTSTATE_HPP

/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/

#include <atomic>
#include <boost/lockfree/spsc_queue.hpp>
#include <condition_variable>
#include <mutex>
#include <thread>

#include "State.hpp"

namespace rdf_parser::Turtle {
	namespace States {

		/*
         * ConcurrentState defines the data structures realted to the whole grammer (stores the parsed triples)
         * in a cunncurent data structure (intel concureent queue)
         */
		template<bool sparqlQuery, typename T = boost::lockfree::spsc_queue<std::conditional_t<sparqlQuery, SparqlQuery::VarOrTerm, Term>>>
		class ConcurrentState : public State<sparqlQuery, T> {

		private:
			//Defines  threhold for triples in the Queue(should be assigned by the constructor)
			unsigned int upperThrehold;
			std::shared_ptr<std::condition_variable> cv;
			std::shared_ptr<std::mutex> m;
			std::shared_ptr<std::atomic_bool> termCountWithinThreholds;
			std::shared_ptr<std::atomic_bool> termsCountIsNotEmpty;
			std::shared_ptr<std::atomic_bool> parsingIsDone;

			std::shared_ptr<std::condition_variable> cv2;
			std::shared_ptr<std::mutex> m2;

		public:
			explicit ConcurrentState(std::shared_ptr<T> &parsingQueue, unsigned int upperThrehold,
									 std::shared_ptr<std::condition_variable> cv, std::shared_ptr<std::mutex> m,
									 std::shared_ptr<std::condition_variable> cv2, std::shared_ptr<std::mutex> m2,
									 std::shared_ptr<std::atomic_bool> termCountWithinThreholds,
									 std::shared_ptr<std::atomic_bool> termsCountIsNotEmpty,
									 std::shared_ptr<std::atomic_bool> parsingIsDone)
				: State<sparqlQuery, T>(parsingQueue) {
				this->upperThrehold = upperThrehold;
				this->cv = cv;
				this->m = m;
				this->cv2 = cv2;
				this->m2 = m2;
				this->termCountWithinThreholds = termCountWithinThreholds;
				this->termsCountIsNotEmpty = termsCountIsNotEmpty;
				this->parsingIsDone = parsingIsDone;
			}

			inline void syncWithMainThread() override {
				if (this->parsed_elements->read_available() > upperThrehold) {
					std::unique_lock<std::mutex> lk(*m);
					*termCountWithinThreholds = false;
					//set the parsing thread to sleep
					cv->wait(lk, [&] { return termCountWithinThreholds->load(); });
					//the parsing thread wake from sleeping
				}
			}

			inline void insertTriple(std::conditional_t<sparqlQuery, SparqlQuery::TriplePatternElement, Triple> triple) override {
				if (*termsCountIsNotEmpty == false) {
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


			void setPasrsingIsDone() override {
				if (*termsCountIsNotEmpty == false) {
					{
						std::lock_guard<std::mutex> lk(*m2);
						*termsCountIsNotEmpty = true;
					}
					cv2->notify_one();
				}
				*parsingIsDone = true;
			}
		};

	}// namespace States
}// namespace rdf_parser::Turtle
#endif//RDF_PARSER_CONCURRENTSTATE_HPP
