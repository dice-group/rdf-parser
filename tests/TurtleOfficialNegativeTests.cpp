#include <gtest/gtest.h>
#include <Dice/rdf_parser/TurtleParser.hpp>

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_01) {

    TurtleParser<StringParser> parser("@base .");
    ASSERT_EQ(parser.isContentParsable(), false);

}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_02) {

    TurtleParser<StringParser> parser(
            "@BASE <http://www.w3.org/2013/TurtleTests/> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_03) {

    TurtleParser<StringParser> parser(
            "BASE <http://www.w3.org/2013/TurtleTests/> .\n"
            "<s> <p> <o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_blank_label_dot_end) {

    TurtleParser<StringParser> parser(
            "_:b1. :p :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_esc_01) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\zb\" .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_esc_02) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\uWXYZ\" .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_esc_03) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\U0000WXYZ\" .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_esc_04) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\U0000WXYZ\" .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_01) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s A :C .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_02) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "a :p :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_03) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p a .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_04) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "true :p :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_05) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s true :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_lang_01) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@1 .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_LITERAL2_with_langtag_and_datatype) {

    TurtleParser<StringParser> parser(
            "<http://example.org/resource> <http://example.org#pred> \"value\"@en^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#XMLLiteral> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ln_dash_start) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p :-o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ln_escape) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p :o%2 .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_ln_escape_start) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p :%2o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_missing_ns_dot_end) {

    TurtleParser<StringParser> parser("valid:s valid:p invalid.:o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_missing_ns_dot_start) {

    TurtleParser<StringParser> parser(".undefined:s .undefined:p .undefined:o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_01) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "\n"
            "{ :a :q :c . } :p :z .\n"
            "");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_02) {

    TurtleParser<StringParser> parser("# = is not Turtle\n"
                                      "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "\n"
                                      ":a = :b .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_03) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@prefix ns: <http://www.w3.org/2013/TurtleTests/p#> .\n"
            "\n"
            ":x.\n"
            "  ns:p.\n"
            "    ns:q :p :z .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_04) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@prefix ns: <http://www.w3.org/2013/TurtleTests/p#> .\n"
            "\n"
            ":x^ns:p :p :z .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_05) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "\n"
            ":z is :p of :x .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_06) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "\n"
            ":a.:b.:c .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_07) {

    TurtleParser<StringParser> parser(
            "@keywords a .\n"
            "x a Item .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_08) {

    TurtleParser<StringParser> parser(
            "@keywords a .\n"
            "x a Item .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_09) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s => :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_10) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s <= :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_11) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@forSome :x .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_12) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@forAll :x .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_13) {

    TurtleParser<StringParser> parser(
            "@keywords .\n"
            "x @a Item .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ns_dot_end) {

    TurtleParser<StringParser> parser("@prefix eg. : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "eg.:s eg.:p eg.:o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ns_dot_start) {

    TurtleParser<StringParser> parser("@prefix .eg : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ".eg:s .eg:p .eg:o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_01) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123.abc .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_02) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123e .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_03) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123abc .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_04) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 0x123 .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_05) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> +-1 .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_number_dot_in_anon) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      "\n"
                                      ":s\n"
                                      "\t:p [\n"
                                      "\t\t:p1 27.\n"
                                      "\t] .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_01) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":a~b :p :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_02) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":a%2 :p :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_03) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":a\\u0039 :p :o .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_prefix_01) {

    TurtleParser<StringParser> parser(
            ":s <http://www.w3.org/2013/TurtleTests/p> \"x\" .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_prefix_02) {

    TurtleParser<StringParser> parser(
            "@prefix rdf:     <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
            "<http://www.w3.org/2013/TurtleTests/s> rdf:type :C .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_03) {

    TurtleParser<StringParser> parser(
            "@prefix ex: .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_04) {

    TurtleParser<StringParser> parser(
            "@prefix <http://www.w3.org/2013/TurtleTests/> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_05) {

    TurtleParser<StringParser> parser(
            "@prefix x <http://www.w3.org/2013/TurtleTests/> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_01) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p \"abc' .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_02) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p 'abc\" .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_03) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p '''abc' .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_04) {

    TurtleParser<StringParser> parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                                      ":s :p \"\"\"abc''' .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_05) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s :p \"\"\"abc\n"
            "def");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_06) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s :p \"\"\"abc\"\"\"\"@en .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_07) {

    TurtleParser<StringParser> parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s :p '''abc''''@en .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_01) {

    TurtleParser<StringParser> parser(
            "{ <http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> }");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_02) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> = <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_03) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> <http://www.w3.org/2013/TurtleTests/g> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_04) {

    TurtleParser<StringParser> parser(
            "\"hello\" <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_05) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> \"hello\" <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_06) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> [] <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_07) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> _:p <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_08) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o>");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_09) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> . .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_10) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> . .\n"
            "<http://www.w3.org/2013/TurtleTests/s1> <http://www.w3.org/2013/TurtleTests/p1> <http://www.w3.org/2013/TurtleTests/o1> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_11) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ;");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_12) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> ");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_13) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> ");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_14) {

    TurtleParser<StringParser> parser(
            "\"abc\" <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/p>  .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_15) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> \"abc\" <http://www.w3.org/2013/TurtleTests/p>  .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_16) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> [] <http://www.w3.org/2013/TurtleTests/p>  .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_17) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/s> _:a <http://www.w3.org/2013/TurtleTests/p>  .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_01) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/ space> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_uri_02) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/\\u00ZZ11> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, DISABLED_turtle_syntax_bad_uri_03) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/\\U00ZZ1111> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_04) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/\\n> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_05) {

    TurtleParser<StringParser> parser(
            "<http://www.w3.org/2013/TurtleTests/\\/> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
    ASSERT_EQ(parser.isContentParsable(), false);
}
