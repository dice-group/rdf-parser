#include <gtest/gtest.h>

#include <Dice/rdf-parser/Parser/Turtle/Parsers/RdfConcurrentStreamParser.hpp>
#include <Dice/rdf-parser/Parser/Turtle/Parsers/RdfFileParser.hpp>
// todo: broken?
//#include <Dice/rdf-parser/Parser/Turtle/Parsers/TriplesBlockFileParser.hpp>
// todo: broken?
//#include <Dice/rdf-parser/Parser/Turtle/Parsers/RdfStreamParser.hpp>

namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests {
	namespace {
		using namespace Dice::rdf_parser::Turtle::parsers;
	}

	TEST(TurtleParserFilesTests, ntripleFile1) {
		RdfFileParser parser{"../datasets/g.nt"};
		long i = 0;
		for (const auto &item : parser) {
			if (item.hash())
				i++;
		}
		ASSERT_TRUE(i > 0);
	}

	TEST(TurtleParserFilesTests, ntripleFile1_concurrent) {
		RdfConcurrentStreamParser parser{"../datasets/g.nt"};
		long i = 0;
		for (const auto &item : parser) {
			if (item.hash())
				i++;
		}
		ASSERT_TRUE(i > 0);
	}

	TEST(TurtleParserFilesTests, turtleFile1) {
		ASSERT_EQ(RdfFileParser::isParsable("datasets/dbpedia_2GB_subset.tt"), true);
	}
}// namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests