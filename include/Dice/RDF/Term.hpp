#ifndef DICE_RDF_TERM_HPP
#define DICE_RDF_TERM_HPP


#include <exception>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

#include <Dice/hash/DiceHash.hpp>
#include <fmt/format.h>


namespace Dice::rdf {

	/**
     * This is a portable a string view. It is not bound to a single string but applicable to any copy of a string.
     */
	struct unbound_string_view {
		std::ptrdiff_t start = 0;
		std::size_t count = 0;

		/**
         * Get a string_view for the given string.
         * @param str string to be viewed
         * @return string_view on the string
         */
		[[nodiscard]] inline std::string_view string_view(const std::string &str) const noexcept {
			return {str.c_str() + start, count};
		}
	};

	class Literal;

	class BNode;

	class URIRef;

	/**
     * An RDF Term.
     */
	class Term {
	public:
		/**
         * Type of a Term.
         */
		enum NodeType {
			None = 0,
			URIRef_,
			BNode_,
			Literal_

		};

	protected:
		std::string identifier_{};
		NodeType node_type_{};
		unbound_string_view value_{};
		// TODO: we may use std::variant for _lang and _data_type
		unbound_string_view lang_{};
		unbound_string_view data_type_{};

		/**
         * Is to being used by subtypes URIRef, BNode and Literal.
         * @param identifier
         * @param node_type
         */
		Term(std::string identifier, NodeType node_type) noexcept : identifier_(std::move(identifier)),
																	node_type_(node_type) {}

	public:
		Term() = default;

		Term(Term &) = default;

		Term(const Term &) = default;

		Term(Term &&) = default;

		Term &operator=(const Term &) = default;

		Term &operator=(Term &&) = default;


		[[nodiscard]] const std::string &getIdentifier() const noexcept {
			return identifier_;
		}

		[[nodiscard]] inline const NodeType &type() const noexcept {
			return node_type_;
		}

		[[nodiscard]] inline bool isLiteral() const noexcept {
			return node_type_ == NodeType::Literal_;
		}

		[[nodiscard]] inline bool isBNode() const noexcept {
			return node_type_ == NodeType::BNode_;
		}

		[[nodiscard]] inline bool isURIRef() const noexcept {
			return node_type_ == NodeType::URIRef_;
		}

		[[nodiscard]] inline Literal &castLiteral() noexcept;

		[[nodiscard]] inline BNode &castBNode() noexcept;

		[[nodiscard]] inline URIRef &castURIRef() noexcept;

		[[nodiscard]] inline const Literal &castLiteral() const noexcept;

		[[nodiscard]] inline const BNode &castBNode() const noexcept;

		[[nodiscard]] inline const URIRef &castURIRef() const noexcept;

		[[nodiscard]] inline std::string_view value() const noexcept {
			return value_.string_view(identifier_);
		}

		inline bool operator==(Term const &rhs) const noexcept {
			return identifier_ == rhs.identifier_;
		}

		inline auto operator<=>(Term const &rhs) const noexcept {
			return identifier_ <=> rhs.identifier_;
		}

		friend bool operator==(const Term &lhs, const std::unique_ptr<Term> &rhs) noexcept {
			return lhs == *rhs;
		}

		friend bool operator==(const std::unique_ptr<Term> &lhs, Term const &rhs) noexcept {
			return *lhs == rhs;
		}

		friend bool operator==(const std::unique_ptr<Term> &lhs, const std::unique_ptr<Term> &rhs) noexcept {
			return *lhs == *rhs;
		}

		friend bool operator==(const Term *lhs, const std::unique_ptr<Term> &rhs) noexcept {
			return *lhs == *rhs;
		}

		friend bool operator==(const std::unique_ptr<Term> &lhs, const Term *rhs) noexcept {
			return *lhs == *rhs;
		}

		[[nodiscard]] std::size_t hash() const noexcept;
	};


	class URIRef : public Term {

	public:
		explicit URIRef(const std::string &uri) noexcept
			: Term(fmt::format("<{}>", uri), NodeType::URIRef_) {
			this->value_ = {1, uri.size()};
		};

		[[nodiscard]] inline std::string_view uri() const noexcept {
			return value();
		}
	};

	class BNode : public Term {
	public:
		explicit BNode(const std::string &bnode_label) noexcept
			: Term(fmt::format("_:{}", bnode_label), NodeType::BNode_) {
			this->value_ = {2, bnode_label.size()};
		};

		[[nodiscard]] inline std::string_view bnodeLabel() const noexcept {
			return value();
		}
	};

	class Literal : public Term {
	public:
		Literal(const std::string &value, const std::optional<std::string> &lang,
				const std::optional<std::string> &type) noexcept {
			node_type_ = NodeType::Literal_;
			if (lang) {
				this->identifier_ = fmt::format("\"{}\"@{}", value, lang.value());
				this->lang_ = {(std::ptrdiff_t)(1 + value.size() + 1 + 1), lang->size()};
			} else if (type and (type != "http://www.w3.org/2001/XMLSchema#string")) {
				// TODO: handle default cases
				this->identifier_ = fmt::format("\"{}\"^^<{}>", value, type.value());
				this->data_type_ = {(std::ptrdiff_t)(1 + value.size() + 1 + 2 + 1), type->size()};
				// TODO: manage types types
			} else {
				this->identifier_ = fmt::format("\"{}\"", value);
			}
			this->value_ = {1, value.size()};
		}

		[[nodiscard]] inline std::string_view dataType() const noexcept {
			return data_type_.string_view(identifier_);
		}

		[[nodiscard]] inline std::string_view lang() const noexcept {
			return lang_.string_view(identifier_);
		}

		[[nodiscard]] inline bool hasDataType() const noexcept {
			return data_type_.count != 0;
		}

		[[nodiscard]] inline bool hasLang() const noexcept {
			return lang_.count != 0;
		}
	};

	Literal &Term::castLiteral() noexcept {
		return static_cast<Literal &>(*this);
	}

	BNode &Term::castBNode() noexcept {
		return static_cast<BNode &>(*this);
	}

	URIRef &Term::castURIRef() noexcept {
		return static_cast<URIRef &>(*this);
	}

	const Literal &Term::castLiteral() const noexcept {
		return static_cast<const Literal &>(*this);
	}

	const BNode &Term::castBNode() const noexcept {
		return static_cast<const BNode &>(*this);
	}

	const URIRef &Term::castURIRef() const noexcept {
		return static_cast<const URIRef &>(*this);
	}
};// namespace Dice::rdf

namespace Dice::hash {
	template<typename Policy>
	struct dice_hash_overload<Policy, Dice::rdf::Term> {
		static std::size_t dice_hash(Dice::rdf::Term const &v) noexcept {
			return dice_hash_templates<Policy>::dice_hash(v.getIdentifier());
		}
	};
}// namespace Dice::hash

std::size_t Dice::rdf::Term::hash() const noexcept {
	return Dice::hash::DiceHashxxh3<Term>()(*this);
}
template<>
struct std::hash<Dice::rdf::Term> {
	size_t operator()(const Dice::rdf::Term &v) const noexcept {
		return v.hash();
	}
};

template<>
struct fmt::formatter<const Dice::rdf::Term *> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const Dice::rdf::Term *p, FormatContext &ctx) {
		if (p != nullptr)
			return format_to(ctx.out(), p->getIdentifier());
		else
			return format_to(ctx.out(), "");
	}
};

template<>
struct fmt::formatter<Dice::rdf::Term> {
	template<typename ParseContext>
	constexpr auto parse(ParseContext &ctx) { return ctx.begin(); }

	template<typename FormatContext>
	auto format(const Dice::rdf::Term &p, FormatContext &ctx) {
		return format_to(ctx.out(), "{}", p.getIdentifier());
	}
};

#endif//DICE_RDF_TERM_HPP