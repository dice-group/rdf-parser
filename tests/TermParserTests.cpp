#include <gtest/gtest.h>
#include <Dice/rdf_parser/RDF/Term.hpp>

namespace {
    using namespace rdf_parser::Turtle;
    using namespace rdf_parser::store::rdf;
}




TEST(TermParserTests,parsableLiterals1) {

    bool t1=rdf_parser::Turtle::TermParser::isTermParsable("\" hello  \"");
    bool t2=rdf_parser::Turtle::TermParser::isTermParsable("\" hello \'hello\'  \"");
    ASSERT_EQ(t1, true);
    ASSERT_EQ(t2, true);
}
//
//
TEST(TermParserTests,unparsableLiterals1) {

    bool t1 = rdf_parser::Turtle::TermParser::isTermParsable("\" hello  ");
    bool t2 = rdf_parser::Turtle::TermParser::isTermParsable(" hello \"");
    ASSERT_EQ(t1, false);
    ASSERT_EQ(t2, false);
}
