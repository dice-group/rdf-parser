#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/StringParser.hpp>

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_01) {

    StringParser parser("@base .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_02) {

    StringParser parser(
            "@BASE <http://www.w3.org/2013/TurtleTests/> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_base_03) {

    StringParser parser(
            "BASE <http://www.w3.org/2013/TurtleTests/> .\n"
            "<s> <p> <o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_blank_label_dot_end) {

    StringParser parser(
            "_:b1. :p :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_esc_01) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"a\\zb\" .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_esc_02) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\uWXYZ\" .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_esc_03) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\U0000WXYZ\" .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_esc_04) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"\\U0000WXYZ\" .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_01) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s A :C .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_02) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "a :p :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_03) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p a .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_04) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "true :p :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_kw_05) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s true :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_lang_01) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> \"string\"@1 .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_LITERAL2_with_langtag_and_datatype) {

    StringParser parser(
            "<http://example.org/resource> <http://example.org#pred> \"value\"@en^^<http://www.w3.org/1999/02/22-rdf-syntax-ns#XMLLiteral> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ln_dash_start) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p :-o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ln_escape) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p :o%2 .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ln_escape_start) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p :%2o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_missing_ns_dot_end) {

    StringParser parser("valid:s valid:p invalid.:o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_missing_ns_dot_start) {

    StringParser parser(".undefined:s .undefined:p .undefined:o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_01) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "\n"
            "{ :a :q :c . } :p :z .\n"
            "");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_02) {

    StringParser parser("# = is not Turtle\n"
                          "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "\n"
                          ":a = :b .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_03) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@prefix ns: <http://www.w3.org/2013/TurtleTests/p#> .\n"
            "\n"
            ":x.\n"
            "  ns:p.\n"
            "    ns:q :p :z .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_04) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@prefix ns: <http://www.w3.org/2013/TurtleTests/p#> .\n"
            "\n"
            ":x^ns:p :p :z .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_05) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "\n"
            ":z is :p of :x .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_06) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "\n"
            ":a.:b.:c .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_07) {

    StringParser parser(
            "@keywords a .\n"
            "x a Item .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_08) {

    StringParser parser(
            "@keywords a .\n"
            "x a Item .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_09) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s => :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_10) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s <= :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_11) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@forSome :x .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_12) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            "@forAll :x .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_n3_extras_13) {

    StringParser parser(
            "@keywords .\n"
            "x @a Item .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ns_dot_end) {

    StringParser parser("@prefix eg. : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "eg.:s eg.:p eg.:o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_ns_dot_start) {

    StringParser parser("@prefix .eg : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ".eg:s .eg:p .eg:o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_01) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123.abc .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_02) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123e .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_03) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 123abc .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_04) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> 0x123 .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_num_05) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> +-1 .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_number_dot_in_anon) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          "\n"
                          ":s\n"
                          "\t:p [\n"
                          "\t\t:p1 27.\n"
                          "\t] .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_01) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":a~b :p :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_02) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":a%2 :p :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_pname_03) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":a\\u0039 :p :o .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_01) {

    StringParser parser(
            ":s <http://www.w3.org/2013/TurtleTests/p> \"x\" .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_02) {

    StringParser parser(
            "@prefix rdf:     <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
            "<http://www.w3.org/2013/TurtleTests/s> rdf:type :C .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_03) {

    StringParser parser(
            "@prefix ex: .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_04) {

    StringParser parser(
            "@prefix <http://www.w3.org/2013/TurtleTests/> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_prefix_05) {

    StringParser parser(
            "@prefix x <http://www.w3.org/2013/TurtleTests/> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_01) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p \"abc' .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_02) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p 'abc\" .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_03) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p '''abc' .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_04) {

    StringParser parser("@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
                          ":s :p \"\"\"abc''' .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_05) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s :p \"\"\"abc\n"
            "def");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_06) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s :p \"\"\"abc\"\"\"\"@en .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_string_07) {

    StringParser parser(
            "@prefix : <http://www.w3.org/2013/TurtleTests/> .\n"
            ":s :p '''abc''''@en .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_01) {

    StringParser parser(
            "{ <http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> }");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_02) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> = <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_03) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> <http://www.w3.org/2013/TurtleTests/g> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_04) {

    StringParser parser(
            "\"hello\" <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_05) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> \"hello\" <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_06) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> [] <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_07) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> _:p <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_08) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o>");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_09) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> . .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_10) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> . .\n"
            "<http://www.w3.org/2013/TurtleTests/s1> <http://www.w3.org/2013/TurtleTests/p1> <http://www.w3.org/2013/TurtleTests/o1> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_11) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> ;");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_12) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> ");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_13) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> ");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_14) {

    StringParser parser(
            "\"abc\" <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/p>  .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_15) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> \"abc\" <http://www.w3.org/2013/TurtleTests/p>  .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_16) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> [] <http://www.w3.org/2013/TurtleTests/p>  .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_struct_17) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/s> _:a <http://www.w3.org/2013/TurtleTests/p>  .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_01) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/ space> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_02) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/\\u00ZZ11> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_03) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/\\U00ZZ1111> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_04) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/\\n> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}

TEST(TurtleOfficialNegativeTests, turtle_syntax_bad_uri_05) {

    StringParser parser(
            "<http://www.w3.org/2013/TurtleTests/\\/> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .");
}
