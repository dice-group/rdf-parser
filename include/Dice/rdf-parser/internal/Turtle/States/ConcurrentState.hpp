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
#include <utility>

#include <boost/lockfree/spsc_queue.hpp>

#include "Dice/rdf-parser/internal/Turtle/Configurations.hpp"
#include "Dice/rdf-parser/internal/Turtle/States/State.hpp"

namespace Dice::rdf_parser::internal::Turtle::States {

	/*
     * ConcurrentState deal with the logic of Concurrent parsing  (already parsed triples can be accessed during the parsing).
     */
	template<bool sparqlQuery>
	class ConcurrentState : public State<sparqlQuery, ConcurrentState<sparqlQuery>> {

		using Term = Dice::rdf::Term;
		using Triple = Dice::rdf::Triple;
		using TriplePattern = Dice::sparql::TriplePattern;
		using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

	private:
		//Defines  threshold for triples in the Queue(should be assigned by the constructor)
		size_t upperThreshold;
		std::condition_variable &cv;
		std::mutex &m;
		std::condition_variable &cv2;
		std::mutex &m2;
		std::atomic_bool &termCountWithinThresholds;
		std::atomic_bool &termsCountIsNotEmpty;
		std::atomic_bool &parsingIsDone;

		boost::lockfree::spsc_queue<Triple_t> &parsed_elements;

	public:
		explicit ConcurrentState(
				boost::lockfree::spsc_queue<Triple_t> &parsingQueue,
				size_t upperThreshold,
				std::condition_variable &cv, std::mutex &m,
				std::condition_variable &cv2, std::mutex &m2,
				std::atomic_bool &termCountWithinThresholds,
				std::atomic_bool &termsCountIsNotEmpty,
				std::atomic_bool &parsingIsDone)
			: parsed_elements(parsingQueue),
			  upperThreshold(upperThreshold),
			  cv(cv), m(m),
			  cv2(cv2), m2(m2),
			  termCountWithinThresholds(termCountWithinThresholds),
			  termsCountIsNotEmpty(termsCountIsNotEmpty),
			  parsingIsDone(parsingIsDone) {}

		inline void syncWithMainThread_impl() {
			if (this->parsed_elements.read_available() > upperThreshold) {
				std::unique_lock<std::mutex> lk(m);
				termCountWithinThresholds = false;
				//set the parsing thread to sleep
				cv.wait(lk, [&] { return termCountWithinThresholds.load(); });
				//the parsing thread wake from sleeping
			}
		}

		inline void insertTriple_impl(Triple_t triple) {
			if (not termsCountIsNotEmpty) {
				{
					std::lock_guard<std::mutex> lk(m2);
					termsCountIsNotEmpty = true;
				}
				this->parsed_elements.push(std::move(triple));
				cv2.notify_one();
			} else {
				this->parsed_elements.push(std::move(triple));
			}
		}


		void setParsingIsDone_impl() {
			if (not termsCountIsNotEmpty) {
				{
					std::lock_guard<std::mutex> lk(m2);
					termsCountIsNotEmpty = true;
				}
				cv2.notify_one();
			}
			parsingIsDone = true;
		}
	};

}// namespace Dice::rdf_parser::internal::Turtle::States
#endif//RDF_PARSER_CONCURRENTSTATE_HPP
