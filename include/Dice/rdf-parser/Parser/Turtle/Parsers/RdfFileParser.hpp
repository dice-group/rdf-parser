#ifndef RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP


/**
 * FileParser is responsible for parsing rdfs  from file sources.
 */


#include <utility>

#include "Dice/rdf-parser/Parser/Turtle/Parsers/BaseFileParser.hpp"

namespace Dice::rdf_parser::Turtle::parsers {

	class RdfFileParser : public BaseFileParser<false> {

	public:
		/**
        * The constructor start the parsing.if the input is not valid it will throws and exception.
        * it also invoke nextTriple to have the first triple ready for using .
        * @param filename the filename of the file we want to parse
        */
		explicit RdfFileParser(std::string text) : BaseFileParser<false>(std::move(text)) {}

		/**
        * checks whether a file is valid rdf turtle file
        */
		static bool isParsable(const std::string& filename) {
			try {
				std::ifstream infile(filename);
				tao::pegtl::read_input file(filename);
				tao::pegtl::parse<Grammar::grammar<false>>(file);
				return true;
			} catch (std::exception &e) {
				return false;
			}
		}

		/**
         * calculate the time for parsing a rdf turtle file.
         * Note that the calculated time is only for parsing without using processing the input(creating and storing the triples out of the string)
         */
		static long calculateParsingTime(const std::string& filename) {
			std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
			isParsable(filename);
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			return duration;
		}
	};
}// namespace Dice::rdf_parser::Turtle::parsers

#endif//RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP
