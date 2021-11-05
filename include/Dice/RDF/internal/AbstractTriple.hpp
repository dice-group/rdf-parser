#ifndef RDF_PARSER_ABSTRACT_TRIPLE_HPP
#define RDF_PARSER_ABSTRACT_TRIPLE_HPP

#include <Dice/hash/DiceHash.hpp>

namespace Dice::rdf::internal {

	template<typename Element, typename Derived>
	class AbstractTriple {
	protected:
		typedef std::array<Element, 3> Triple_t;
		Triple_t entries_{};

	public:
		typedef typename Triple_t::iterator iterator;
		typedef typename Triple_t::const_iterator const_iterator;
		typedef typename Triple_t::reverse_iterator reverse_iterator;
		typedef typename Triple_t::const_reverse_iterator const_reverse_iterator;

		AbstractTriple() = default;

		AbstractTriple(Element subject, Element predicate, Element object) noexcept
			: entries_{subject, predicate, object} {}

		[[nodiscard]] const Element &subject() const noexcept { return entries_[0]; }

		[[nodiscard]] Element &subject() noexcept { return entries_[0]; }

		[[nodiscard]] const Element &predicate() const noexcept { return entries_[1]; }

		[[nodiscard]] Element &predicate() noexcept { return entries_[1]; }

		[[nodiscard]] const Element &object() const noexcept { return entries_[2]; }

		[[nodiscard]] Element &object() noexcept { return entries_[2]; }

		Element &operator[](std::size_t pos) noexcept { return entries_[pos]; }

		const Element &operator[](std::size_t pos) const noexcept { return entries_[pos]; }


		void setSubject(Element subject) noexcept { entries_[0] = std::move(subject); }

		void setPredicate(Element predicate) noexcept { entries_[1] = std::move(predicate); }

		void setObject(Element object) noexcept { entries_[2] = std::move(object); }

		iterator begin() noexcept { return entries_.begin(); }
		const_iterator begin() const noexcept { return entries_.begin(); }
		iterator end() noexcept { return entries_.end(); }
		const_iterator end() const noexcept { return entries_.end(); }
		iterator rbegin() noexcept { return entries_.rbegin(); }
		const_iterator rbegin() const noexcept { return entries_.rbegin(); }
		reverse_iterator rend() noexcept { return entries_.rend(); }
		const_reverse_iterator rend() const noexcept { return entries_.rend(); }

		friend bool operator==(const Derived &triple1, const Derived &triple2) {
			return std::tie(triple1.subject(), triple1.predicate(), triple1.object()) ==
				   std::tie(triple2.subject(), triple2.predicate(), triple2.object());
		}

		friend auto operator<=>(const Derived &triple1, const Derived &triple2) {
			return std::tie(triple1.subject(), triple1.predicate(), triple1.object()) <=>
				   std::tie(triple2.subject(), triple2.predicate(), triple2.object());
		}
	};

}// namespace Dice::rdf::internal

#endif//RDF_PARSER_ABSTRACT_TRIPLE_HPP
