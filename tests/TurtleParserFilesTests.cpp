#include <gtest/gtest.h>

#include <Dice/rdf-parser/TurtleFileParser.hpp>

namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests {
		using namespace Dice::rdf_parser::Turtle::parsers;

	TEST(TurtleParserFilesTests, parseSWDF) {
		TurtleFileParser parser{"../tests/datasets/swdf.nt"};
		long i = 0;
		for (const auto &item : parser) {
			if (item.hash())
				i++;
		}
		ASSERT_TRUE(i > 0);
	}
}// namespace Dice::tests::rdf_parser::turtle_parser_concurrent_tests