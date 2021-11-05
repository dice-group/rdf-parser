#ifndef RDF_PARSER_TRIPLE_HPP
#define RDF_PARSER_TRIPLE_HPP

#include <Dice/hash/DiceHash.hpp>
#include <fmt/format.h>

#include "Dice/RDF/Term.hpp"
#include "Dice/RDF/internal/AbstractTriple.hpp"

namespace Dice::rdf {
	/**
	 * An RDF triple
	 */
	class Triple : public internal::AbstractTriple<Term, Triple> {

		using super_t = internal::AbstractTriple<Term, Triple>;

	public:
		Triple() = default;

		Triple(Term subject, Term predicate, Term object) noexcept
			: super_t{std::move(subject), std::move(predicate), std::move(object)} {}
		[[nodiscard]] size_t hash() const noexcept;

		[[nodiscard]] constexpr size_t size() const noexcept { return 3; }
	};
}// namespace Dice::rdf

template<>
struct Dice::hash::is_ordered_container<Dice::rdf::Triple> : std::true_type {};


std::size_t Dice::rdf::Triple::hash() const noexcept {
	return Dice::hash::DiceHashxxh3<Triple>()(*this);
}
template<>
struct std::hash<Dice::rdf::Triple> {
	size_t operator()(const Dice::rdf::Triple &v) const noexcept {
		return v.hash();
	}
};

template<>
struct fmt::formatter<Dice::rdf::Triple> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const Dice::rdf::Triple &p, FormatContext &ctx) {
		return format_to(ctx.out(), "({})", fmt::join(p, ", "));
	}
};

#endif//RDF_PARSER_TRIPLE_HPP
