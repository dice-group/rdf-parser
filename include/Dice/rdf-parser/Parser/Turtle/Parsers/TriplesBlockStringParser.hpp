//
// Created by fakhr on 08.01.21.
//

#ifndef RDF_PARSER_TRIPLESBLOCKSTRINGPARSER_HPP
#define RDF_PARSER_TRIPLESBLOCKSTRINGPARSER_HPP


#include "BaseStringParser.hpp"

/**
 * TriplesBlockStringParser is responsible for parsing sparql's tripleBlocks from string sources.
 */

namespace {
    using namespace tao::pegtl;
}


namespace rdf_parser::Turtle::parsers {

    class TriplesBlockStringParser : public BaseStringParser<true> {


    public:


        /**
         * The constructor start the parsing.if the input is not valid it will throws an exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param text the string to parse
         */
        TriplesBlockStringParser(std::string text) : BaseStringParser<true>(text) {
        }


        /**
        * The constructor start the parsing.if the input is not valid it will throws and exception.
        * it also invoke nextTriple to have the first triple ready for using .
        * @param text the string to parse
        * @param prefix_map defines prefixes to be added before parsing
        */
        TriplesBlockStringParser(std::string text, std::map<std::string, std::string> prefix_map) : BaseStringParser<true>(text,
                                                                                                                     prefix_map) {
        };
    };
}

#endif //RDF_PARSER_TRIPLESBLOCKSTRINGPARSER_HPP
