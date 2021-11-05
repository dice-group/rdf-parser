#ifndef RDF_PARSER_SPARQL_TRIPLEVARIABLE_HPP
#define RDF_PARSER_SPARQL_TRIPLEVARIABLE_HPP

#include <string>
#include <utility>

#include <Dice/hash/DiceHash.hpp>
#include <fmt/format.h>

namespace Dice::sparql {
	class Variable {
	private:
		std::string name_;
		bool is_anonym_ = false;

	public:
		Variable() = default;
		explicit Variable(std::string var_name, bool anonym = false) noexcept
			: name_{std::move(var_name)},
			  is_anonym_{anonym} {}

		inline bool operator==(const Variable &rhs) const noexcept {
			return name_ == rhs.name_;
		}

		inline auto operator<=>(const Variable &rhs) const noexcept {
			return name_ <=> rhs.name_;
		}

		inline void setName(std::string name) noexcept {
			this->name_ = std::move(name);
		}

		[[nodiscard]] const std::string &getName() const noexcept {
			return name_;
		}

		inline void setIs_anonym(bool is_anonym) noexcept {
			this->is_anonym_ = is_anonym;
		}

		[[nodiscard]] bool isAnon() const noexcept {
			return is_anonym_;
		}

		[[nodiscard]] std::size_t hash() const noexcept;
	};
}// namespace Dice::sparql

namespace Dice::hash {
	template<typename Policy>
	struct dice_hash_overload<Policy, Dice::sparql::Variable> {
		static std::size_t dice_hash(Dice::sparql::Variable const &v) noexcept {
			return dice_hash_templates<Policy>::dice_hash(std::make_tuple(v.getName(), v.isAnon()));
		}
	};
}// namespace Dice::hash

std::size_t Dice::sparql::Variable::hash() const noexcept {
	return Dice::hash::DiceHashxxh3<Variable>()(*this);
}
template<>
struct std::hash<Dice::sparql::Variable> {
	size_t operator()(const Dice::sparql::Variable &v) const {
		return v.hash();
	}
};

template<>
struct fmt::formatter<Dice::sparql::Variable> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const Dice::sparql::Variable &p, FormatContext &ctx) {
		if (p.isAnon()) {
			return format_to(ctx.out(), "_:{}", p.getName());
		} else {
			return format_to(ctx.out(), "?{}", p.getName());
		}
	}
};
#endif//RDF_PARSER_SPARQL_TRIPLEVARIABLE_HPP
