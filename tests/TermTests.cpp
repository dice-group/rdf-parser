#include <gtest/gtest.h>
#include <Dice/rdf_parser/TurtleParser.hpp>

namespace {
	using namespace rdf_parser::Turtle;
	using namespace rdf_parser::store::rdf;
}


TEST(TermTests, parseIRI) {
	TurtleParser<false,StringParser<>> parser("@prefix pref: <http://example.com/> . "
									  "<http://example.com/x> a pref:x.");
	TurtleParser<false,StringParser<>>::Iterator iterator = parser.begin();
	ASSERT_TRUE(bool(iterator));
	const Triple &triple = *iterator;
	// check if the non-prefix IRI is correct
	ASSERT_EQ(triple.subject().getIdentifier(), "<http://example.com/x>");
	// check if the prefix IRI is correct
	ASSERT_EQ(triple.subject().getIdentifier(), "<http://example.com/x>");
}

TEST(TermTests, parseStringTerm) {
	TurtleParser<false,StringParser<>> parser("@prefix xsd: <http://www.w3.org/2001/XMLSchema#> . "
									  "<http://example.com/x> a \"text\". "
									  "<http://example.com/x> a \"text\"^^<http://www.w3.org/2001/XMLSchema#string>. "
									  "<http://example.com/x> a \"text\"^^xsd:string. ");
	TurtleParser<false,StringParser<>>::Iterator iterator = parser.begin();
	ASSERT_TRUE(bool(iterator));
	Triple plain = *iterator;
	++iterator;
	Triple full_typed = *iterator;
	++iterator;
	Triple prefix_typed = *iterator;

	// check if they are correct
	ASSERT_EQ(plain.object().getIdentifier(), "\"text\"");
	ASSERT_EQ(full_typed.object().getIdentifier(), "\"text\"");
	ASSERT_EQ(prefix_typed.object().getIdentifier(), "\"text\"");
}


TEST(TermTests, parseNumbers) {
	TurtleParser<false,StringParser<>> parser("@prefix : <http://example.org/elements> .                                                                              \n"
									  "<http://en.wikipedia.org/wiki/Helium>   "
		    						  ":atomicNumber 2 ;"
			  						  " :atomicMass 4.002602 ;"
			                          " :specificGravity 1.663E-4 . ");
	TurtleParser<false,StringParser<>>::Iterator iterator = parser.begin();
	ASSERT_TRUE(bool(iterator));
	Triple integerNumber = *iterator;
	++iterator;
	Triple decimalNumber = *iterator;
	++iterator;
	Triple doubleNumber = *iterator;

	// check if they are correct
	ASSERT_EQ(integerNumber.object().getIdentifier(), "\"2\"^^<xsd:integer>");
	ASSERT_EQ(decimalNumber.object().getIdentifier(), "\"4.002602\"^^<xsd:decimal>");
	ASSERT_EQ(doubleNumber.object().getIdentifier(), "\"1.663E-4\"^^<xsd:double>");
}


