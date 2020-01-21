#include <gtest/gtest.h>
#include <Dice/rdf_parser/TurtleParser.hpp>

namespace {
    using namespace rdf_parser::Turtle;
    using namespace rdf_parser::store::rdf;
}


TEST(TurtleParserFilesTests,ntripleFile1) {
    TurtleParser<> parser("../datasets/g.nt");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleParserFilesTests,turtleFile1) {
    TurtleParser<> parser("datasets/dbpedia_2GB_subset.ttl");
    ASSERT_EQ(parser.isContentParsable(), true);

}
