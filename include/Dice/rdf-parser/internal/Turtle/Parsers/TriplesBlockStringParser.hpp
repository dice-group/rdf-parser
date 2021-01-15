#ifndef RDF_PARSER_TRIPLESBLOCKSTRINGPARSER_HPP
#define RDF_PARSER_TRIPLESBLOCKSTRINGPARSER_HPP


#include <utility>

#include "Dice/rdf-parser/internal/Turtle/Parsers/BaseStringParser.hpp"

/**
 * TriplesBlockStringParser is responsible for parsing sparql's tripleBlocks from string sources.
 */


namespace Dice::rdf_parser::internal::Turtle::Parsers {

	class TriplesBlockStringParser : public BaseStringParser<true> {


	public:
		/**
         * The constructor start the parsing.if the input is not valid it will throws an exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param text the string to parse
         */
		explicit TriplesBlockStringParser(std::string text) : BaseStringParser<true>(std::move(text)) {}


		/**
        * The constructor start the parsing.if the input is not valid it will throws and exception.
        * it also invoke nextTriple to have the first triple ready for using .
        * @param text the string to parse
        * @param prefix_map defines prefixes to be added before parsing. In a std::unordered_map.
        */
		TriplesBlockStringParser(std::string text, const std::unordered_map<std::string, std::string> &prefix_map) : BaseStringParser<true>(std::move(text),
																																  prefix_map){};

        /**
        * The constructor start the parsing.if the input is not valid it will throws and exception.
        * it also invoke nextTriple to have the first triple ready for using .
        * @param text the string to parse
        * @param prefix_map defines prefixes to be added before parsing. In a robin_hood map.
        */
        TriplesBlockStringParser(std::string text, const robin_hood::unordered_map<std::string, std::string> &prefix_map) : BaseStringParser<true>(std::move(text),
                                                                                                                                            prefix_map){};
	};
}// namespace Dice::rdf_parser::Turtle::parsers

#endif//RDF_PARSER_TRIPLESBLOCKSTRINGPARSER_HPP
