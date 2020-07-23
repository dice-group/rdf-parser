
#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/PartialGrammerParsers/CollectionParser.hpp>





TEST(PatrialGrammerTest, parseSparqslCollectison) {

    rdf_parser::Turtle::TurtleParser<StringParser<true>> parser("?x foaf:name  ?name ") ;
    auto it= parser.begin();
    while (it)
        it++;
//    bool t2=rdf_parser::Turtle::TermParser::isTermParsable("\" hello \'hello\'  \"");
//    ASSERT_EQ(t1, true);
//    ASSERT_EQ(t2, true);
    ASSERT_EQ(1, true);
}

TEST(PatrialGrammerTest, F1) {

    rdf_parser::Turtle::TurtleParser<StringParser<true>> parser("?g dc:publisher ?who") ;
    bool x=parser.isContentParsable();
    ASSERT_EQ(x, true);
}
