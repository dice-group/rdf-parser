#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/StringParser.hpp>


TEST(TurtleOfficialPositiveTests, anonymous_blank_node_object) {

   StringParser parser("<http://a.example/s> <http://a.example/p> [] .");

}

TEST(TurtleOfficialPositiveTests, anonymous_blank_node_subject) {

   StringParser parser("[] <http://a.example/p> <http://a.example/o> .");

}


TEST(TurtleOfficialPositiveTests, bareword_integer) {

   StringParser parser("<http://a.example/s> <http://a.example/p> 1 .");
}

TEST(TurtleOfficialPositiveTests, comment_following_localName) {

   StringParser parser("@prefix p: <http://a.example/> .\n"
                          "<http://a.example/s> <http://a.example/p> p:o#comment\n"
                          ".");
}

TEST(TurtleOfficialPositiveTests, default_namespace_IRI) {

   StringParser parser("@prefix : <http://a.example/>.\n"
                          ":s <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, IRI_spo) {

   StringParser parser("<http://a.example/s> <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, IRI_subject) {

   StringParser parser("<http://a.example/s> <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, IRI_with_eight_digit_numeric_escape) {

   StringParser parser(
            "<http://a.example/\\U00000073> <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, IRI_with_four_digit_numeric_escape) {

   StringParser parser("<http://a.example/\\u0073> <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_leading_digit) {

   StringParser parser("<http://a.example/s> <http://a.example/p> _:0 .");

}

TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_leading_underscore) {

   StringParser parser("<http://a.example/s> <http://a.example/p> _:_ .");

}

TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_non_leading_extras) {

   StringParser parser("<http://a.example/s> <http://a.example/p> _:a·̀ͯ‿.⁀ .");

}

/*TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_PN_CHARS_BASE_character_boundaries) {
    
   StringParserparser(
            "<http://a.example/s> <http://a.example/p> _:AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD .");

}*/

TEST(TurtleOfficialPositiveTests, langtagged_LONG) {

   StringParser parser("<http://a.example/s> <http://a.example/p> \"\"\"chat\"\"\"@en .");

}

TEST(TurtleOfficialPositiveTests, LITERAL1_all_controls) {

   StringParser parser(
            "<http://a.example/s> <http://a.example/p> \"\\u0000\\u0001\\u0002\\u0003\\u0004\\u0005\\u0006\\u0007\\u0008\\t\\u000B\\u000C\\u000E\\u000F\\u0010\\u0011\\u0012\\u0013\\u0014\\u0015\\u0016\\u0017\\u0018\\u0019\\u001A\\u001B\\u001C\\u001D\\u001E\\u001F\" .");
}

/*TEST(TurtleOfficialPositiveTests, LITERAL1_with_UTF8_boundaries) {
    
   StringParserparser(
            "<http://a.example/s> <http://a.example/p> '\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD' .");

}*/

TEST(TurtleOfficialPositiveTests, LITERAL2) {

   StringParser parser("<http://a.example/s> <http://a.example/p> \"x\" .");

}

TEST(TurtleOfficialPositiveTests, LITERAL2_ascii_boundaries) {

   StringParser parser(
            "<http://a.example/s> <http://a.example/p> \"\\u0000\\t\\u000B\\u000C\\u000E!#[]\\u007F\" .");

}

TEST(TurtleOfficialPositiveTests, LITERAL2_with_UTF8_boundaries) {

   StringParser parser(
            "<http://a.example/s> <http://a.example/p> \" \t\u000B\f\u000E!#[]\u007F\" .");

}

TEST(TurtleOfficialPositiveTests, LITERAL_LONG1) {

   StringParser parser("<http://a.example/s> <http://a.example/p> '''x''' .");

}
/*
TEST(TurtleOfficialPositiveTests, LITERAL_LONG1_with_UTF8_boundaries) {
    
   StringParserparser(
            "<http://a.example/s> <http://a.example/p> '''\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD''' .");

}*/

TEST(TurtleOfficialPositiveTests, LITERAL_LONG2) {

   StringParser parser("<http://a.example/s> <http://a.example/p> \"\"\"x\"\"\" .");

}

/*TEST(TurtleOfficialPositiveTests, LITERAL_LONG2_with_UTF8_boundaries) {
    
   StringParserparser("<http://a.example/s> <http://a.example/p> \"\"\"\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD\"\"\" .");

}*/
TEST(TurtleOfficialPositiveTests, literal_with_escaped_BACKSPACE) {

   StringParser parser("<http://a.example/s> <http://a.example/p> '\\b' .");

}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_CARRIAGE_RETURN) {

   StringParser parser("<http://a.example/s> <http://a.example/p> '\\r' .");

}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_CHARACTER_TABULATION) {

   StringParser parser("<http://a.example/s> <http://a.example/p> '\\t' .");

}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_FORM_FEED) {

   StringParser parser("<http://a.example/s> <http://a.example/p> '\\f' .");
}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_LINE_FEED) {

   StringParser parser("<http://a.example/s> <http://a.example/p> '\\n' .");
}

TEST(TurtleOfficialPositiveTests, literal_with_numeric_escape8) {

   StringParser parser("<http://a.example/s> <http://a.example/p> '\\U0000006F' .");
}

TEST(TurtleOfficialPositiveTests, LITERAL_with_UTF8_boundaries) {

   StringParser parser(
            "<http://a.example/s> <http://a.example/p> \"\\u0080\\u07FF\\u0800\\u0FFF\\u1000\\uCFFF\\uD000\\uD7FF\\uE000\\uFFFD\\U00010000\\U0003FFFD\\U00040000\\U000FFFFD\\U00100000\\U0010FFFD\" .");

}

TEST(TurtleOfficialPositiveTests, old_style_base) {

   StringParser parser("@base <http://a.example/>.\n"
                          "<s> <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, old_style_prefix) {

   StringParser parser("@prefix p: <http://a.example/>.\n"
                          "p:s <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, prefix_only_IRI) {

   StringParser parser("@prefix p: <http://a.example/s>.\n"
                          "p: <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, prefix_with_non_leading_extras) {

   StringParser parser("@prefix a·̀ͯ‿.⁀: <http://a.example/>.\n"
                          "a·̀ͯ‿.⁀:s <http://a.example/p> <http://a.example/o> .");
}

/*
TEST(TurtleOfficialPositiveTests, prefix_with_PN_CHARS_BASE_character_boundaries) {
    
   StringParserparser("@prefix AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD:o .");
}
*/

TEST(TurtleOfficialPositiveTests, prefixed_IRI_object) {

   StringParser parser("@prefix p: <http://a.example/>.\n"
                          "<http://a.example/s> <http://a.example/p> p:o .");
}

TEST(TurtleOfficialPositiveTests, prefixed_IRI_predicate) {

   StringParser parser("@prefix p: <http://a.example/>.\n"
                          "<http://a.example/s> p:p <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, prefixed_name_datatype) {

   StringParser parser("@prefix xsd: <http://www.w3.org/2001/XMLSchema#> .\n"
                          "<http://a.example/s> <http://a.example/p> \"1\"^^xsd:integer .");
}

TEST(TurtleOfficialPositiveTests, repeated_semis_at_end) {

   StringParser parser(
            "<http://a.example/s> <http://a.example/p1> <http://a.example/o1>;; <http://a.example/p2> <http://a.example/o2> .");
}

TEST(TurtleOfficialPositiveTests, sole_blankNodePropertyList) {

   StringParser parser("[ <http://a.example/p> <http://a.example/o> ] .");
}

TEST(TurtleOfficialPositiveTests, SPARQL_style_base) {

   StringParser parser("BASE <http://a.example/>\n"
                          "<s> <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, SPARQL_style_prefix) {

   StringParser parser("PREFIX p: <http://a.example/>\n"
                          "p:s <http://a.example/p> <http://a.example/o> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_01) {

   StringParser parser("@base <http://www.w3.org/2013/TurtleTests/> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_02) {

   StringParser parser("BASE <http://www.w3.org/2013/TurtleTests/>");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_03) {

   StringParser parser("@base <http://www.w3.org/2013/TurtleTests/> .\n"
                          "<s> <p> <o> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_04) {

   StringParser parser("base <http://www.w3.org/2013/TurtleTests/>\n"
                          "<s> <p> <o> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_blank_label) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "_:0b :p :o . # Starts with digit\n"
                          "_:_b :p :o . # Starts with underscore\n"
                          "_:b.0 :p :o . # Contains dot, ends with digit");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_blank_label_TEST) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "_:0b :p :o . # Starts with digit\n"
                          "_:_b :p :o . # Starts with underscore\n"
                          "_:b.0 :p :o . # Contains dot, ends with digit");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_01) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "[] :p :o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_02) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p [] .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_03) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p [ :q :o ] .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_04) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p [ :q1 :o1 ; :q2 :o2 ] .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_05) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "[ :q1 :o1 ; :q2 :o2 ] :p :o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_06) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "_:a  :p :o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_07) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s  :p _:a .\n"
                          "_:a  :p :o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_08) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "[ :p  :o ] .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_09) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "[ :p  :o1,:2 ] .\n"
                          ":s :p :o  .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_10) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "\n"
                          ":s1 :p :o .\n"
                          "[ :p1  :o1 ; :p2 :o2 ] .\n"
                          ":s2 :p :o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_datatypes_01) {

   StringParser parser("@prefix xsd:     <http://www.w3.org/2001/XMLSchema#> .\n"
                          "<s> <p> \"123\"^^xsd:byte .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_datatypes_02) {

   StringParser parser("@prefix rdf:     <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                          "@prefix xsd:     <http://www.w3.org/2001/XMLSchema#> .\n"
                          "<s> <p> \"123\"^^xsd:string .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_file_01) {

   StringParser parser("");
}

//TEST(TurtleOfficialPositiveTests, turtle_syntax_file_02) {
//
//    //StringParser<> parser("#Empty file.");
//    StringParser<seq<Grammer::ignored, eof>> parser("#Empty file.");
//}

TEST(TurtleOfficialPositiveTests, turtle_syntax_file_03) {

   StringParser parser("#One comment, one empty line.\n"
                          "");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_01) {

   StringParser parser("<s> <p> true .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_02) {

   StringParser parser("<s> <p> false .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_03) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s a :C .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_01) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p () .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_02) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p (1 \"2\" :o) .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_03) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "(1) :p (1) .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_04) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "(()) :p (()) .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_05) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "(1 2 (1 2)) :p (( \"a\") \"b\" :o) .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_ln_colons) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s:1 :p:1 :o:1 .\n"
                          ":s::2 :p::2 :o::2 .\n"
                          ":3:s :3:p :3 .\n"
                          "::s ::p ::o .\n"
                          "::s: ::p: ::o: .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_ln_dots) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s.1 :p.1 :o.1 .\n"
                          ":s..2 :p..2 :o..2.\n"
                          ":3.s :3.p :3.");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_ns_dots) {

   StringParser parser("@prefix e.g: <http://www.w3.org/2013/TurtleTests/> .\n"
                          "e.g:s e.g:p e.g:o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_01) {

   StringParser parser("<s> <p> 123 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_02) {

   StringParser parser("<s> <p> -123 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_03) {

   StringParser parser("<s> <p> +123 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_04) {

   StringParser parser("# This is a decimal.\n"
                          "<s> <p> 123.0 . ");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_05) {

   StringParser parser("# This is a decimal.\n"
                          "<s> <p> .1 . ");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_06) {

   StringParser parser("# This is a decimal.\n"
                          "<s> <p> -123.0 . ");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_07) {

   StringParser parser("# This is a decimal.\n"
                          "<s> <p> +123.0 . ");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_08) {

   StringParser parser("# This is an integer\n"
                          "<s> <p> 123.");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_09) {

   StringParser parser("<s> <p> 123.0e1 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_10) {

   StringParser parser("<s> <p> -123e-1 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_11) {

   StringParser parser("<s> <p> 123.E+1 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_01) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p :\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\_\\%AA .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_02) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p :0123\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\_\\%AA123 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_03) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":xyz\\~ :abc\\.:  : .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_01) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_02) {

   StringParser parser("PreFIX : <http://www.w3.org/2013/TurtleTests/>");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_03) {

   StringParser parser("PREFIX : <http://www.w3.org/2013/TurtleTests/>\n"
                          ":s :p :123 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_04) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p :%20 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_05) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ": : : .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_06) {

   StringParser parser("# colon is a legal pname character\n"
                          "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":a:b:c  x:d:e:f :::: .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_07) {

   StringParser parser("# dash is a legal pname character\n"
                          "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                          "x:a-b-c  x:p x:o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_08) {

   StringParser parser("# underscore is a legal pname character\n"
                          "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                          "x:_  x:p_1 x:o .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_09) {

   StringParser parser("# percents\n"
                          "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":a%3E  x:%25 :a%3Eb .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_01) {

   StringParser parser("<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\n\" .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_02) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\u0020b\" .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_03) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\U00000020b\" .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_01) {

   StringParser parser("<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\" .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_02) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@en .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_03) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@en-uk .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_04) {

   StringParser parser("<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string' .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_05) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string'@en .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_06) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string'@en-uk .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_07) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\"\"def''ghi\"\"\" .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_08) {

   StringParser parser("<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\n"
                          "def\"\"\" .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_09) {

   StringParser parser("<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> '''abc\n"
                          "def''' .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_10) {

   StringParser parser("<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\n"
                          "def\"\"\"@en .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_11) {

   StringParser parser("<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> '''abc\n"
                          "def'''@en .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_01) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p :o1 , :o2 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_02) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p1 :o1 ;\n"
                          "   :p2 :o2 .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_03) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p1 :o1 ;\n"
                          "   :p2 :o2 ;\n"
                          "   .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_04) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p1 :o1 ;;\n"
                          "   :p2 :o2 \n"
                          "   .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_05) {

   StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p1 :o1 ;\n"
                          "   :p2 :o2 ;;\n"
                          "   .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_01) {

   StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_02) {

   StringParser parser("# x53 is capital S\n"
                          "<http://www.w3.org/2013/TurtleTests/\\u0053> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_03) {

   StringParser parser("# x53 is capital S\n"
                          "<http://www.w3.org/2013/TurtleTests/\\U00000053> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_04) {

   StringParser parser("# IRI with all chars in it.\n"
                          "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p>\n"
                          "<scheme:!$%25&'()*+,-./0123456789:/@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~?#> .");
}