
#ifndef RDF_PARSER_TRIPLESPARSER_HPP
#define RDF_PARSER_TRIPLESPARSER_HPP

#include "Dice/rdf_parser/RDF/Triple.hpp"


/**
 * Base class for parsing triples from different sources.
 */

namespace {
    using namespace rdf_parser::store::rdf;


}
namespace rdf_parser::Turtle {

    template<class Derived,bool sparqlQuery>
    class Iterator;

    template<class Derived,bool sparqlQuery = false>
    class TriplesParser {

    protected:
    	using element_type = std::conditional_t<sparqlQuery, SparqlQuery::TriplePatternElement, Triple>;

        explicit TriplesParser() {
            current_triple = std::make_shared<element_type>();
        };
        std::shared_ptr<element_type> current_triple;


    public:

        /**
         * process to the next parsed triple.
         */
        virtual void nextTriple() = 0;

        /**
         * check whether there is a further triple
         */
        virtual bool hasNextTriple() const = 0;

        /**
         * get the current triple
         */
        const element_type &getCurrentTriple() {
            return *current_triple;
        }


        virtual ~TriplesParser() {};


        Iterator<Derived,sparqlQuery> begin()
        {
            return static_cast<Derived*>(this)->begin_implementation();
        }

        bool end() { return false; }

    };

    template<class Derived,bool sparqlQuery = false>
    class Iterator {

    private:
        bool done_;
        bool parser_done_;
		Derived *triplesParser = nullptr;

    public:
        explicit Iterator(Derived *triplesParser) :
                done_{false}, parser_done_{false}, triplesParser{triplesParser} {
            //check if there is at least one parsed triple
            if (triplesParser->hasNextTriple())
                this->operator++();
            else
                parser_done_ = true;
        };


        void operator++() {
            if (parser_done_) {
                done_ = true;
            } else {
                triplesParser->nextTriple();
                if (not triplesParser->hasNextTriple())
                    parser_done_ = true;
            }
        }

        void operator++(int) { operator++(); }

        operator bool() { return not done_; }

        const std::conditional_t<sparqlQuery, SparqlQuery::TriplePatternElement, Triple> &
        operator*() { return triplesParser->getCurrentTriple(); }
    };


    };




#endif //RDF_PARSER_TRIPLESPARSER_HPP
