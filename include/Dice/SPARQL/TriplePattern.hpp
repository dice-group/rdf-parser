#ifndef RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP
#define RDF_PARSER_SPARQL_TRIPLEPATTERNELEMENT_HPP

#include <variant>

#include "Dice/RDF/Term.hpp"
#include "Dice/RDF/internal/AbstractTriple.hpp"
#include "Dice/SPARQL/Variable.hpp"

namespace Dice::sparql {
	using VarOrTerm = std::variant<Variable, Dice::rdf::Term>;
}// namespace Dice::sparql

namespace Dice::hash {
	template<>
	inline std::size_t dice_hash(const Dice::sparql::VarOrTerm &v) noexcept {
		if (std::holds_alternative<Dice::sparql::Variable>(v))
			return dice_hash(std::get<Dice::sparql::Variable>(v));
		else
			return dice_hash(std::get<Dice::rdf::Term>(v));
	}
}// namespace Dice::hash

namespace Dice::sparql {
	class TriplePattern : public ::Dice::rdf::internal::AbstractTriple<VarOrTerm, TriplePattern> {

		using super_t = ::Dice::rdf::internal::AbstractTriple<VarOrTerm, TriplePattern>;

	public:
		TriplePattern() = default;

		TriplePattern(VarOrTerm subject, VarOrTerm predicate, VarOrTerm object) : super_t{std::move(subject), std::move(predicate), std::move(object)} {}


		[[nodiscard]] size_t hash() const noexcept {
			return ::Dice::hash::dice_hash(this->entries_);
		}

	};
}// namespace Dice::sparql

namespace Dice::hash {
	template<>
	inline std::size_t dice_hash(const Dice::sparql::TriplePattern &v) noexcept {
		return v.hash();
	}
}// namespace Dice::hash

template<>
struct std::hash<Dice::sparql::TriplePattern> {
	inline size_t operator()(const Dice::sparql::TriplePattern &v) const {
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
