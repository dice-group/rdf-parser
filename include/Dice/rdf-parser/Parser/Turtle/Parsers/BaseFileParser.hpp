#ifndef RDF_PARSER_BASEFILEPARSER_HPP
#define RDF_PARSER_BASEFILEPARSER_HPP


/**
 * FileParser is responsible for parsing triples from file sources.
 * It parse the file one time and put the parsed triples in a std::queue
 */


#include <chrono>
#include <fstream>

#include "Dice/rdf-parser/Parser/Turtle/Actions/Actions.hpp"
#include "Dice/rdf-parser/Parser/Turtle/Parsers/AbstractParser.hpp"

namespace Dice::rdf_parser::Turtle::parsers {

	template<bool sparqlQuery>
	class BaseFileParser : public AbstractParser<BaseFileParser<sparqlQuery>, sparqlQuery> {
		using Term = Dice::rdf::Term;
		using URIRef = Dice::rdf::URIRef;
		using Literal = Dice::rdf::Literal;
		using BNode = Dice::rdf::BNode;
		using Variable = Dice::sparql::Variable;
		using VarOrTerm = Dice::sparql::VarOrTerm;
		using Triple = Dice::rdf::Triple;
		using TriplePattern = Dice::sparql::TriplePattern;
		using Element_t = std::conditional_t<sparqlQuery, VarOrTerm, Term>;
		using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;
	private:
		/**
         * a queue for storing parsed triples .
         */
		std::shared_ptr<std::queue<Triple_t>> parsedTerms;

	protected:
		/**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param filename the filename of the file we want to parse
         */
		explicit BaseFileParser(const std::string& filename) {
			try {
				std::ifstream infile(filename);
				tao::pegtl::read_input file(filename);
				States::State<> state(parsedTerms);
				tao::pegtl::parse<Grammar::grammar<false>, Actions::action>(std::move(file), std::move(state));

			} catch (std::exception &e) {
				throw e;
			}
		}

		/**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param filename the filename of the file we want to parse
         */
		BaseFileParser(std::string filename, const std::map<std::string, std::string>& prefix_map) {
			try {
				std::ifstream infile(filename);
				tao::pegtl::read_input file(filename);
				States::State<sparqlQuery> state(parsedTerms);
				for (auto pair : prefix_map)
					state.addPrefix(pair.first, pair.second);
				tao::pegtl::parse<Grammar::grammar<sparqlQuery>, Actions::action>(std::move(filename), std::move(state));

			} catch (std::exception &e) {
				throw e;
			}
		}

	public:
		~BaseFileParser() override {
			//           The constructors that take a FILE* argument take ownership of the file pointer, i.e. they fclose() it in the destructor.Therfore, no need to close the file in this destructor
			//           see https://github.com/taocpp/PEGTL/blob/master/doc/Inputs-and-Parsing.md#file-input
		}

		bool hasNextTriple() const override {
			return not parsedTerms->empty();
		}

		void nextTriple() override {
			*(this->current_triple) = parsedTerms->front();
			parsedTerms->pop();
		}


		Iterator<BaseFileParser<sparqlQuery>, sparqlQuery> begin_implementation() {
			return Iterator<BaseFileParser<sparqlQuery>, sparqlQuery>(this);
		}
	};
}// namespace Dice::rdf_parser::Turtle::parsers


#endif//RDF_PARSER_BASEFILEPARSER_HPP
