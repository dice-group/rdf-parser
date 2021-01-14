#include <gtest/gtest.h>

#include <Dice/rdf-parser/TurtleFileParser.hpp>

namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests {
		using namespace Dice::rdf_parser::Turtle::parsers;

	TEST(TurtleParserFilesTests, ntripleFile1) {
		TurtleFileParser parser{"../datasets/g.nt"};
		long i = 0;
		for (const auto &item : parser) {
			if (item.hash())
				i++;
		}
		ASSERT_TRUE(i > 0);
	}

	TEST(TurtleParserFilesTests, ntripleFile1_concurrent) {
		TurtleFileParser parser{"../datasets/g.nt"};
		long i = 0;
		for (const auto &item : parser) {
			if (item.hash())
				i++;
		}
		ASSERT_TRUE(i > 0);
	}
}// namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests