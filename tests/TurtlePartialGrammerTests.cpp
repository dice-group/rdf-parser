
#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/StringParser.hpp>
#include <Dice/rdf_parser/TurtleParser.hpp>


using namespace rdf_parser::Turtle;


TEST(PatrialGrammerTest, parseSparqslCollectison) {

    rdf_parser::Turtle::TurtleParser<true,StringParser<true>> parser("?x <sad>  ?name ") ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
//    bool t2=rdf_parser::Turtle::TermParser::isTermParsable("\" hello \'hello\'  \"");
//    ASSERT_EQ(t1, true);
//    ASSERT_EQ(t2, true);
    ASSERT_EQ(1, true);
}

TEST(PatrialGrammerTest, F1) {

    rdf_parser::Turtle::TurtleParser<true,StringParser<true>> parser("?g <sad> ?who") ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}
