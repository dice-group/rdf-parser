//
// Created by fakhr on 29.04.20.
//

#ifndef RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP
#define RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP

#include <variant>

#include "TripleVariable.hpp"
#include <Dice/rdf-parser/RDF/Term.hpp>

namespace rdf_parser::SparqlQuery {
	using VarOrTerm = std::variant<TripleVariable, rdf_parser::store::rdf::Term>;
	class TriplePatternElement {
	private:
		std::array<VarOrTerm, 3> triplePattern;

	public:
		TriplePatternElement(){};
		explicit TriplePatternElement(VarOrTerm element1, VarOrTerm element2, VarOrTerm element3) : triplePattern{
																											element1, element2, element3} {};


		VarOrTerm subject() { return triplePattern.at(0); };

		VarOrTerm predicate() { return triplePattern.at(1); };

		VarOrTerm object() { return triplePattern.at(2); };

		void setSubject(VarOrTerm subject) { triplePattern.at(0) = subject; };

		void setPredicate(VarOrTerm predicate) { triplePattern.at(1) = predicate; };

		void setObject(VarOrTerm object) { triplePattern.at(2) = object; };
	};
}// namespace rdf_parser::SparqlQuery
#endif//RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP
