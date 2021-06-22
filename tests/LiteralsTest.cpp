#include <Dice/RDF/ParseTerm.hpp>
#include <Dice/rdf-parser/TurtleStringParser.hpp>
#include <gtest/gtest.h>


namespace Dice::tests::rdf_parser::literals_tests {
	using namespace Dice::rdf_parser::internal::Turtle;
	using namespace Dice::rdf;
	using namespace Dice::rdf_parser::internal::Turtle::Parsers;
	using namespace Dice::rdf_parser;

    TEST(LiteralsTests, boolean) {
    Term term = parse_term("false");
	std::cout<<term.getIdentifier();
    ASSERT_EQ(term.type(), Term::NodeType::Literal_);
	ASSERT_EQ(term.getIdentifier(), "\"false\"^^<http://www.w3.org/2001/XMLSchema#boolean>");
}

    TEST(LiteralsTests, integer) {
        Term term = parse_term("-5");
        std::cout<<term.getIdentifier();
        ASSERT_EQ(term.type(), Term::NodeType::Literal_);
        ASSERT_EQ(term.getIdentifier(), "\"-5\"^^<http://www.w3.org/2001/XMLSchema#integer>");
    }

    TEST(LiteralsTests, decimal) {
        Term term = parse_term("-5.0");
        std::cout<<term.getIdentifier();
        ASSERT_EQ(term.type(), Term::NodeType::Literal_);
        ASSERT_EQ(term.getIdentifier(), "\"-5.0\"^^<http://www.w3.org/2001/XMLSchema#decimal>");
    }

    TEST(LiteralsTests, Double) {
        Term term = parse_term("4.2E9");
        std::cout<<term.getIdentifier();
        ASSERT_EQ(term.type(), Term::NodeType::Literal_);
        ASSERT_EQ(term.getIdentifier(), "\"4.2E9\"^^<http://www.w3.org/2001/XMLSchema#double>");
    }

}
