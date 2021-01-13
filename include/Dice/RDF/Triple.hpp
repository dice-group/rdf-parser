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
	class Triple : public internal::AbstractTriple<Term> {

		using super_t = internal::AbstractTriple<Term>;

	public:
		Triple() = default;

		Triple(Term subject, Term predicate, Term object) : super_t{std::move(subject), std::move(predicate), std::move(object)} {}
		[[nodiscard]] size_t hash() const noexcept {
			return ::Dice::hash::dice_hash(this->entries_);
		}
	};
}// namespace Dice::rdf

namespace Dice::hash {
	template<>
	inline std::size_t dice_hash(const Dice::rdf::Triple &v) noexcept {
		return v.hash();
	}
}// namespace Dice::hash

template<>
struct std::hash<Dice::rdf::Triple> {
	inline size_t operator()(const Dice::rdf::Triple &v) const {
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
