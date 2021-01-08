#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/RdfFileParser.hpp>

namespace {
    using namespace rdf_parser::Turtle::parsers;
}


TEST(TurtleParserFilesTests,ntripleFile1) {
    ASSERT_EQ(RdfFileParser::isParsable("../datasets/g.nt"), true);
}

TEST(TurtleParserFilesTests,turtleFile1) {
    ASSERT_EQ(RdfFileParser::isParsable("datasets/dbpedia_2GB_subset.tt"), true);

}
