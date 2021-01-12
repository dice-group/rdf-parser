#ifndef RDF_PARSER_ABSTRACT_TRIPLE_HPP
#define RDF_PARSER_ABSTRACT_TRIPLE_HPP
namespace Dice::rdf::internal {

	template<typename Element>
	class AbstractTriple {

		std::array<Element, 3> entries_{};

	public:
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
	};
}// namespace Dice::rdf::internal

#endif//RDF_PARSER_ABSTRACT_TRIPLE_HPP
