#include <gtest/gtest.h>
#include <Dice/rdf_parser/TurtleParser.hpp>


TEST(TurtleOfficialPositiveTests, anonymous_blank_node_object) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> [] .");
    ASSERT_EQ(parser.isContentParsable(), true);


}

TEST(TurtleOfficialPositiveTests, anonymous_blank_node_subject) {

    TurtleParser<StringParser> parser("[] <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}


TEST(TurtleOfficialPositiveTests, bareword_integer) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> 1 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, comment_following_localName) {

    TurtleParser<StringParser> parser("@prefix p: <http://a.example/> .\n"
                                      "<http://a.example/s> <http://a.example/p> p:o#comment\n"
                                      ".");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, default_namespace_IRI) {

    TurtleParser<StringParser> parser("@prefix : <http://a.example/>.\n"
                                      ":s <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, IRI_spo) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, IRI_subject) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, IRI_with_eight_digit_numeric_escape) {

    TurtleParser<StringParser> parser(
            "<http://a.example/\\U00000073> <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, IRI_with_four_digit_numeric_escape) {

    TurtleParser<StringParser> parser("<http://a.example/\\u0073> <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_leading_digit) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> _:0 .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_leading_underscore) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> _:_ .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_non_leading_extras) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> _:a·̀ͯ‿.⁀ .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

/*TEST(TurtleOfficialPositiveTests, labeled_blank_node_with_PN_CHARS_BASE_character_boundaries) {
    
   TurtleParser<StringParser>parser(
            "<http://a.example/s> <http://a.example/p> _:AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD .");
   ASSERT_EQ(parser.isContentParsable(), true);

}*/

TEST(TurtleOfficialPositiveTests, langtagged_LONG) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> \"\"\"chat\"\"\"@en .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, LITERAL1_all_controls) {

    TurtleParser<StringParser> parser(
            "<http://a.example/s> <http://a.example/p> \"\\u0000\\u0001\\u0002\\u0003\\u0004\\u0005\\u0006\\u0007\\u0008\\t\\u000B\\u000C\\u000E\\u000F\\u0010\\u0011\\u0012\\u0013\\u0014\\u0015\\u0016\\u0017\\u0018\\u0019\\u001A\\u001B\\u001C\\u001D\\u001E\\u001F\" .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

/*TEST(TurtleOfficialPositiveTests, LITERAL1_with_UTF8_boundaries) {
    
   TurtleParser<StringParser>parser(
            "<http://a.example/s> <http://a.example/p> '\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD' .");
   ASSERT_EQ(parser.isContentParsable(), true);

}*/

TEST(TurtleOfficialPositiveTests, LITERAL2) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> \"x\" .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, LITERAL2_ascii_boundaries) {

    TurtleParser<StringParser> parser(
            "<http://a.example/s> <http://a.example/p> \"\\u0000\\t\\u000B\\u000C\\u000E!#[]\\u007F\" .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, LITERAL2_with_UTF8_boundaries) {

    TurtleParser<StringParser> parser(
            "<http://a.example/s> <http://a.example/p> \" \t\u000B\f\u000E!#[]\u007F\" .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, LITERAL_LONG1) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> '''x''' .");
    ASSERT_EQ(parser.isContentParsable(), true);

}
/*
TEST(TurtleOfficialPositiveTests, LITERAL_LONG1_with_UTF8_boundaries) {
    
   TurtleParser<StringParser>parser(
            "<http://a.example/s> <http://a.example/p> '''\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD''' .");
   ASSERT_EQ(parser.isContentParsable(), true);

}*/

TEST(TurtleOfficialPositiveTests, LITERAL_LONG2) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> \"\"\"x\"\"\" .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

/*TEST(TurtleOfficialPositiveTests, LITERAL_LONG2_with_UTF8_boundaries) {
    
   TurtleParser<StringParser>parser("<http://a.example/s> <http://a.example/p> \"\"\"\u0080\u07FFࠀ\u0FFFက쿿퀀\uD7FF\uE000�\uD800\uDC00\uD8BF\uDFFD\uD8C0\uDC00\uDBBF\uDFFD\uDBC0\uDC00\uDBFF\uDFFD\"\"\" .");
   ASSERT_EQ(parser.isContentParsable(), true);

}*/
TEST(TurtleOfficialPositiveTests, literal_with_escaped_BACKSPACE) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> '\\b' .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_CARRIAGE_RETURN) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> '\\r' .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_CHARACTER_TABULATION) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> '\\t' .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_FORM_FEED) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> '\\f' .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, literal_with_escaped_LINE_FEED) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> '\\n' .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, literal_with_numeric_escape8) {

    TurtleParser<StringParser> parser("<http://a.example/s> <http://a.example/p> '\\U0000006F' .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, LITERAL_with_UTF8_boundaries) {

    TurtleParser<StringParser> parser(
            "<http://a.example/s> <http://a.example/p> \"\\u0080\\u07FF\\u0800\\u0FFF\\u1000\\uCFFF\\uD000\\uD7FF\\uE000\\uFFFD\\U00010000\\U0003FFFD\\U00040000\\U000FFFFD\\U00100000\\U0010FFFD\" .");
    ASSERT_EQ(parser.isContentParsable(), true);

}

TEST(TurtleOfficialPositiveTests, old_style_base) {

    TurtleParser<StringParser> parser("@base <http://a.example/>.\n"
                                      "<s> <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, old_style_prefix) {

    TurtleParser<StringParser> parser("@prefix p: <http://a.example/>.\n"
                                      "p:s <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, prefix_only_IRI) {

    TurtleParser<StringParser> parser("@prefix p: <http://a.example/s>.\n"
                                      "p: <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, prefix_with_non_leading_extras) {

    TurtleParser<StringParser> parser("@prefix a·̀ͯ‿.⁀: <http://a.example/>.\n"
                                      "a·̀ͯ‿.⁀:s <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

/*
TEST(TurtleOfficialPositiveTests, prefix_with_PN_CHARS_BASE_character_boundaries) {
    
   TurtleParser<StringParser>parser("@prefix AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF豈\uFDCFﷰ�\uD800\uDC00\uDB7F\uDFFD:o .");
   ASSERT_EQ(parser.isContentParsable(), true);
}
*/

TEST(TurtleOfficialPositiveTests, prefixed_IRI_object) {

    TurtleParser<StringParser> parser("@prefix p: <http://a.example/>.\n"
                                      "<http://a.example/s> <http://a.example/p> p:o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, prefixed_IRI_predicate) {

    TurtleParser<StringParser> parser("@prefix p: <http://a.example/>.\n"
                                      "<http://a.example/s> p:p <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, prefixed_name_datatype) {

    TurtleParser<StringParser> parser("@prefix xsd: <http://www.w3.org/2001/XMLSchema#> .\n"
                                      "<http://a.example/s> <http://a.example/p> \"1\"^^xsd:integer .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, repeated_semis_at_end) {

    TurtleParser<StringParser> parser(
            "<http://a.example/s> <http://a.example/p1> <http://a.example/o1>;; <http://a.example/p2> <http://a.example/o2> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, sole_blankNodePropertyList) {

    TurtleParser<StringParser> parser("[ <http://a.example/p> <http://a.example/o> ] .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, SPARQL_style_base) {

    TurtleParser<StringParser> parser("BASE <http://a.example/>\n"
                                      "<s> <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, SPARQL_style_prefix) {

    TurtleParser<StringParser> parser("PREFIX p: <http://a.example/>\n"
                                      "p:s <http://a.example/p> <http://a.example/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_01) {

    TurtleParser<StringParser> parser("@base <http://www.w3.org/2013/TurtleTests/> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_02) {

    TurtleParser<StringParser> parser("BASE <http://www.w3.org/2013/TurtleTests/>");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_03) {

    TurtleParser<StringParser> parser("@base <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "<s> <p> <o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_base_04) {

    TurtleParser<StringParser> parser("base <http://www.w3.org/2013/TurtleTests/>\n"
                                      "<s> <p> <o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_blank_label) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "_:0b :p :o . # Starts with digit\n"
                                      "_:_b :p :o . # Starts with underscore\n"
                                      "_:b.0 :p :o . # Contains dot, ends with digit");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_blank_label_TEST) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "_:0b :p :o . # Starts with digit\n"
                                      "_:_b :p :o . # Starts with underscore\n"
                                      "_:b.0 :p :o . # Contains dot, ends with digit");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_01) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "[] :p :o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_02) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p [] .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_03) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p [ :q :o ] .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_04) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p [ :q1 :o1 ; :q2 :o2 ] .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_05) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "[ :q1 :o1 ; :q2 :o2 ] :p :o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_06) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "_:a  :p :o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_07) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s  :p _:a .\n"
                                      "_:a  :p :o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_08) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "[ :p  :o ] .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_09) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "[ :p  :o1,:2 ] .\n"
                                      ":s :p :o  .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_bnode_10) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "\n"
                                      ":s1 :p :o .\n"
                                      "[ :p1  :o1 ; :p2 :o2 ] .\n"
                                      ":s2 :p :o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_datatypes_01) {

    TurtleParser<StringParser> parser("@prefix xsd:     <http://www.w3.org/2001/XMLSchema#> .\n"
                                      "<s> <p> \"123\"^^xsd:byte .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_datatypes_02) {

    TurtleParser<StringParser> parser("@prefix rdf:     <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                      "@prefix xsd:     <http://www.w3.org/2001/XMLSchema#> .\n"
                                      "<s> <p> \"123\"^^xsd:string .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_file_01) {

    TurtleParser<StringParser> parser("");
    ASSERT_EQ(parser.isContentParsable(), true);
}

//TEST(TurtleOfficialPositiveTests, turtle_syntax_file_02) {
//
//    //TurtleParser<StringParser><> parser("#Empty file.");
//   ASSERT_EQ(parser.isContentParsable(), true);
//    TurtleParser<StringParser><seq<Grammer::ignored, eof>> parser("#Empty file.");
//   ASSERT_EQ(parser.isContentParsable(), true);
//}

TEST(TurtleOfficialPositiveTests, turtle_syntax_file_03) {

    TurtleParser<StringParser> parser("#One comment, one empty line.\n"
                                      "");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_01) {

    TurtleParser<StringParser> parser("<s> <p> true .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_02) {

    TurtleParser<StringParser> parser("<s> <p> false .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_kw_03) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s a :C .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_01) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p () .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_02) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p (1 \"2\" :o) .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_03) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "(1) :p (1) .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_04) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "(()) :p (()) .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_lists_05) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "(1 2 (1 2)) :p (( \"a\") \"b\" :o) .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_ln_colons) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s:1 :p:1 :o:1 .\n"
                                      ":s::2 :p::2 :o::2 .\n"
                                      ":3:s :3:p :3 .\n"
                                      "::s ::p ::o .\n"
                                      "::s: ::p: ::o: .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_ln_dots) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s.1 :p.1 :o.1 .\n"
                                      ":s..2 :p..2 :o..2.\n"
                                      ":3.s :3.p :3.");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_ns_dots) {

    TurtleParser<StringParser> parser("@prefix e.g: <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "e.g:s e.g:p e.g:o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_01) {

    TurtleParser<StringParser> parser("<s> <p> 123 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_02) {

    TurtleParser<StringParser> parser("<s> <p> -123 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_03) {

    TurtleParser<StringParser> parser("<s> <p> +123 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_04) {

    TurtleParser<StringParser> parser("# This is a decimal.\n"
                                      "<s> <p> 123.0 . ");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_05) {

    TurtleParser<StringParser> parser("# This is a decimal.\n"
                                      "<s> <p> .1 . ");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_06) {

    TurtleParser<StringParser> parser("# This is a decimal.\n"
                                      "<s> <p> -123.0 . ");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_07) {

    TurtleParser<StringParser> parser("# This is a decimal.\n"
                                      "<s> <p> +123.0 . ");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_08) {

    TurtleParser<StringParser> parser("# This is an integer\n"
                                      "<s> <p> 123.");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_09) {

    TurtleParser<StringParser> parser("<s> <p> 123.0e1 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_10) {

    TurtleParser<StringParser> parser("<s> <p> -123e-1 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_number_11) {

    TurtleParser<StringParser> parser("<s> <p> 123.E+1 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_01) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p :\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\_\\%AA .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_02) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p :0123\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\_\\%AA123 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_pname_esc_03) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":xyz\\~ :abc\\.:  : .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_01) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_02) {

    TurtleParser<StringParser> parser("PreFIX : <http://www.w3.org/2013/TurtleTests/>");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_03) {

    TurtleParser<StringParser> parser("PREFIX : <http://www.w3.org/2013/TurtleTests/>\n"
                                      ":s :p :123 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_04) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p :%20 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_05) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ": : : .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_06) {

    TurtleParser<StringParser> parser("# colon is a legal pname character\n"
                                      "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":a:b:c  x:d:e:f :::: .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_07) {

    TurtleParser<StringParser> parser("# dash is a legal pname character\n"
                                      "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "x:a-b-c  x:p x:o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_08) {

    TurtleParser<StringParser> parser("# underscore is a legal pname character\n"
                                      "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "x:_  x:p_1 x:o .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_prefix_09) {

    TurtleParser<StringParser> parser("# percents\n"
                                      "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "@prefix x: <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":a%3E  x:%25 :a%3Eb .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_01) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\n\" .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_02) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\u0020b\" .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_str_esc_03) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\U00000020b\" .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_01) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\" .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_02) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@en .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_03) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@en-uk .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_04) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string' .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_05) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string'@en .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_06) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 'string'@en-uk .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_07) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\"\"def''ghi\"\"\" .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_08) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\n"
            "def\"\"\" .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_09) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> '''abc\n"
            "def''' .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_10) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\"\"abc\n"
            "def\"\"\"@en .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_string_11) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> '''abc\n"
            "def'''@en .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_01) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p :o1 , :o2 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_02) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p1 :o1 ;\n"
                                      "   :p2 :o2 .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_03) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p1 :o1 ;\n"
                                      "   :p2 :o2 ;\n"
                                      "   .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_04) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p1 :o1 ;;\n"
                                      "   :p2 :o2 \n"
                                      "   .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_struct_05) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p1 :o1 ;\n"
                                      "   :p2 :o2 ;;\n"
                                      "   .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_01) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_02) {

    TurtleParser<StringParser> parser("# x53 is capital S\n"
                                      "<http://www.w3.org/2013/TurtleTests/\\u0053> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_03) {

    TurtleParser<StringParser> parser("# x53 is capital S\n"
                                      "<http://www.w3.org/2013/TurtleTests/\\U00000053> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}

TEST(TurtleOfficialPositiveTests, turtle_syntax_uri_04) {

    TurtleParser<StringParser> parser("# IRI with all chars in it.\n"
                                      "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p>\n"
                                      "<scheme:!$%25&'()*+,-./0123456789:/@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~?#> .");
    ASSERT_EQ(parser.isContentParsable(), true);
}