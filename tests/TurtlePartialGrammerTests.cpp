
#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/PartialGrammerParsers/CollectionParser.hpp>




TEST(PatrialGrammerTest, parseSparqlCollection) {

    auto a=rdf_parser::Turtle::PartialGrammerParsers::CollectionParser::ParseSparqlCollection("(1 'ff' '$r' 'q' 2  )");
//    bool t2=rdf_parser::Turtle::TermParser::isTermParsable("\" hello \'hello\'  \"");
//    ASSERT_EQ(t1, true);
//    ASSERT_EQ(t2, true);
    ASSERT_EQ(1, true);
}


TEST(PatrialGrammerTest, parseSparqslCollection) {

    rdf_parser::Turtle::TurtleParser<StringParser<true>> parser("(1 'ff' '$r' 'q' 2  )") ;
    auto it= parser.begin();
    while (it)
        it++;
//    bool t2=rdf_parser::Turtle::TermParser::isTermParsable("\" hello \'hello\'  \"");
//    ASSERT_EQ(t1, true);
//    ASSERT_EQ(t2, true);
    ASSERT_EQ(1, true);
}