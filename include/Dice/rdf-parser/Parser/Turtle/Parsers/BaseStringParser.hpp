#ifndef RDF_PARSER_BASESTRINGPARSER_HPP
#define RDF_PARSER_BASESTRINGPARSER_HPP


#include <chrono>

#include "Dice/rdf-parser/Parser/Turtle/Actions/Actions.hpp"
#include "Dice/rdf-parser/Parser/Turtle/Parsers/AbstractParser.hpp"


/**
 * BaseStringParser is a base class for parsing string sources .
 * It parse the string one time and put the parsed elements in a std::queue
 */

namespace Dice::rdf_parser::Turtle::parsers {

	template<bool sparqlQuery>
	class BaseStringParser : public AbstractParser<BaseStringParser<sparqlQuery>, sparqlQuery> {

		using Triple = Dice::rdf::Triple;
		using TriplePattern = Dice::sparql::TriplePattern;
		using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

	protected:
		/**
         * a queue for storing parsed triples .
         */
		std::shared_ptr<std::queue<Triple_t>> parsedTerms;

	protected:
		/**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param text the string to parse
         */
		explicit BaseStringParser(std::string text) {
			try {
				tao::pegtl::string_input input(std::move(text), "the text");
				States::State<sparqlQuery> state(parsedTerms);
				tao::pegtl::parse<Grammar::grammar<sparqlQuery>, Actions::action>(input, state);

			} catch (std::exception &e) {
				throw e;
			}
		}

		/**
        * The constructor start the parsing.if the input is not valid it will throws and exception.
        * it also invoke nextTriple to have the first triple ready for using .
        * @param text the string to parse
        * @param prefix_map defines prefixes to be added before parsing
        */
		BaseStringParser(std::string text, const std::map<std::string, std::string> &prefix_map) {
			try {
				tao::pegtl::string_input input(text, "the text");
				States::State<sparqlQuery> state(parsedTerms);
				for (auto pair : prefix_map)
					state.addPrefix(pair.first, pair.second);
				tao::pegtl::parse<Grammar::grammar<sparqlQuery>, Actions::action>(input, state);

			} catch (std::exception &e) {
				throw e;
			}
		}

	public:
		[[nodiscard]] bool hasNextTriple() const override {
			return not parsedTerms->empty();
		}

		~BaseStringParser() override = default;

		void nextTriple() override {
			*(this->current_triple) = parsedTerms->front();
			parsedTerms->pop();
		}


		Iterator<BaseStringParser, sparqlQuery> begin_implementation() {
			return Iterator<BaseStringParser, sparqlQuery>(this);
		}
	};
}// namespace Dice::rdf_parser::Turtle::parsers


#endif//RDF_PARSER_BASESTRINGPARSER_HPP
