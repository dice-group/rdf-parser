#include <gtest/gtest.h>

#include <Dice/rdf-parser/Parser/Turtle/Parsers/RdfStringParser.hpp>

namespace Dice::tests::rdf_parser::turtle_official_negative_tests {
	using namespace Dice::rdf_parser::Turtle::parsers;

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@base ."), false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@BASE <http://www.w3.org/2013/TurtleTests/> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "BASE <http://www.w3.org/2013/TurtleTests/> .\n"
						  "<s> <p> <o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_blank_label_dot_end) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "_:b1. :p :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_esc_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\zb\" ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_esc_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\uWXYZ\" ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_esc_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\U0000WXYZ\" ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_esc_04) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\U0000WXYZ\" ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s A :C ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_02) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "a :p :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p a ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_04) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "true :p :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_05) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s true :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_lang_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@1 ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_LITERAL2_with_langtag_and_datatype) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://example.org/resource> <http://example.org#pred> \"value\"@en^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#XMLLiteral> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ln_dash_start) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p :-o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ln_escape) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p :o%2 ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_ln_escape_start) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p :%2o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_missing_ns_dot_end) {

		ASSERT_EQ(RdfStringParser::isParsable("valid:s valid:p invalid.:o ."), false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_missing_ns_dot_start) {

		ASSERT_EQ(RdfStringParser::isParsable(".undefined:s .undefined:p .undefined:o ."), false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  "\n"
						  "{ :a :q :c . } :p :z .\n"
						  ""),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_02) {

		ASSERT_EQ(RdfStringParser::isParsable("# = is not Turtle\n"
											  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "\n"
											  ":a = :b ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  "@prefix ns: <http://www.w3.org/2013/TurtleTests/p#> .\n"
						  "\n"
						  ":x.\n"
						  "  ns:p.\n"
						  "    ns:q :p :z ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_04) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  "@prefix ns: <http://www.w3.org/2013/TurtleTests/p#> .\n"
						  "\n"
						  ":x^ns:p :p :z ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_05) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  "\n"
						  ":z is :p of :x ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_06) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  "\n"
						  ":a.:b.:c ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_07) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@keywords a .\n"
						  "x a Item ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_08) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@keywords a .\n"
						  "x a Item ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_09) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":s => :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_10) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":s <= :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_11) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  "@forSome :x ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_12) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  "@forAll :x ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_13) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@keywords .\n"
						  "x @a Item ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ns_dot_end) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix eg. : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "eg.:s eg.:p eg.:o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ns_dot_start) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix .eg : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ".eg:s .eg:p .eg:o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123.abc ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123e ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123abc ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_04) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 0x123 ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_05) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> +-1 ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_number_dot_in_anon) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  "\n"
											  ":s\n"
											  "\t:p [\n"
											  "\t\t:p1 27.\n"
											  "\t] ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":a~b :p :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":a%2 :p :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":a\\u0039 :p :o ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_prefix_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  ":s <http://www.w3.org/2013/TurtleTests/p> \"x\" ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_prefix_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix rdf:     <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
						  "<http://www.w3.org/2013/TurtleTests/s> rdf:type :C ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix ex: ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_04) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix <http://www.w3.org/2013/TurtleTests/> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_05) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix x <http://www.w3.org/2013/TurtleTests/> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_01) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p \"abc' ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_02) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p 'abc\" ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_03) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p '''abc' ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_04) {

		ASSERT_EQ(RdfStringParser::isParsable("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
											  ":s :p \"\"\"abc''' ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_05) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":s :p \"\"\"abc\n"
						  "def"),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_06) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":s :p \"\"\"abc\"\"\"\"@en ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_07) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
						  ":s :p '''abc''''@en ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "{ <http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> }"),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> = <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> <http://www.w3.org/2013/TurtleTests/g> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_04) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "\"hello\" <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_05) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> \"hello\" <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_06) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> [] <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_07) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> _:p <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_08) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o>"),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_09) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> . ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_10) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> . .\n"
						  "<http://www.w3.org/2013/TurtleTests/s1> <http://www.w3.org/2013/TurtleTests/p1> <http://www.w3.org/2013/TurtleTests/o1> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_11) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ;"),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_12) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> "),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_13) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> "),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_14) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "\"abc\" <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/p>  ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_15) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> \"abc\" <http://www.w3.org/2013/TurtleTests/p>  ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_16) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> [] <http://www.w3.org/2013/TurtleTests/p>  ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_17) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/s> _:a <http://www.w3.org/2013/TurtleTests/p>  ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_01) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/ space> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_uri_02) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/\\u00ZZ11> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_uri_03) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/\\U00ZZ1111> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_04) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/\\n> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}

	TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_05) {

		ASSERT_EQ(RdfStringParser::isParsable(
						  "<http://www.w3.org/2013/TurtleTests/\\/> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ."),
				  false);
	}
}// namespace Dice::tests::rdf_parser::turtle_official_negative_tests