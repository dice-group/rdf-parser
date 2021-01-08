#ifndef RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP


/**
 * FileParser is responsible for parsing rdfs  from file sources.
 */



#include "BaseFileParser.hpp"

namespace {
    using namespace tao::pegtl;
}

namespace rdf_parser::Turtle::parsers {

    class RdfFileParser : public BaseFileParser<false> {

    public:
        /**
        * The constructor start the parsing.if the input is not valid it will throws and exception.
        * it also invoke nextTriple to have the first triple ready for using .
        * @param filename the filename of the file we want to parse
        */
        RdfFileParser(std::string text) : BaseFileParser<false>(text) {}


    };
}

#endif //RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP
