//
// Created by fakhr on 08.01.21.
//

#ifndef RDF_PARSER_TRIPLESBLOCKPARSER_HPP
#define RDF_PARSER_TRIPLESBLOCKPARSER_HPP


#include <chrono>

#include "BaseStringParser.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Actions/Actions.hpp"

/**
 * TriplesBlockParser is responsible for parsing sparql's tripleBlocks from string sources.
 * It parse the string one time and put the parsed triples in a std::queue
 */

namespace {
    using namespace tao::pegtl;
}


namespace rdf_parser::Turtle::parsers {

    class TriplesBlockParser : public BaseStringParser<true> {


    public:


        /**
         * The constructor start the parsing.if the input is not valid it will throws an exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param text the string to parse
         */
        TriplesBlockParser(std::string text) : BaseStringParser(text) {
        }


        /**
        * The constructor start the parsing.if the input is not valid it will throws and exception.
        * it also invoke nextTriple to have the first triple ready for using .
        * @param text the string to parse
        * @param prefix_map defines prefixes to be added before parsing
        */
        TriplesBlockParser(std::string text, std::map<std::string, std::string> prefix_map) : BaseStringParser(text,
                                                                                                               prefix_map) {
        };
    };
}

#endif //RDF_PARSER_TRIPLESBLOCKPARSER_HPP
