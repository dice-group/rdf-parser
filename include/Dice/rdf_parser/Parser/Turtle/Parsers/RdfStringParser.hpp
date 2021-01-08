
#ifndef RDF_PARSER_TURTLEPEGTLSTRINGPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLSTRINGPARSER_HPP


/**
 * StringParser is responsible for parsing rdf from string sources.
 */



#include <chrono>

#include "BaseStringParser.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Actions/Actions.hpp"


namespace {
    using namespace tao::pegtl;
}


namespace rdf_parser::Turtle::parsers {

    class RdfStringParser : public BaseStringParser<false> {


    public:

        /**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param text the string to parse
         */
        RdfStringParser(std::string text): BaseStringParser<false>(text) {}



        ~RdfStringParser() override {}


    };
}

#endif //RDF_PARSER_TURTLEPEGTLSTRINGPARSER_HPP
