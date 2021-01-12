#include <gtest/gtest.h>

#include <Dice/rdf-parser/Parser/Turtle/Parsers/RdfFileParser.hpp>

namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests {
	namespace {
		using namespace Dice::rdf_parser::Turtle::parsers;
	}

	TEST(TurtleParserFilesTests, ntripleFile1) {
		ASSERT_EQ(RdfFileParser::isParsable("../datasets/g.nt"), true);
	}

	TEST(TurtleParserFilesTests, turtleFile1) {
		ASSERT_EQ(RdfFileParser::isParsable("datasets/dbpedia_2GB_subset.tt"), true);
	}
}// namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests