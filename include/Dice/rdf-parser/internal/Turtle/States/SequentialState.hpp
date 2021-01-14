//
// Created by fakhr on 14.01.21.
//

#ifndef RDF_PARSER_SEQUENTIALSTATE_HPP
#define RDF_PARSER_SEQUENTIALSTATE_HPP


/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/


#include "Dice/rdf-parser/internal/Turtle/States/State.hpp"


namespace Dice::rdf_parser::internal::Turtle::States {

	/*
       * SequentialState deal with the logic of Sequential parsing  (parsed triples cant be accessed until all the file or the string is parsed).
       */
	template<bool sparqlQuery>
	class SequentialState : public State<sparqlQuery, SequentialState<sparqlQuery>> {
		using Term = Dice::rdf::Term;
		using Triple = Dice::rdf::Triple;
		using TriplePattern = Dice::sparql::TriplePattern;
		using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

	private:
		std::shared_ptr<std::queue<Triple_t>> parsed_elements;

	public:
		SequentialState(std::shared_ptr<std::queue<Triple_t>> parsingQueue) : parsed_elements(parsingQueue){};

		inline void syncWithMainThread_impl() {
		}

		inline void insertTriple_impl(Triple_t triple) {
			this->parsed_elements->push(std::move(triple));
		}

		void setParsingIsDone_impl() {
		}
	};
}// namespace Dice::rdf_parser::Turtle::States

#endif//RDF_PARSER_SEQUENTIALSTATE_HPP
