#ifndef RDF_PARSER_TRIPLE_HPP
#define RDF_PARSER_TRIPLE_HPP

/**
 * An RDF triple
 */


#include "Dice/rdf_parser/RDF/Term.hpp"

namespace rdf_parser::store::rdf {
    class Triple {

        std::array<Term, 3> terms_{};

    public:
        Triple() {}

        Triple(Term subject, Term predicate, Term object) :
                terms_{subject, predicate, object} {}

        [[nodiscard]] const Term &subject() const { return terms_[0]; }

        [[nodiscard]] Term &subject() { return terms_[0]; }

        [[nodiscard]] const Term &predicate() const { return terms_[1]; }

        [[nodiscard]] Term &predicate() { return terms_[1]; }

        [[nodiscard]] const Term &object() const { return terms_[2]; }

        [[nodiscard]] Term &object() { return terms_[2]; }

        Term &operator[](std::size_t pos) { return terms_[pos]; }

        const Term &operator[](std::size_t pos) const { return terms_[pos]; }

        void setSubject(Term subject) { terms_[0] = std::move(subject); }

        void setPredicate(Term predicate) { terms_[1] = std::move(predicate); }

        void setObject(Term object) { terms_[2] = std::move(object); }

    };
}

#endif //RDF_PARSER_TRIPLE_HPP
