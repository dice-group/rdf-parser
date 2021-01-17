#ifndef RDF_PARSER_ABSTRACT_TRIPLE_HPP
#define RDF_PARSER_ABSTRACT_TRIPLE_HPP

#include <Dice/hash/DiceHash.hpp>

namespace Dice::rdf::internal {

	template<typename Element>
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

		AbstractTriple(Element subject, Element predicate, Element object) : entries_{subject, predicate, object} {}

		[[nodiscard]] const Element &subject() const { return entries_[0]; }

		[[nodiscard]] Element &subject() { return entries_[0]; }

		[[nodiscard]] const Element &predicate() const { return entries_[1]; }

		[[nodiscard]] Element &predicate() { return entries_[1]; }

		[[nodiscard]] const Element &object() const { return entries_[2]; }

		[[nodiscard]] Element &object() { return entries_[2]; }

		Element &operator[](std::size_t pos) { return entries_[pos]; }

		const Element &operator[](std::size_t pos) const { return entries_[pos]; }


		void setSubject(Element subject) { entries_[0] = std::move(subject); }

		void setPredicate(Element predicate) { entries_[1] = std::move(predicate); }

		void setObject(Element object) { entries_[2] = std::move(object); }

		iterator begin() { return entries_.begin(); }
		const_iterator begin() const { return entries_.begin(); }
		iterator end() { return entries_.end(); }
		const_iterator end() const { return entries_.end(); }
		iterator rbegin() { return entries_.rbegin(); }
		const_iterator rbegin() const { return entries_.rbegin(); }
		reverse_iterator rend() { return entries_.rend(); }
		const_reverse_iterator rend() const { return entries_.rend(); }


	};

}// namespace Dice::rdf::internal

#endif//RDF_PARSER_ABSTRACT_TRIPLE_HPP
