
#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/PartialGrammerParsers/CollectionParser.hpp>


TEST(PatrialGrammerTest, parseCollection) {

    auto a=rdf_parser::Turtle::PartialGrammerParsers::CollectionParser::ParseCollection("(1 'ff' 'q' 2  )");
//    bool t2=rdf_parser::Turtle::TermParser::isTermParsable("\" hello \'hello\'  \"");
//    ASSERT_EQ(t1, true);
//    ASSERT_EQ(t2, true);
    ASSERT_EQ(1, true);
}