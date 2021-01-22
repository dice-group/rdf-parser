#ifndef RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP

/**
 * CuncurrentStreamParser is responsible for parsing Rdfs from stream sources.
 * It also creates its own thread for parsing.
 * It is also responsible for synchronizing between the parsing thread and the triples queue
 * It parse a file as a stream and put the parsed triples increasingly in a tbb::concurrent_bounded_queue
 * It is the best choice for very large files or stream sources.
 */

#include <exception>
#include <fstream>
#include <iostream>
#include <thread>
#include <utility>

#include "Dice/rdf-parser/exception/RDFParsingExecption.hpp"
#include "Dice/rdf-parser/internal/Turtle/Actions/Actions.hpp"
#include "Dice/rdf-parser/internal/Turtle/Configurations.hpp"
#include "Dice/rdf-parser/internal/Turtle/Parsers/AbstractParser.hpp"
#include "Dice/rdf-parser/internal/Turtle/States/ConcurrentState.hpp"
#include "Dice/rdf-parser/internal/exception//InternalError.hpp"
#include "Dice/rdf-parser/internal/util/ScopedThread.hpp"

namespace Dice::rdf_parser::Turtle::parsers {

	/*
     *
     */
	class TurtleFileParser : public internal::Turtle::Parsers::AbstractParser<TurtleFileParser, false> {
		using Term = Dice::rdf::Term;
		using Triple = Dice::rdf::Triple;

	private:
		// TODO: we don't need the smart pointers for the members

		boost::lockfree::spsc_queue<Triple>
				parsedTerms{internal::Turtle::Configurations::RdfConcurrentStreamParser_QueueCapacity};
		size_t upperThreshold;
		size_t lowerThreshold;

		std::ifstream stream;
		std::condition_variable cv;
		std::mutex m;
		std::condition_variable cv2;
		std::mutex m2;
		std::atomic_bool termCountWithinThresholds;
		std::atomic_bool termsCountIsNotEmpty;
		std::atomic_bool parsingIsDone;
		std::unique_ptr<internal::util::ScopedThread> parsingThread;

	public:
		using Iterator = internal::Turtle::Parsers::Iterator<TurtleFileParser, false>;
		void startParsing(std::string filename, std::size_t bufferSize) {
			namespace Grammar = internal::Turtle::Grammar;
			namespace States = internal::Turtle::States;
			namespace Actions = internal::Turtle::Actions;
			try {

				States::ConcurrentState<false>
						state(parsedTerms,
							  upperThreshold,
							  cv, m,
							  cv2, m2,
							  termCountWithinThresholds,
							  termsCountIsNotEmpty,
							  parsingIsDone);
				tao::pegtl::parse<Grammar::grammar<false>, Actions::action>(
						tao::pegtl::istream_input(stream, bufferSize, filename), std::move(state));
			} catch (std::exception &e) {
				throw exception::RDFParsingException();
			}
		}

		~TurtleFileParser() override {
			stream.close();
		}

		/**
		 *
		 * @param filename name of the file to be parsed
		 * @param queue_capacity maximum number of entries which are cached. When the capacity is reached processing stops.
		 * @param queue_capacity_lower_threshold after queue_capacity was reach, when queue reached this length, processing starts again.
		 */
		explicit TurtleFileParser(const std::string &filename,
								  const size_t queue_capacity = internal::Turtle::Configurations::RdfConcurrentStreamParser_QueueCapacity,
								  const size_t queue_capacity_lower_threshold = internal::Turtle::Configurations::RdfConcurrentStreamParser_QueueCapacity / 10)
			: stream{filename},
			  upperThreshold(queue_capacity),
			  lowerThreshold(queue_capacity_lower_threshold),
			  cv{},
			  m{},
			  cv2{},
			  m2{},
			  termCountWithinThresholds{false},
			  termsCountIsNotEmpty{false},
			  parsingIsDone{false},
			  parsingThread{std::make_unique<internal::util::ScopedThread>(
					  std::thread(&TurtleFileParser::startParsing, this, filename,
								  internal::Turtle::Configurations::RdfConcurrentStreamParser_BufferSize))} {
			if (queue_capacity < queue_capacity_lower_threshold) {
				throw std::logic_error{"queue_capacity_lower_threshold must not be larger than queue_capacity."};
			}
		}


		void nextTriple_impl() {
			parsedTerms.pop(this->current_triple);
			if (parsedTerms.read_available() < lowerThreshold) {
				{
					std::lock_guard<std::mutex> lk(m);
					termCountWithinThresholds = true;
				}
				cv.notify_one();
			}
		}

		bool hasNextTriple_impl() {
			if (parsedTerms.read_available() != 0) {
				return true;
			} else {

				//check if the parsing is done
				if (parsingIsDone) {
					return false;
				} else {
					std::unique_lock<std::mutex> lk(m2);
					termsCountIsNotEmpty = false;
					cv2.wait(lk, [&] { return termsCountIsNotEmpty.load(); });

					if (parsedTerms.read_available() != 0)
						return true;

					else if (parsingIsDone) {
						return false;
					} else {
						throw internal::exception::InternalError();
					}
				}
			};
		};


		internal::Turtle::Parsers::Iterator<TurtleFileParser, false> begin_impl() {
			return internal::Turtle::Parsers::Iterator<TurtleFileParser, false>(this);
		};
	};
}// namespace Dice::rdf_parser::Turtle::parsers

#endif//RDF_PARSER_TURTLEPEGTLCONCURRENTSTREAMPARSER_HPP
