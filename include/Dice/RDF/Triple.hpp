#ifndef RDF_PARSER_TRIPLE_HPP
#define RDF_PARSER_TRIPLE_HPP

#include "Dice/RDF/Term.hpp"
#include "Dice/RDF/internal/AbstractTriple.hpp"

namespace Dice::rdf {
	/**
	 * An RDF triple
	 */
	class Triple : public internal::AbstractTriple<Term> {

		using super_t = internal::AbstractTriple<Term>;

	public:
		Triple() = default;

		Triple(Term subject, Term predicate, Term object) : super_t{std::move(subject), std::move(predicate), std::move(object)} {}
	};
}// namespace Dice::rdf

#endif//RDF_PARSER_TRIPLE_HPP
