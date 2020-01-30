#include <gtest/gtest.h>
#include <Dice/rdf_parser/TurtleParser.hpp>

namespace {
	using namespace rdf_parser::Turtle;
	using namespace rdf_parser::store::rdf;
}


TEST(TermTests, parseIRI) {
	TurtleParser<StringParser> parser("@prefix pref: <http://example.com/> . "
									  "<http://example.com/x> a pref:x.");
	TurtleParser<StringParser>::Iterator iterator = parser.begin();
	ASSERT_TRUE(bool(iterator));
	const Triple &triple = *iterator;
	// check if the non-prefix IRI is correct
	ASSERT_EQ(triple.subject().getIdentifier(), "<http://example.com/x>");
	// check if the prefix IRI is correct
	ASSERT_EQ(triple.subject().getIdentifier(), "<http://example.com/x>");
}

TEST(TermTests, parseStringTerm) {
	TurtleParser<StringParser> parser("@prefix xsd: <http://www.w3.org/2001/XMLSchema#> . "
									  "<http://example.com/x> a \"text\". "
									  "<http://example.com/x> a \"text\"^^<http://www.w3.org/2001/XMLSchema#string>. "
									  "<http://example.com/x> a \"text\"^^xsd:string. ");
	TurtleParser<StringParser>::Iterator iterator = parser.begin();
	ASSERT_TRUE(bool(iterator));
	const Triple &plain = *iterator;
	++iterator;
	const Triple &full_typed = *iterator;
	++iterator;
	const Triple &prefix_typed = *iterator;

	// check if they are correct
	ASSERT_EQ(plain.object().getIdentifier(), "\"text\"");
	ASSERT_EQ(full_typed.object().getIdentifier(), "\"text\"");
	ASSERT_EQ(prefix_typed.object().getIdentifier(), "\"text\"");
}
