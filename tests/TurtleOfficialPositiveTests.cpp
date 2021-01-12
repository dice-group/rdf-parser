#include <gtest/gtest.h>

#include <Dice/rdf-parser/Parser/Turtle/Parsers/RdfStringParser.hpp>

namespace Dice::tests::rdf_parser::turtle_official_positive_tests {
	using namespace Dice::rdf_parser::Turtle::parsers;

	TEST(TurtleOfficialPositiveTests, anonymous_blank_node_object) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> [] ."), true);
	}

	TEST(TurtleOfficialPositiveTests, anonymous_blank_node_subject) {

		ASSERT_EQ(RdfStringParser::isParsable("[] <http://a.example/p> <http://a.example/o> ."), true);
	}


	TEST(TurtleOfficialPositiveTests, bareword_integer) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> 1 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, comment_following_localName) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix p: <http://a.example/> .\n"
											  "<http://a.example/s> <http://a.example/p> p:o#comment\n"
											  "."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, default_namespace_IRI) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://a.example/>.\n"
											  ":s <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, IRI_spo) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> <http://a.example/o> ."), true);
	}

	TEST(TurtleOfficialPositiveTests, IRI_subject) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> <http://a.example/o> ."), true);
	}

	TEST(TurtleOfficialPositiveTests, IRI_with_eight_digit_numeric_escape) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://a.example/\\U00000073> <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, IRI_with_four_digit_numeric_escape) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/\\u0073> <http://a.example/p> <http://a.example/o> ."), true);
	}

	TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_leading_digit) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> _:0 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_leading_underscore) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> _:_ ."), true);
	}

	TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_non_leading_extras) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> _:a·̀ͯ‿.⁀ ."), true);
	}

	/*TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_PN_CHARS_BASE_character_boundaries) {

  RdfStringRdfStringParserRdfStringParser(
            "<http://a.example/s> <http://a.example/p> _:AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD ."),true);
   

}*/

	TEST(TurtleOfficialPositiveTests, langtagged_LONG) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> \"\"\"chat\"\"\"@en ."), true);
	}

	TEST(TurtleOfficialPositiveTests, LITERAL1_all_controls) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://a.example/s> <http://a.example/p> \"\\u0000\\u0001\\u0002\\u0003\\u0004\\u0005\\u0006\\u0007\\u0008\\t\\u000B\\u000C\\u000E\\u000F\\u0010\\u0011\\u0012\\u0013\\u0014\\u0015\\u0016\\u0017\\u0018\\u0019\\u001A\\u001B\\u001C\\u001D\\u001E\\u001F\" ."),
				  true);
	}

	/*TEST(TurtleOfficialPositiveTests, LITERAL1_with_UTF8_boundaries) {

  RdfStringRdfStringParserRdfStringParser(
            "<http://a.example/s> <http://a.example/p> '\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD' ."),true);
   

}*/

	TEST(TurtleOfficialPositiveTests, LITERAL2) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> \"x\" ."), true);
	}

	TEST(TurtleOfficialPositiveTests, LITERAL2_ascii_boundaries) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://a.example/s> <http://a.example/p> \"\\u0000\\t\\u000B\\u000C\\u000E!#[]\\u007F\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, LITERAL2_with_UTF8_boundaries) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://a.example/s> <http://a.example/p> \" \t\u000B\f\u000E!#[]\u007F\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, LITERAL_LONG1) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> '''x''' ."), true);
	}
	/*
TEST(TurtleOfficialPositiveTests, LITERAL_LONG1_with_UTF8_boundaries) {

  RdfStringRdfStringParserRdfStringParser(
            "<http://a.example/s> <http://a.example/p> '''\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD''' ."),true);
   

}*/

	TEST(TurtleOfficialPositiveTests, LITERAL_LONG2) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> \"\"\"x\"\"\" ."), true);
	}

	/*TEST(TurtleOfficialPositiveTests, LITERAL_LONG2_with_UTF8_boundaries) {

  RdfStringRdfStringParserRdfStringParser("<http://a.example/s> <http://a.example/p> \"\"\"\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD\"\"\" ."),true);
   

}*/
	TEST(TurtleOfficialPositiveTests, literal_with_escaped_BACKSPACE) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> '\\b' ."), true);
	}

	TEST(TurtleOfficialPositiveTests, literal_with_escaped_CARRIAGE_RETURN) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> '\\r' ."), true);
	}

	TEST(TurtleOfficialPositiveTests, literal_with_escaped_CHARACTER_TABULATION) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> '\\t' ."), true);
	}

	TEST(TurtleOfficialPositiveTests, literal_with_escaped_FORM_FEED) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> '\\f' ."), true);
	}

	TEST(TurtleOfficialPositiveTests, literal_with_escaped_LINE_FEED) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> '\\n' ."), true);
	}

	TEST(TurtleOfficialPositiveTests, literal_with_numeric_escape8) {

		ASSERT_EQ(RdfStringParser::isParsable("<http://a.example/s> <http://a.example/p> '\\U0000006F' ."), true);
	}

	TEST(TurtleOfficialPositiveTests, LITERAL_with_UTF8_boundaries) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://a.example/s> <http://a.example/p> \"\\u0080\\u07FF\\u0800\\u0FFF\\u1000\\uCFFF\\uD000\\uD7FF\\uE000\\uFFFD\\U00010000\\U0003FFFD\\U00040000\\U000FFFFD\\U00100000\\U0010FFFD\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, old_style_base) {

		ASSERT_EQ(RdfStringParser::isParsable("@base <http://a.example/>.\n"
											  "<s> <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, old_style_prefix) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix p: <http://a.example/>.\n"
											  "p:s <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, prefix_only_IRI) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix p: <http://a.example/s>.\n"
											  "p: <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, prefix_with_non_leading_extras) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix a·̀ͯ‿.⁀: <http://a.example/>.\n"
											  "a·̀ͯ‿.⁀:s <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	/*
TEST(TurtleOfficialPositiveTests, prefix_with_PN_CHARS_BASE_character_boundaries) {

  RdfStringRdfStringParserRdfStringParser("@prefix AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD:o ."),true);
   
}
*/

	TEST(TurtleOfficialPositiveTests, prefixed_IRI_object) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix p: <http://a.example/>.\n"
											  "<http://a.example/s> <http://a.example/p> p:o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, prefixed_IRI_predicate) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix p: <http://a.example/>.\n"
											  "<http://a.example/s> p:p <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, prefixed_name_datatype) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix xsd: <http://www.w3.org/2001/XMLSchema#> .\n"
											  "<http://a.example/s> <http://a.example/p> \"1\"^^xsd:integer ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, repeated_semis_at_end) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://a.example/s> <http://a.example/p1> <http://a.example/o1>;; <http://a.example/p2> <http://a.example/o2> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, sole_blankNodePropertyList) {

		ASSERT_EQ(RdfStringParser::isParsable("[ <http://a.example/p> <http://a.example/o> ] ."), true);
	}

	TEST(TurtleOfficialPositiveTests, SPARQL_style_base) {

		ASSERT_EQ(RdfStringParser::isParsable("BASE <http://a.example/>\n"
											  "<s> <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, SPARQL_style_prefix) {

		ASSERT_EQ(RdfStringParser::isParsable("PREFIX p: <http://a.example/>\n"
											  "p:s <http://a.example/p> <http://a.example/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_base_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@base <http://www.w3.org/2013/TurtleTests/> ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_base_02) {

		ASSERT_EQ(RdfStringParser::isParsable("BASE <http://www.w3.org/2013/TurtleTests/>"), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_base_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@base <http://www.w3.org/2013/TurtleTests/> .\n"
											  "<s> <p> <o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_base_04) {

		ASSERT_EQ(RdfStringParser::isParsable("base <http://www.w3.org/2013/TurtleTests/>\n"
											  "<s> <p> <o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, DISABLED_turtle_syntax_blank_label) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "_:0b :p :o . # Starts with digit\n"
											  "_:_b :p :o . # Starts with underscore\n"
											  "_:b.0 :p :o . # Contains dot, ends with digit"),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, DISABLED_turtle_syntax_blank_label_TEST) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "_:0b :p :o . # Starts with digit\n"
											  "_:_b :p :o . # Starts with underscore\n"
											  "_:b.0 :p :o . # Contains dot, ends with digit"),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "[] :p :o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_02) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p [] ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p [ :q :o ] ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_04) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p [ :q1 :o1 ; :q2 :o2 ] ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_05) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "[ :q1 :o1 ; :q2 :o2 ] :p :o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_06) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "_:a  :p :o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_07) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s  :p _:a .\n"
											  "_:a  :p :o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_08) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "[ :p  :o ] ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_09) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "[ :p  :o1,:2 ] .\n"
											  ":s :p :o  ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_10) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "\n"
											  ":s1 :p :o .\n"
											  "[ :p1  :o1 ; :p2 :o2 ] .\n"
											  ":s2 :p :o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_datatypes_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix xsd:     <http://www.w3.org/2001/XMLSchema#> .\n"
											  "<s> <p> \"123\"^^xsd:byte ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_datatypes_02) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix rdf:     <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
											  "@prefix xsd:     <http://www.w3.org/2001/XMLSchema#> .\n"
											  "<s> <p> \"123\"^^xsd:string ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, DISABLED_turtle_syntax_file_01) {

		ASSERT_EQ(RdfStringParser::isParsable(""), true);
	}

	TEST(TurtleOfficialPositiveTests, DISABLED_turtle_syntax_file_02) {

		ASSERT_EQ(RdfStringParser::isParsable("#Empty file."), true);
	}

	TEST(TurtleOfficialPositiveTests, DISABLED_turtle_syntax_file_03) {

		ASSERT_EQ(RdfStringParser::isParsable("#One comment, one empty line.\n"
											  ""),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_01) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> true ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_02) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> false ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s a :C ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p () ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_02) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p (1 \"2\" :o) ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "(1) :p (1) ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_04) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "(()) :p (()) ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_05) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "(1 2 (1 2)) :p (( \"a\") \"b\" :o) ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_ln_colons) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s:1 :p:1 :o:1 .\n"
											  ":s::2 :p::2 :o::2 .\n"
											  ":3:s :3:p :3 .\n"
											  "::s ::p ::o .\n"
											  "::s: ::p: ::o: ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_ln_dots) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s.1 :p.1 :o.1 .\n"
											  ":s..2 :p..2 :o..2.\n"
											  ":3.s :3.p :3."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_ns_dots) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix e.g: <http://www.w3.org/2013/TurtleTests/> .\n"
											  "e.g:s e.g:p e.g:o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_01) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> 123 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_02) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> -123 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_03) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> +123 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_04) {

		ASSERT_EQ(RdfStringParser::isParsable("# This is a decimal.\n"
											  "<s> <p> 123.0 . "),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_05) {

		ASSERT_EQ(RdfStringParser::isParsable("# This is a decimal.\n"
											  "<s> <p> .1 . "),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_06) {

		ASSERT_EQ(RdfStringParser::isParsable("# This is a decimal.\n"
											  "<s> <p> -123.0 . "),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_07) {

		ASSERT_EQ(RdfStringParser::isParsable("# This is a decimal.\n"
											  "<s> <p> +123.0 . "),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_08) {

		ASSERT_EQ(RdfStringParser::isParsable("# This is an integer\n"
											  "<s> <p> 123."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_09) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> 123.0e1 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_10) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> -123e-1 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_number_11) {

		ASSERT_EQ(RdfStringParser::isParsable("<s> <p> 123.E+1 ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p :\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\_\\%AA ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_02) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p :0123\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\_\\%AA123 ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":xyz\\~ :abc\\.:  : ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> ."), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_02) {

		ASSERT_EQ(RdfStringParser::isParsable("PreFIX : <http://www.w3.org/2013/TurtleTests/>"), true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_03) {

		ASSERT_EQ(RdfStringParser::isParsable("PREFIX : <http://www.w3.org/2013/TurtleTests/>\n"
											  ":s :p :123 ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_04) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p :%20 ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_05) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ": : : ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_06) {

		ASSERT_EQ(RdfStringParser::isParsable("# colon is a legal pname character\n"
											  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":a:b:c  x:d:e:f :::: ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_07) {

		ASSERT_EQ(RdfStringParser::isParsable("# dash is a legal pname character\n"
											  "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
											  "x:a-b-c  x:p x:o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_08) {

		ASSERT_EQ(RdfStringParser::isParsable("# underscore is a legal pname character\n"
											  "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
											  "x:_  x:p_1 x:o ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_09) {

		ASSERT_EQ(RdfStringParser::isParsable("# percents\n"
											  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":a%3E  x:%25 :a%3Eb ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\n\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\u0020b\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\U00000020b\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@en ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@en-uk ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_04) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string' ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_05) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string'@en ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_06) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string'@en-uk ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_07) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\"\"def''ghi\"\"\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_08) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\n"
						  "def\"\"\" ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_09) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> '''abc\n"
						  "def''' ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_10) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\n"
						  "def\"\"\"@en ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_string_11) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> '''abc\n"
						  "def'''@en ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p :o1 , :o2 ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_02) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p1 :o1 ;\n"
											  "   :p2 :o2 ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p1 :o1 ;\n"
											  "   :p2 :o2 ;\n"
											  "   ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_04) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p1 :o1 ;;\n"
											  "   :p2 :o2 \n"
											  "   ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_05) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p1 :o1 ;\n"
											  "   :p2 :o2 ;;\n"
											  "   ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_02) {

		ASSERT_EQ(RdfStringParser::isParsable("# x53 is capital S\n"
											  "<http://www.w3.org/2013/TurtleTests/\\u0053> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_03) {

		ASSERT_EQ(RdfStringParser::isParsable("# x53 is capital S\n"
											  "<http://www.w3.org/2013/TurtleTests/\\U00000053> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  true);
	}

	TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_04) {

		ASSERT_EQ(RdfStringParser::isParsable("# IRI with all chars in it.\n"
											  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p>\n"
											  "<scheme:!$%25&'()*+,-./0123456789:/@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~?#> ."),
				  true);
	}
}// namespace Dice::tests::rdf_parser::turtle_official_positive_tests