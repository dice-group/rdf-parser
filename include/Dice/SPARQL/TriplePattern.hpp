#ifndef RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP
#define RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP

#include <variant>

#include "Dice/RDF/Term.hpp"
#include "Dice/RDF/internal/AbstractTriple.hpp"
#include "Dice/SPARQL/Variable.hpp"

namespace Dice::sparql {
	using VarOrTerm = std::variant<Variable, Dice::rdf::Term>;
	class TriplePattern : public ::Dice::rdf::internal::AbstractTriple<VarOrTerm> {

		using super_t = ::Dice::rdf::internal::AbstractTriple<VarOrTerm>;

	public:
		TriplePattern() = default;

		TriplePattern(VarOrTerm subject, VarOrTerm predicate, VarOrTerm object) : super_t{std::move(subject), std::move(predicate), std::move(object)} {}
	};
}// namespace Dice::sparql
#endif//RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP
