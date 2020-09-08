
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

    template<bool sparqlQuery=false>
    class TriplesParser {

    protected:

        TriplesParser(){
            current_triple=std::make_shared<std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple>>();};
        std::shared_ptr<std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple>> current_triple;


    public:

        class Iterator {

        private:
            bool done_;
            bool parser_done_;
            TriplesParser* triplesParser;

        public:
            explicit Iterator(TriplesParser* triplesParser) :
                    done_{false}, parser_done_{false} {
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
        const  std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple>& getCurrentTriple() {
            return *current_triple;
        }


        virtual ~TriplesParser() {};


        virtual Iterator begin()=0;

        bool end() { return false; }


    };
}


#endif //RDF_PARSER_TRIPLESPARSER_HPP
