#ifndef RDF_PARSER_SPARQL_TRIPLEVARIABLE_HPP
#define RDF_PARSER_SPARQL_TRIPLEVARIABLE_HPP

#include <utility>
#include <string>

namespace Dice::sparql {
	class Variable {
	private:
		std::string name_;
		bool is_anonym_ = false;

	public:
		Variable() = default;
		explicit Variable(std::string var_name, bool anonym = false) : name_{std::move(var_name)},
																	   is_anonym_{anonym} {}

		inline bool operator==(const Variable &rhs) const {
			return name_ == rhs.name_;
		}

		inline bool operator!=(const Variable &rhs) const {
			return name_ != rhs.name_;
		}

		inline bool operator<(const Variable &rhs) const {
			return name_ < rhs.name_;
		}

		inline bool operator>(const Variable &rhs) const {
			return name_ > rhs.name_;
		}

		inline void setName(std::string name) {
			this->name_ = std::move(name);
		}

		[[nodiscard]] const std::string &getName() const {
			return name_;
		}

		inline void setIs_anonym(bool is_anonym) {
			this->is_anonym_ = is_anonym;
		}

		[[nodiscard]] bool isAnon() const {
			return is_anonym_;
		}
	};
}// namespace Dice::sparql
#endif//RDF_PARSER_SPARQL_TRIPLEVARIABLE_HPP
