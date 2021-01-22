#include <gtest/gtest.h>

#include <Dice/rdf-parser/TurtleStringParser.hpp>


namespace Dice::tests::rdf_parser::turtle_official_evaluation_tests {
	using namespace Dice::rdf_parser;

	TEST(TurtleOfficialEvaluationTests, bareword_a_predicate) {
		TurtleStringParser turtleParser("<http://a.example/s> a <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, bareword_decimal) {
		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> 1.0 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, bareword_double) {
		TurtleStringParser turtleParser(
				"<http://a.example/s> <http://a.example/p> \"1E0\"^^<http://www.w3.org/2001/XMLSchema#double> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> 1E0 .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_as_object) {
		TurtleStringParser turtleParser(
				"<http://a.example/s> <http://a.example/p> [ <http://a.example/p2> <http://a.example/o2> ] .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> _:b1 .\n"
										  "_:b1 <http://a.example/p2> <http://a.example/o2> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_as_subject) {
		TurtleStringParser turtleParser(
				"[ <http://a.example/p> <http://a.example/o> ] <http://a.example/p2> <http://a.example/o2> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:b1 <http://a.example/p> <http://a.example/o> .\n"
										  "_:b1 <http://a.example/p2> <http://a.example/o2> .");

		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_containing_collection) {
		TurtleStringParser turtleParser("[ <http://a.example/p1> (1) ] .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:b1 <http://a.example/p1> _:el1 .\n"
										  "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
										  "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_with_multiple_triples) {
		TurtleStringParser turtleParser(
				"[ <http://a.example/p1> <http://a.example/o1> ; <http://a.example/p2> <http://a.example/o2> ] <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:b1 <http://a.example/p1> <http://a.example/o1> .\n"
										  "_:b1 <http://a.example/p2> <http://a.example/o2> .\n"
										  "_:b1 <http://a.example/p> <http://a.example/o> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, collection_object) {
		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> (1) .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> _:el1 .\n"
										  "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
										  "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, collection_subject) {
		TurtleStringParser turtleParser("(1) <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
				"_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
				"_:el1 <http://a.example/p> <http://a.example/o> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, comment_following_PNAME_NS) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/> .\n"
										"<http://a.example/s> <http://a.example/p> p:#comment\n"
										".");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> <http://a.example/> .");
	}

	TEST(TurtleOfficialEvaluationTests, double_lower_case_e) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> 1e0 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"1e0\"^^<http://www.w3.org/2001/XMLSchema#double> .");
	}

	TEST(TurtleOfficialEvaluationTests, empty_collection) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> () .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, first) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> ((1) 2) .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> _:outerEl1 .\n"
										  "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> _:innerEl1 .\n"
										  "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
										  "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
										  "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> _:outerEl2 .\n"
										  "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
										  "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .");
		//ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
	}

	TEST(TurtleOfficialEvaluationTests, HYPHEN_MINUS_in_localName) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:s- <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s-> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, IRI_with_all_punctuation) {

		TurtleStringParser turtleParser(
				"<scheme:!$%25&amp;'()*+,-./0123456789:/@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~?#> <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<scheme:!$%25&amp;'()*+,-./0123456789:/@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~?#> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, IRIREF_datatype) {

		TurtleStringParser turtleParser(
				"<http://a.example/s> <http://a.example/p> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .");
	}

	TEST(TurtleOfficialEvaluationTests, labeled_blank_node_object) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> _:o .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> _:b1 .");
	}

	TEST(TurtleOfficialEvaluationTests, labeled_blank_node_subject) {

		TurtleStringParser turtleParser("_:s <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:b1 <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, langtagged_LONG_with_subtag) {

		TurtleStringParser turtleParser("# Test long literal with lang tag\n"
										"@prefix :  <http://example.org/ex#> .\n"
										":a :b \"\"\"Cheers\"\"\"@en-UK .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://example.org/ex#a> <http://example.org/ex#b> \"Cheers\"@en-UK .");
	}

	TEST(TurtleOfficialEvaluationTests, langtagged_non_LONG) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> \"chat\"@en .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"chat\"@en .");
	}

	TEST(TurtleOfficialEvaluationTests, lantag_with_subtag) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> \"chat\"@en-us .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"chat\"@en-us .");
	}

	TEST(TurtleOfficialEvaluationTests, last) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> (1 (2)) .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> _:outerEl1 .\n"
										  "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
										  "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> _:outerEl2 .\n"
										  "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> _:innerEl1 .\n"
										  "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
										  "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
										  "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL1) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> 'x' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"x\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL1_all_punctuation) {

		TurtleStringParser turtleParser(
				"<http://a.example/s> <http://a.example/p> ' !\"#$%&():;<=>?@[]^_`{|}~' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \" !\\\"#$%&():;<=>?@[]^_`{|}~\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL1_ascii_boundaries) {

		TurtleStringParser turtleParser(
				"<http://a.example/s> <http://a.example/p> ' \t\u000B\f\u000E&([]\u007F' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"\\u0000\\t\\u000B\\u000C\\u000E&([]\\u007F\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_false) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> false .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"false\"^^<http://www.w3.org/2001/XMLSchema#boolean> .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL_LONG1_ascii_boundaries) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> ' &([]\u007F' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\u0000&([]\\u007F\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL_LONG1_with_1_squote) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '''x'y''' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"x'y\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL_LONG1_with_2_squotes) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '''x''y''' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"x''y\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_ascii_boundaries) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> \" !#[]\u007F\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\u0000!#[]\\u007F\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_with_1_squote) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> \"\"\"x\"y\"\"\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"x\\\"y\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_with_2_squotes) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> \"\"\"x\"\"y\"\"\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"x\\\"\\\"y\" .");
	}

	TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_with_REVERSE_SOLIDUS) {

		TurtleStringParser turtleParser("@prefix : <http://example.org/ns#> .\n"
										"\n"
										":s :p1 \"\"\"test-\\\\\"\"\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://example.org/ns#s> <http://example.org/ns#p1> \"test-\\\\\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_true) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> true .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"true\"^^<http://www.w3.org/2001/XMLSchema#boolean> .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_with_BACKSPACE) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '\b' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\u0008\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_with_CARRIAGE_RETURN) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '''\n"
										"''' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\r\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_with_CHARACTER_TABULATION) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '\t' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\t\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_with_FORM_FEED) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '\f' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\u000C\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_with_LINE_FEED) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '''\n"
										"''' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\n\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_with_numeric_escape4) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '\\u006F' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"o\" .");
	}

	TEST(TurtleOfficialEvaluationTests, literal_with_REVERSE_SOLIDUS) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> '\\\\' .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> \"\\\\\" .");
	}

	TEST(TurtleOfficialEvaluationTests, localName_with_assigned_nfc_bmp_PN_CHARS_BASE_character_boundaries) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/> .\n"
										"<http://a.example/s> <http://a.example/p> p:AZazÀÖØöø˿Ͱͽ΄῾\u200C\u200D⁰↉Ⰰ⿕、ퟻ﨎ﷇﷰ\uFFEF .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> <http://a.example/AZaz\\u00C0\\u00D6\\u00D8\\u00F6\\u00F8\\u02FF\\u0370\\u037D\\u0384\\u1FFE\\u200C\\u200D\\u2070\\u2189\\u2C00\\u2FD5\\u3001\\uD7FB\\uFA0E\\uFDC7\\uFDF0\\uFFEF> .");
	}

	/*TEST(TurtleOfficialEvaluationTests, localName_with_assigned_nfc_PN_CHARS_BASE_character_boundaries) {
   
    RdfStringParser turtleParser("@prefix p: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> p:AZazÀÖØöø˿Ͱͽ΄῾\u200C\u200D⁰↉Ⰰ⿕、ퟻ﨎ﷇﷰ\uFFEF\uD800\uDC00\uDB40\uDDEF .");
    auto it=turtleParser.begin();
    RdfStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> <http://a.example/AZaz\\u00C0\\u00D6\\u00D8\\u00F6\\u00F8\\u02FF\\u0370\\u037D\\u0384\\u1FFE\\u200C\\u200D\\u2070\\u2189\\u2C00\\u2FD5\\u3001\\uD7FB\\uFA0E\\uFDC7\\uFDF0\\uFFEF\\U00010000\\U000E01EF> .");
   
}*/

	TEST(TurtleOfficialEvaluationTests, localname_with_COLON) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:s: <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s:> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, localName_with_leading_digit) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:0 <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/0> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, localName_with_leading_underscore) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:_ <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/_> <http://a.example/p> <http://a.example/o> .");
	}

	/*
TEST(TurtleOfficialEvaluationTests, localName_with_nfc_PN_CHARS_BASE_character_boundaries) {
   
    RdfStringParser turtleParser("@prefix p: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> p:AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF﨎\uFDCFﷰ\uFFEF\uD800\uDC00\uDB7F\uDFFD .");
    auto it=turtleParser.begin();
    RdfStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> <http://a.example/AZaz\\u00C0\\u00D6\\u00D8\\u00F6\\u00F8\\u02FF\\u0370\\u037D\\u037F\\u1FFF\\u200C\\u200D\\u2070\\u218F\\u2C00\\u2FEF\\u3001\\uD7FF\\uFA0E\\uFDCF\\uFDF0\\uFFEF\\U00010000\\U000EFFFD> .");
   
}
*/

	TEST(TurtleOfficialEvaluationTests, localName_with_non_leading_extras) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:a·̀ͯ‿.⁀ <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/a\\u00b7\\u0300\\u036f\\u203f\\u002e\\u2040> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, negative_numeric) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> -1 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"-1\"^^<http://www.w3.org/2001/XMLSchema#integer> .");
	}

	TEST(TurtleOfficialEvaluationTests, nested_blankNodePropertyLists) {

		TurtleStringParser turtleParser(
				"[ <http://a.example/p1> [ <http://a.example/p2> <http://a.example/o2> ] ; <http://a.example/p> <http://a.example/o> ].");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:b1 <http://a.example/p1> _:b2 .\n"
										  "_:b2 <http://a.example/p2> <http://a.example/o2> .\n"
										  "_:b1 <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, nested_collection) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> ((1)) .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> _:outerEl1 .\n"
										  "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> _:innerEl1 .\n"
										  "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
										  "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
										  "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .");
	}

	TEST(TurtleOfficialEvaluationTests, number_sign_following_localName) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/> .\n"
										"<http://a.example/s> <http://a.example/p> p:o\\#numbersign\n"
										".");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> <http://a.example/o#numbersign> .");
	}

	TEST(TurtleOfficialEvaluationTests, number_sign_following_PNAME_NS) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"<http://a.example/s> <http://a.example/p> p:\\#numbersign\n"
										".");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> <http://a.example/#numbersign> .");
	}

	TEST(TurtleOfficialEvaluationTests, numeric_with_leading_0) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> 01 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"01\"^^<http://www.w3.org/2001/XMLSchema#integer> .");
	}

	TEST(TurtleOfficialEvaluationTests, objectList_with_two_objects) {

		TurtleStringParser turtleParser(
				"<http://a.example/s> <http://a.example/p> <http://a.example/o1>, <http://a.example/o2> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p> <http://a.example/o1> .\n"
										  "<http://a.example/s> <http://a.example/p> <http://a.example/o2> .");
	}

	TEST(TurtleOfficialEvaluationTests, percent_escaped_localName) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:%25 <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/%25> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, positive_numeric) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p> +1 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/s> <http://a.example/p> \"+1\"^^<http://www.w3.org/2001/XMLSchema#integer> .");
	}

	TEST(TurtleOfficialEvaluationTests, predicateObjectList_with_two_objectLists) {

		TurtleStringParser turtleParser(
				"<http://a.example/s> <http://a.example/p1> <http://a.example/o1>; <http://a.example/p2> <http://a.example/o2> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p1> <http://a.example/o1> .\n"
										  "<http://a.example/s> <http://a.example/p2> <http://a.example/o2> .");
	}

	TEST(TurtleOfficialEvaluationTests, prefix_reassigned_and_used) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"@prefix p: <http://b.example/>.\n"
										"p:s <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://b.example/s> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, repeated_semis_not_at_end) {

		TurtleStringParser turtleParser("<http://a.example/s> <http://a.example/p1> <http://a.example/o1>;; .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s> <http://a.example/p1> <http://a.example/o1> .");
	}

	TEST(TurtleOfficialEvaluationTests, reserved_escaped_localName) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:\\_\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\%00 <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://a.example/_~.-!$&'()*+,;=/?#@%00> <http://a.example/p> <http://a.example/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_eval_struct_01) {

		TurtleStringParser turtleParser(
				"<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_eval_struct_02) {

		TurtleStringParser turtleParser("<http://www.w3.org/2013/TurtleTests/s> \n"
										"      <http://www.w3.org/2013/TurtleTests/p1> <http://www.w3.org/2013/TurtleTests/o1> ;\n"
										"      <http://www.w3.org/2013/TurtleTests/p2> <http://www.w3.org/2013/TurtleTests/o2> ; \n"
										"      .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p1> <http://www.w3.org/2013/TurtleTests/o1> .\n"
				"<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p2> <http://www.w3.org/2013/TurtleTests/o2> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_01) {

		TurtleStringParser turtleParser("@prefix : <#> .\n"
										"[] :x :y .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"_:genid1 <http://www.w3.org/2013/TurtleTests/turtle-subm-01.ttl#x> <http://www.w3.org/2013/TurtleTests/turtle-subm-01.ttl#y> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_02) {

		TurtleStringParser turtleParser("# Test @prefix and qnames\n"
										"@prefix :  <http://example.org/base1#> .\n"
										"@prefix a: <http://example.org/base2#> .\n"
										"@prefix b: <http://example.org/base3#> .\n"
										":a :b :c .\n"
										"a:a a:b a:c .\n"
										":a a:a b:a .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/base1#a> <http://example.org/base1#b> <http://example.org/base1#c> .\n"
				"<http://example.org/base2#a> <http://example.org/base2#b> <http://example.org/base2#c> .\n"
				"<http://example.org/base1#a> <http://example.org/base2#a> <http://example.org/base3#a> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_03) {

		TurtleStringParser turtleParser("# Test , operator\n"
										"@prefix : <http://example.org/base#> .\n"
										":a :b :c,\n"
										"      :d,\n"
										"      :e .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#c> .\n"
				"<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#d> .\n"
				"<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#e> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_04) {

		TurtleStringParser turtleParser("# Test ; operator\n"
										"@prefix : <http://example.org/base#> .\n"
										":a :b :c ;\n"
										"   :d :e ;\n"
										"   :f :g .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#c> .\n"
				"<http://example.org/base#a> <http://example.org/base#d> <http://example.org/base#e> .\n"
				"<http://example.org/base#a> <http://example.org/base#f> <http://example.org/base#g> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_05) {

		TurtleStringParser turtleParser("# Test empty [] operator; not allowed as predicate\n"
										"@prefix : <http://example.org/base#> .\n"
										"[] :a :b .\n"
										":c :d [] .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:genid1 <http://example.org/base#a> <http://example.org/base#b> .\n"
										  "<http://example.org/base#c> <http://example.org/base#d> _:genid2 .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_06) {

		TurtleStringParser turtleParser("# Test non empty [] operator; not allowed as predicate\n"
										"@prefix : <http://example.org/base#> .\n"
										"[ :a :b ] :c :d .\n"
										":e :f [ :g :h ] .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:genid1 <http://example.org/base#a> <http://example.org/base#b> .\n"
										  "_:genid1 <http://example.org/base#c> <http://example.org/base#d> .\n"
										  "_:genid2 <http://example.org/base#g> <http://example.org/base#h> .\n"
										  "<http://example.org/base#e> <http://example.org/base#f> _:genid2 .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_07) {

		TurtleStringParser turtleParser("# 'a' only allowed as a predicate\n"
										"@prefix : <http://example.org/base#> .\n"
										":a a :b .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/base#a> <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://example.org/base#b> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_08) {

		TurtleStringParser turtleParser("@prefix : <http://example.org/stuff/1.0/> .\n"
										":a :b ( \"apple\" \"banana\" ) .\n"
										"");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"_:genid1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"banana\" .\n"
				"_:genid1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
				"_:genid2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"apple\" .\n"
				"_:genid2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> _:genid1 .\n"
				"<http://example.org/stuff/1.0/a> <http://example.org/stuff/1.0/b> _:genid2 .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_09) {

		TurtleStringParser turtleParser("@prefix : <http://example.org/stuff/1.0/> .\n"
										":a :b ( ) .\n"
										"");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/stuff/1.0/a> <http://example.org/stuff/1.0/b> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_10) {

		TurtleStringParser turtleParser("# Test integer datatyped literals using an OWL cardinality constraint\n"
										"@prefix owl: <http://www.w3.org/2002/07/owl#> .\n"
										"\n"
										"# based on examples in the OWL Reference\n"
										"\n"
										"_:hasParent a owl:ObjectProperty .\n"
										"\n"
										"[] a owl:Restriction ;\n"
										"  owl:onProperty _:hasParent ;\n"
										"  owl:maxCardinality 2 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"_:hasParent <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://www.w3.org/2002/07/owl#ObjectProperty> .\n"
				"_:genid1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://www.w3.org/2002/07/owl#Restriction> .\n"
				"_:genid1 <http://www.w3.org/2002/07/owl#onProperty> _:hasParent .\n"
				"_:genid1 <http://www.w3.org/2002/07/owl#maxCardinality> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_11) {

		TurtleStringParser turtleParser("<http://example.org/res1> <http://example.org/prop1> 000000 .\n"
										"<http://example.org/res2> <http://example.org/prop2> 0 .\n"
										"<http://example.org/res3> <http://example.org/prop3> 000001 .\n"
										"<http://example.org/res4> <http://example.org/prop4> 2 .\n"
										"<http://example.org/res5> <http://example.org/prop5> 4 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/res1> <http://example.org/prop1> \"000000\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
				"<http://example.org/res2> <http://example.org/prop2> \"0\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
				"<http://example.org/res3> <http://example.org/prop3> \"000001\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
				"<http://example.org/res4> <http://example.org/prop4> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
				"<http://example.org/res5> <http://example.org/prop5> \"4\"^^<http://www.w3.org/2001/XMLSchema#integer> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_12) {

		TurtleStringParser turtleParser("# Tests for - and _ in names, qnames\n"
										"@prefix ex1: <http://example.org/ex1#> .\n"
										"@prefix ex-2: <http://example.org/ex2#> .\n"
										"@prefix ex3_: <http://example.org/ex3#> .\n"
										"@prefix ex4-: <http://example.org/ex4#> .\n"
										"\n"
										"ex1:foo-bar ex1:foo_bar \"a\" .\n"
										"ex-2:foo-bar ex-2:foo_bar \"b\" .\n"
										"ex3_:foo-bar ex3_:foo_bar \"c\" .\n"
										"ex4-:foo-bar ex4-:foo_bar \"d\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/ex1#foo-bar> <http://example.org/ex1#foo_bar> \"a\" .\n"
				"<http://example.org/ex2#foo-bar> <http://example.org/ex2#foo_bar> \"b\" .\n"
				"<http://example.org/ex3#foo-bar> <http://example.org/ex3#foo_bar> \"c\" .\n"
				"<http://example.org/ex4#foo-bar> <http://example.org/ex4#foo_bar> \"d\" .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_13) {

		TurtleStringParser turtleParser("# Tests for rdf:_<numbers> and other qnames starting with _\n"
										"@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
										"@prefix ex:  <http://example.org/ex#> .\n"
										"@prefix :    <http://example.org/myprop#> .\n"
										"\n"
										"ex:foo rdf:_1 \"1\" .\n"
										"ex:foo rdf:_2 \"2\" .\n"
										"ex:foo :_abc \"def\" .\n"
										"ex:foo :_345 \"678\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/ex#foo> <http://www.w3.org/1999/02/22-rdf-syntax-ns#_1> \"1\" .\n"
				"<http://example.org/ex#foo> <http://www.w3.org/1999/02/22-rdf-syntax-ns#_2> \"2\" .\n"
				"<http://example.org/ex#foo> <http://example.org/myprop#_abc> \"def\" .\n"
				"<http://example.org/ex#foo> <http://example.org/myprop#_345> \"678\" .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_14) {

		TurtleStringParser turtleParser("# Test for : allowed\n"
										"@prefix :    <http://example.org/ron> .\n"
										"\n"
										"[] : [] .\n"
										"\n"
										": : : .\n"
										"");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("_:genid1 <http://example.org/ron> _:genid2 .\n"
										  "<http://example.org/ron> <http://example.org/ron> <http://example.org/ron> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_15) {

		TurtleStringParser turtleParser("# Test long literal\n"
										"@prefix :  <http://example.org/ex#> .\n"
										":a :b \"\"\"a long\n"
										"\tliteral\n"
										"with\n"
										"newlines\"\"\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/ex#a> <http://example.org/ex#b> \"a long\\n\\tliteral\\nwith\\nnewlines\" .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_16) {

		TurtleStringParser turtleParser("@prefix : <http://example.org/foo#> .\n"
										"\n"
										"## \\U00015678 is a not a legal codepoint\n"
										"## :a :b \"\"\"\\nthis \\ris a \\U00015678long\\t\n"
										"## literal\\uABCD\n"
										"## \"\"\" .\n"
										"## \n"
										"## :d :e \"\"\"\\tThis \\uABCDis\\r \\U00015678another\\n\n"
										"## one\n"
										"## \"\"\" .\n"
										"\n"
										"# \\U00015678 is a not a legal codepoint\n"
										"# \\U00012451 in Cuneiform numeric ban 3\n"
										":a :b \"\"\"\\nthis \\ris a \\U00012451long\\t\n"
										"literal\\uABCD\n"
										"\"\"\" .\n"
										"\n"
										":d :e \"\"\"\\tThis \\uABCDis\\r \\U00012451another\\n\n"
										"one\n"
										"\"\"\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/foo#a> <http://example.org/foo#b> \"\\nthis \\ris a \\U00012451long\\t\\nliteral\\uABCD\\n\" .\n"
				"<http://example.org/foo#d> <http://example.org/foo#e> \"\\tThis \\uABCDis\\r \\U00012451another\\n\\none\\n\" .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_17) {

		TurtleStringParser turtleParser("@prefix : <http://example.org/#> .\n"
										"\n"
										":a :b  1.0 .\n"
										"");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/#a> <http://example.org/#b> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_18) {

		TurtleStringParser turtleParser("@prefix : <http://example.org/#> .\n"
										"\n"
										":a :b \"\" .\n"
										"\n"
										":c :d \"\"\"\"\"\" .\n"
										"");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://example.org/#a> <http://example.org/#b> \"\" .\n"
										  "<http://example.org/#c> <http://example.org/#d> \"\" .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_19) {

		TurtleStringParser turtleParser("@prefix : <http://example.org#> .\n"
										":a :b 1.0 .\n"
										":c :d 1 .\n"
										":e :f 1.0e0 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org#a> <http://example.org#b> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org#c> <http://example.org#d> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
				"<http://example.org#e> <http://example.org#f> \"1.0e0\"^^<http://www.w3.org/2001/XMLSchema#double> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_20) {

		TurtleStringParser turtleParser("@prefix : <http://example.org#> .\n"
										":a :b -1.0 .\n"
										":c :d -1 .\n"
										":e :f -1.0e0 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org#a> <http://example.org#b> \"-1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org#c> <http://example.org#d> \"-1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
				"<http://example.org#e> <http://example.org#f> \"-1.0e0\"^^<http://www.w3.org/2001/XMLSchema#double> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_21) {

		TurtleStringParser turtleParser("# Test long literal\n"
										"@prefix :  <http://example.org/ex#> .\n"
										":a :b \"\"\"John said: \"Hello World!\\\"\"\"\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/ex#a> <http://example.org/ex#b> \"John said: \\\"Hello World!\\\"\" .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_22) {

		TurtleStringParser turtleParser("@prefix : <http://example.org#> .\n"
										":a :b true .\n"
										":c :d false .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org#a> <http://example.org#b> \"true\"^^<http://www.w3.org/2001/XMLSchema#boolean> .\n"
				"<http://example.org#c> <http://example.org#d> \"false\"^^<http://www.w3.org/2001/XMLSchema#boolean> .");
	}

	TEST(TurtleOfficialEvaluationTests, DISABLED_turtle_subm_23) {

		TurtleStringParser turtleParser("# comment test\n"
										"@prefix : <http://example.org/#> .\n"
										":a :b :c . # end of line comment\n"
										":d # ignore me\n"
										"  :e # and me\n"
										"      :f # and me\n"
										"        .\n"
										":g :h #ignore me\n"
										"     :i,  # and me\n"
										"     :j . # and me\n"
										"\n"
										":k :l :m ; #ignore me\n"
										"   :n :o ; # and me\n"
										"   :p :q . # and me");
		//bool a = turtleParser.isContentParsable();
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/#a> <http://example.org/#b> <http://example.org/#c> .\n"
				"<http://example.org/#d> <http://example.org/#e> <http://example.org/#f> .\n"
				"<http://example.org/#g> <http://example.org/#h> <http://example.org/#i> .\n"
				"<http://example.org/#g> <http://example.org/#h> <http://example.org/#j> .\n"
				"<http://example.org/#k> <http://example.org/#l> <http://example.org/#m> .\n"
				"<http://example.org/#k> <http://example.org/#n> <http://example.org/#o> .\n"
				"<http://example.org/#k> <http://example.org/#p> <http://example.org/#q> .");
	}

	TEST(TurtleOfficialEvaluationTests, DISABLED_turtle_subm_24) {

		TurtleStringParser turtleParser("# comment line with no final newline test\n"
										"@prefix : <http://example.org/#> .\n"
										":a :b :c .\n"
										"#foo");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/#a> <http://example.org/#b> <http://example.org/#c> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_25) {

		TurtleStringParser turtleParser("@prefix foo: <http://example.org/foo#>  .\n"
										"@prefix foo: <http://example.org/bar#>  .\n"
										"\n"
										"foo:blah foo:blah foo:blah .\n"
										"");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/bar#blah> <http://example.org/bar#blah> <http://example.org/bar#blah> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_26) {

		TurtleStringParser turtleParser(
				"<http://example.org/foo> <http://example.org/bar> \"2.345\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.000000000\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.3\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.2345678901234567890123457890\"^^<http://www.w3.org/2001/XMLSchema#decimal> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/foo> <http://example.org/bar> \"2.345\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.000000000\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.3\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.234000000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.2340000000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"2.23400000000000000000005\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
				"<http://example.org/foo> <http://example.org/bar> \"1.2345678901234567890123457890\"^^<http://www.w3.org/2001/XMLSchema#decimal> .");
	}

	TEST(TurtleOfficialEvaluationTests, turtle_subm_27) {

		TurtleStringParser turtleParser(
				"# In-scope base URI is <http://www.w3.org/2013/TurtleTests/turtle-subm-27.ttl> at this point\n"
				"<a1> <b1> <c1> .\n"
				"@base <http://example.org/ns/> .\n"
				"# In-scope base URI is http://example.org/ns/ at this point\n"
				"<a2> <http://example.org/ns/b2> <c2> .\n"
				"@base <foo/> .\n"
				"# In-scope base URI is http://example.org/ns/foo/ at this point\n"
				"<a3> <b3> <c3> .\n"
				"@prefix : <bar#> .\n"
				":a4 :b4 :c4 .\n"
				"@prefix : <http://example.org/ns2#> .\n"
				":a5 :b5 :c5 .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://www.w3.org/2013/TurtleTests/a1> <http://www.w3.org/2013/TurtleTests/b1> <http://www.w3.org/2013/TurtleTests/c1> .\n"
				"<http://example.org/ns/a2> <http://example.org/ns/b2> <http://example.org/ns/c2> .\n"
				"<http://example.org/ns/foo/a3> <http://example.org/ns/foo/b3> <http://example.org/ns/foo/c3> .\n"
				"<http://example.org/ns/foo/bar#a4> <http://example.org/ns/foo/bar#b4> <http://example.org/ns/foo/bar#c4> .\n"
				"<http://example.org/ns2#a5> <http://example.org/ns2#b5> <http://example.org/ns2#c5> .");
	}

	TEST(TurtleOfficialEvaluationTests, two_LITERAL_LONG2s) {

		TurtleStringParser turtleParser("# Test long literal twice to ensure it does not over-quote\n"
										"@prefix :  <http://example.org/ex#> .\n"
										":a :b \"\"\"first long literal\"\"\" .\n"
										":c :d \"\"\"second long literal\"\"\" .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser(
				"<http://example.org/ex#a> <http://example.org/ex#b> \"first long literal\" .\n"
				"<http://example.org/ex#c> <http://example.org/ex#d> \"second long literal\" .");
	}

	TEST(TurtleOfficialEvaluationTests, underscore_in_localName) {

		TurtleStringParser turtleParser("@prefix p: <http://a.example/>.\n"
										"p:s_ <http://a.example/p> <http://a.example/o> .");
		auto it = turtleParser.begin();
		TurtleStringParser nTriplesParser("<http://a.example/s_> <http://a.example/p> <http://a.example/o> .");
	}
}// namespace Dice::tests::rdf_parser::turtle_official_evaluation_tests