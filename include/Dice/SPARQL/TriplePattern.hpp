#ifndef RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP
#define RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP

#include <variant>

#include "Dice/RDF/Term.hpp"
#include "Dice/RDF/internal/AbstractTriple.hpp"
#include "Dice/SPARQL/Variable.hpp"

namespace Dice::sparql {
	using VarOrTerm = std::variant<Variable, Dice::rdf::Term>;
}// namespace Dice::sparql

namespace Dice::sparql {
	class TriplePattern : public ::Dice::rdf::internal::AbstractTriple<VarOrTerm, TriplePattern> {

		using super_t = ::Dice::rdf::internal::AbstractTriple<VarOrTerm, TriplePattern>;

	public:
		TriplePattern() = default;

		TriplePattern(VarOrTerm subject, VarOrTerm predicate, VarOrTerm object) noexcept
			: super_t{std::move(subject), std::move(predicate), std::move(object)} {}

		[[nodiscard]] size_t hash() const noexcept;

		[[nodiscard]] constexpr size_t size() const noexcept { return 3; }
	};
}// namespace Dice::sparql

template<>
struct Dice::hash::is_ordered_container<Dice::sparql::TriplePattern> : std::true_type {};


std::size_t Dice::sparql::TriplePattern::hash() const noexcept {
	return Dice::hash::DiceHashxxh3<TriplePattern>()(*this);
}
template<>
struct std::hash<Dice::sparql::TriplePattern> {
	size_t operator()(const Dice::sparql::TriplePattern &v) const noexcept {
		return v.hash();
	}
};

template<>
struct fmt::formatter<Dice::sparql::VarOrTerm> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const Dice::sparql::VarOrTerm &p, FormatContext &ctx) {
		if (std::holds_alternative<Dice::sparql::Variable>(p))
			return format_to(ctx.out(), "{}", std::get<Dice::sparql::Variable>(p));
		else
			return format_to(ctx.out(), "{}", std::get<Dice::rdf::Term>(p));
	}
};

template<>
struct fmt::formatter<Dice::sparql::TriplePattern> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const Dice::sparql::TriplePattern &p, FormatContext &ctx) {
		return format_to(ctx.out(), "({})", fmt::join(p, ", "));
	}
};
#endif//RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP
