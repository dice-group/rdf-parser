
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

    class TriplesParser {
    protected:

        Triple current_triple;


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
        const Triple &getCurrentTriple() {
            return current_triple;
        }


        virtual ~TriplesParser() {};




    };
}


#endif //RDF_PARSER_TRIPLESPARSER_HPP
