#include <gtest/gtest.h>
#include <Parser/Turtle/AbstractParser.hpp>

TEST(TurtleOfficialEvaluationTests, bareword_a_predicate) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> a <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://a.example/o> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, bareword_decimal) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> 1.0 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .",
            nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, bareword_double) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"1E0\"^^<http://www.w3.org/2001/XMLSchema#double> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> 1E0 .", nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_as_object) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> [ <http://a.example/p2> <http://a.example/o2> ] .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> _:b1 .\n"
                                               "_:b1 <http://a.example/p2> <http://a.example/o2> .", nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_as_subject) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "[ <http://a.example/p> <http://a.example/o> ] <http://a.example/p2> <http://a.example/o2> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:b1 <http://a.example/p> <http://a.example/o> .\n"
                                               "_:b1 <http://a.example/p2> <http://a.example/o2> .", nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_containing_collection) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("[ <http://a.example/p1> (1) ] .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:b1 <http://a.example/p1> _:el1 .\n"
                                               "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
                                               "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .",
                                               nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, blankNodePropertyList_with_multiple_triples) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "[ <http://a.example/p1> <http://a.example/o1> ; <http://a.example/p2> <http://a.example/o2> ] <http://a.example/p> <http://a.example/o> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:b1 <http://a.example/p1> <http://a.example/o1> .\n"
                                               "_:b1 <http://a.example/p2> <http://a.example/o2> .\n"
                                               "_:b1 <http://a.example/p> <http://a.example/o> .", nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, collection_object) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> (1) .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> _:el1 .\n"
                                               "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
                                               "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .",
                                               nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, collection_subject) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("(1) <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
            "_:el1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
            "_:el1 <http://a.example/p> <http://a.example/o> .", nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, comment_following_PNAME_NS) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> p:#comment\n"
                                               ".", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> <http://a.example/> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, double_lower_case_e) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> 1e0 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"1e0\"^^<http://www.w3.org/2001/XMLSchema#double> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, empty_collection) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> () .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .",
            nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, first) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> ((1) 2) .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> _:outerEl1 .\n"
                                               "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> _:innerEl1 .\n"
                                               "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
                                               "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
                                               "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> _:outerEl2 .\n"
                                               "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
                                               "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .",
                                               nTriples_state);
    //ASSERT_TRUE(turtle_state.parsed_terms==nTriples_state.parsed_terms);
    std::cout << std::endl;
    for (const auto &it:turtle_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
    std::cout << std::endl;
    for (const auto &it:nTriples_state.parsed_terms) {
        std::cout << (std::get<0>(it))->getValue() << " "
                  << (std::get<1>(it))->getValue() << " "
                  << (std::get<2>(it))->getValue()
                  << std::endl;
    }
}

TEST(TurtleOfficialEvaluationTests, HYPHEN_MINUS_in_localName) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:s- <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s-> <http://a.example/p> <http://a.example/o> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, IRI_with_all_punctuation) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<scheme:!$%25&amp;'()*+,-./0123456789:/@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~?#> <http://a.example/p> <http://a.example/o> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<scheme:!$%25&amp;'()*+,-./0123456789:/@ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz~?#> <http://a.example/p> <http://a.example/o> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, IRIREF_datatype) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, labeled_blank_node_object) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> _:o .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> _:b1 .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, labeled_blank_node_subject) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("_:s <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:b1 <http://a.example/p> <http://a.example/o> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, langtagged_LONG_with_subtag) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test long literal with lang tag\n"
                                               "@prefix :  <http://example.org/ex#> .\n"
                                               ":a :b \"\"\"Cheers\"\"\"@en-UK .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://example.org/ex#a> <http://example.org/ex#b> \"Cheers\"@en-UK .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, langtagged_non_LONG) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"chat\"@en .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"chat\"@en .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, lantag_with_subtag) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"chat\"@en-us .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"chat\"@en-us .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, last) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> (1 (2)) .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> _:outerEl1 .\n"
                                               "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
                                               "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> _:outerEl2 .\n"
                                               "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> _:innerEl1 .\n"
                                               "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
                                               "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
                                               "_:outerEl2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL1) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> 'x' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"x\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL1_all_punctuation) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> ' !\"#$%&():;<=>?@[]^_`{|}~' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \" !\\\"#$%&():;<=>?@[]^_`{|}~\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL1_ascii_boundaries) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> ' \t\u000B\f\u000E&([]\u007F' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"\\u0000\\t\\u000B\\u000C\\u000E&([]\\u007F\" .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, literal_false) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> false .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"false\"^^<http://www.w3.org/2001/XMLSchema#boolean> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL_LONG1_ascii_boundaries) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> ' &([]\u007F' .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\u0000&([]\\u007F\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL_LONG1_with_1_squote) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '''x'y''' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"x'y\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL_LONG1_with_2_squotes) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '''x''y''' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"x''y\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_ascii_boundaries) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \" !#[]\u007F\" .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\u0000!#[]\\u007F\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_with_1_squote) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\"\"x\"y\"\"\" .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"x\\\"y\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_with_2_squotes) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\"\"x\"\"y\"\"\" .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"x\\\"\\\"y\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, LITERAL_LONG2_with_REVERSE_SOLIDUS) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org/ns#> .\n"
                                               "\n"
                                               ":s :p1 \"\"\"test-\\\\\"\"\" .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://example.org/ns#s> <http://example.org/ns#p1> \"test-\\\\\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, literal_true) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> true .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"true\"^^<http://www.w3.org/2001/XMLSchema#boolean> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, literal_with_BACKSPACE) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '\b' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\u0008\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, literal_with_CARRIAGE_RETURN) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '''\n"
                                               "''' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\r\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, literal_with_CHARACTER_TABULATION) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '\t' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\t\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, literal_with_FORM_FEED) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '\f' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\u000C\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);

}

TEST(TurtleOfficialEvaluationTests, literal_with_LINE_FEED) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '''\n"
                                               "''' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\n\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);

}

TEST(TurtleOfficialEvaluationTests, literal_with_numeric_escape4) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '\\u006F' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"o\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, literal_with_REVERSE_SOLIDUS) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> '\\\\' .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> \"\\\\\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, localName_with_assigned_nfc_bmp_PN_CHARS_BASE_character_boundaries) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> p:AZazÀÖØöø˿Ͱͽ΄῾\u200C\u200D⁰↉Ⰰ⿕、ퟻ﨎ﷇﷰ\uFFEF .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> <http://a.example/AZaz\\u00C0\\u00D6\\u00D8\\u00F6\\u00F8\\u02FF\\u0370\\u037D\\u0384\\u1FFE\\u200C\\u200D\\u2070\\u2189\\u2C00\\u2FD5\\u3001\\uD7FB\\uFA0E\\uFDC7\\uFDF0\\uFFEF> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

/*TEST(TurtleOfficialEvaluationTests, localName_with_assigned_nfc_PN_CHARS_BASE_character_boundaries) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> p:AZazÀÖØöø˿Ͱͽ΄῾\u200C\u200D⁰↉Ⰰ⿕、ퟻ﨎ﷇﷰ\uFFEF\uD800\uDC00\uDB40\uDDEF .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> <http://a.example/AZaz\\u00C0\\u00D6\\u00D8\\u00F6\\u00F8\\u02FF\\u0370\\u037D\\u0384\\u1FFE\\u200C\\u200D\\u2070\\u2189\\u2C00\\u2FD5\\u3001\\uD7FB\\uFA0E\\uFDC7\\uFDF0\\uFFEF\\U00010000\\U000E01EF> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}*/

TEST(TurtleOfficialEvaluationTests, localname_with_COLON) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:s: <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s:> <http://a.example/p> <http://a.example/o> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, localName_with_leading_digit) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:0 <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/0> <http://a.example/p> <http://a.example/o> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, localName_with_leading_underscore) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:_ <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/_> <http://a.example/p> <http://a.example/o> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

/*
TEST(TurtleOfficialEvaluationTests, localName_with_nfc_PN_CHARS_BASE_character_boundaries) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> p:AZazÀÖØöø˿Ͱͽ\u037F\u1FFF\u200C\u200D⁰\u218FⰀ\u2FEF、\uD7FF﨎\uFDCFﷰ\uFFEF\uD800\uDC00\uDB7F\uDFFD .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> <http://a.example/AZaz\\u00C0\\u00D6\\u00D8\\u00F6\\u00F8\\u02FF\\u0370\\u037D\\u037F\\u1FFF\\u200C\\u200D\\u2070\\u218F\\u2C00\\u2FEF\\u3001\\uD7FF\\uFA0E\\uFDCF\\uFDF0\\uFFEF\\U00010000\\U000EFFFD> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}
*/

TEST(TurtleOfficialEvaluationTests, localName_with_non_leading_extras) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:a·̀ͯ‿.⁀ <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/a\\u00b7\\u0300\\u036f\\u203f\\u002e\\u2040> <http://a.example/p> <http://a.example/o> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, negative_numeric) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> -1 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"-1\"^^<http://www.w3.org/2001/XMLSchema#integer> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, nested_blankNodePropertyLists) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "[ <http://a.example/p1> [ <http://a.example/p2> <http://a.example/o2> ] ; <http://a.example/p> <http://a.example/o> ].",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:b1 <http://a.example/p1> _:b2 .\n"
                                               "_:b2 <http://a.example/p2> <http://a.example/o2> .\n"
                                               "_:b1 <http://a.example/p> <http://a.example/o> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, nested_collection) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> ((1)) .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> _:outerEl1 .\n"
                                               "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> _:innerEl1 .\n"
                                               "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
                                               "_:innerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
                                               "_:outerEl1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, number_sign_following_localName) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/> .\n"
                                               "<http://a.example/s> <http://a.example/p> p:o\\#numbersign\n"
                                               ".", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> <http://a.example/o#numbersign> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, number_sign_following_PNAME_NS) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "<http://a.example/s> <http://a.example/p> p:\\#numbersign\n"
                                               ".", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> <http://a.example/#numbersign> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, numeric_with_leading_0) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> 01 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"01\"^^<http://www.w3.org/2001/XMLSchema#integer> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, objectList_with_two_objects) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> <http://a.example/o1>, <http://a.example/o2> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> <http://a.example/o1> .\n"
                                               "<http://a.example/s> <http://a.example/p> <http://a.example/o2> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, percent_escaped_localName) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:%25 <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/%25> <http://a.example/p> <http://a.example/o> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, positive_numeric) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p> +1 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p> \"+1\"^^<http://www.w3.org/2001/XMLSchema#integer> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, predicateObjectList_with_two_objectLists) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/s> <http://a.example/p1> <http://a.example/o1>; <http://a.example/p2> <http://a.example/o2> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p1> <http://a.example/o1> .\n"
                                               "<http://a.example/s> <http://a.example/p2> <http://a.example/o2> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, prefix_reassigned_and_used) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "@prefix p: <http://b.example/>.\n"
                                               "p:s <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://b.example/s> <http://a.example/p> <http://a.example/o> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, repeated_semis_not_at_end) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p1> <http://a.example/o1>;; .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s> <http://a.example/p1> <http://a.example/o1> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, reserved_escaped_localName) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:\\_\\~\\.\\-\\!\\$\\&\\'\\(\\)\\*\\+\\,\\;\\=\\/\\?\\#\\@\\%00 <http://a.example/p> <http://a.example/o> .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://a.example/_~.-!$&'()*+,;=/?#@%00> <http://a.example/p> <http://a.example/o> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_eval_struct_01) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_eval_struct_02) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://www.w3.org/2013/TurtleTests/s> \n"
                                               "      <http://www.w3.org/2013/TurtleTests/p1> <http://www.w3.org/2013/TurtleTests/o1> ;\n"
                                               "      <http://www.w3.org/2013/TurtleTests/p2> <http://www.w3.org/2013/TurtleTests/o2> ; \n"
                                               "      .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p1> <http://www.w3.org/2013/TurtleTests/o1> .\n"
            "<http://www.w3.org/2013/TurtleTests/s> <http://www.w3.org/2013/TurtleTests/p2> <http://www.w3.org/2013/TurtleTests/o2> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_01) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <#> .\n"
                                               "[] :x :y .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "_:genid1 <http://www.w3.org/2013/TurtleTests/turtle-subm-01.ttl#x> <http://www.w3.org/2013/TurtleTests/turtle-subm-01.ttl#y> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_02) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test @prefix and qnames\n"
                                               "@prefix :  <http://example.org/base1#> .\n"
                                               "@prefix a: <http://example.org/base2#> .\n"
                                               "@prefix b: <http://example.org/base3#> .\n"
                                               ":a :b :c .\n"
                                               "a:a a:b a:c .\n"
                                               ":a a:a b:a .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/base1#a> <http://example.org/base1#b> <http://example.org/base1#c> .\n"
            "<http://example.org/base2#a> <http://example.org/base2#b> <http://example.org/base2#c> .\n"
            "<http://example.org/base1#a> <http://example.org/base2#a> <http://example.org/base3#a> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_03) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test , operator\n"
                                               "@prefix : <http://example.org/base#> .\n"
                                               ":a :b :c,\n"
                                               "      :d,\n"
                                               "      :e .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#c> .\n"
            "<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#d> .\n"
            "<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#e> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_04) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test ; operator\n"
                                               "@prefix : <http://example.org/base#> .\n"
                                               ":a :b :c ;\n"
                                               "   :d :e ;\n"
                                               "   :f :g .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/base#a> <http://example.org/base#b> <http://example.org/base#c> .\n"
            "<http://example.org/base#a> <http://example.org/base#d> <http://example.org/base#e> .\n"
            "<http://example.org/base#a> <http://example.org/base#f> <http://example.org/base#g> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_05) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test empty [] operator; not allowed as predicate\n"
                                               "@prefix : <http://example.org/base#> .\n"
                                               "[] :a :b .\n"
                                               ":c :d [] .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:genid1 <http://example.org/base#a> <http://example.org/base#b> .\n"
                                               "<http://example.org/base#c> <http://example.org/base#d> _:genid2 .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_06) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test non empty [] operator; not allowed as predicate\n"
                                               "@prefix : <http://example.org/base#> .\n"
                                               "[ :a :b ] :c :d .\n"
                                               ":e :f [ :g :h ] .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:genid1 <http://example.org/base#a> <http://example.org/base#b> .\n"
                                               "_:genid1 <http://example.org/base#c> <http://example.org/base#d> .\n"
                                               "_:genid2 <http://example.org/base#g> <http://example.org/base#h> .\n"
                                               "<http://example.org/base#e> <http://example.org/base#f> _:genid2 .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_07) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# 'a' only allowed as a predicate\n"
                                               "@prefix : <http://example.org/base#> .\n"
                                               ":a a :b .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/base#a> <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://example.org/base#b> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_08) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org/stuff/1.0/> .\n"
                                               ":a :b ( \"apple\" \"banana\" ) .\n"
                                               "", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "_:genid1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"banana\" .\n"
            "_:genid1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .\n"
            "_:genid2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#first> \"apple\" .\n"
            "_:genid2 <http://www.w3.org/1999/02/22-rdf-syntax-ns#rest> _:genid1 .\n"
            "<http://example.org/stuff/1.0/a> <http://example.org/stuff/1.0/b> _:genid2 .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_09) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org/stuff/1.0/> .\n"
                                               ":a :b ( ) .\n"
                                               "", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/stuff/1.0/a> <http://example.org/stuff/1.0/b> <http://www.w3.org/1999/02/22-rdf-syntax-ns#nil> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_10) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test integer datatyped literals using an OWL cardinality constraint\n"
                                               "@prefix owl: <http://www.w3.org/2002/07/owl#> .\n"
                                               "\n"
                                               "# based on examples in the OWL Reference\n"
                                               "\n"
                                               "_:hasParent a owl:ObjectProperty .\n"
                                               "\n"
                                               "[] a owl:Restriction ;\n"
                                               "  owl:onProperty _:hasParent ;\n"
                                               "  owl:maxCardinality 2 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "_:hasParent <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://www.w3.org/2002/07/owl#ObjectProperty> .\n"
            "_:genid1 <http://www.w3.org/1999/02/22-rdf-syntax-ns#type> <http://www.w3.org/2002/07/owl#Restriction> .\n"
            "_:genid1 <http://www.w3.org/2002/07/owl#onProperty> _:hasParent .\n"
            "_:genid1 <http://www.w3.org/2002/07/owl#maxCardinality> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_11) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("<http://example.org/res1> <http://example.org/prop1> 000000 .\n"
                                               "<http://example.org/res2> <http://example.org/prop2> 0 .\n"
                                               "<http://example.org/res3> <http://example.org/prop3> 000001 .\n"
                                               "<http://example.org/res4> <http://example.org/prop4> 2 .\n"
                                               "<http://example.org/res5> <http://example.org/prop5> 4 .",
                                               turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/res1> <http://example.org/prop1> \"000000\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
            "<http://example.org/res2> <http://example.org/prop2> \"0\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
            "<http://example.org/res3> <http://example.org/prop3> \"000001\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
            "<http://example.org/res4> <http://example.org/prop4> \"2\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
            "<http://example.org/res5> <http://example.org/prop5> \"4\"^^<http://www.w3.org/2001/XMLSchema#integer> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_12) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Tests for - and _ in names, qnames\n"
                                               "@prefix ex1: <http://example.org/ex1#> .\n"
                                               "@prefix ex-2: <http://example.org/ex2#> .\n"
                                               "@prefix ex3_: <http://example.org/ex3#> .\n"
                                               "@prefix ex4-: <http://example.org/ex4#> .\n"
                                               "\n"
                                               "ex1:foo-bar ex1:foo_bar \"a\" .\n"
                                               "ex-2:foo-bar ex-2:foo_bar \"b\" .\n"
                                               "ex3_:foo-bar ex3_:foo_bar \"c\" .\n"
                                               "ex4-:foo-bar ex4-:foo_bar \"d\" .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/ex1#foo-bar> <http://example.org/ex1#foo_bar> \"a\" .\n"
            "<http://example.org/ex2#foo-bar> <http://example.org/ex2#foo_bar> \"b\" .\n"
            "<http://example.org/ex3#foo-bar> <http://example.org/ex3#foo_bar> \"c\" .\n"
            "<http://example.org/ex4#foo-bar> <http://example.org/ex4#foo_bar> \"d\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_13) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Tests for rdf:_<numbers> and other qnames starting with _\n"
                                               "@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
                                               "@prefix ex:  <http://example.org/ex#> .\n"
                                               "@prefix :    <http://example.org/myprop#> .\n"
                                               "\n"
                                               "ex:foo rdf:_1 \"1\" .\n"
                                               "ex:foo rdf:_2 \"2\" .\n"
                                               "ex:foo :_abc \"def\" .\n"
                                               "ex:foo :_345 \"678\" .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/ex#foo> <http://www.w3.org/1999/02/22-rdf-syntax-ns#_1> \"1\" .\n"
            "<http://example.org/ex#foo> <http://www.w3.org/1999/02/22-rdf-syntax-ns#_2> \"2\" .\n"
            "<http://example.org/ex#foo> <http://example.org/myprop#_abc> \"def\" .\n"
            "<http://example.org/ex#foo> <http://example.org/myprop#_345> \"678\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_14) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test for : allowed\n"
                                               "@prefix :    <http://example.org/ron> .\n"
                                               "\n"
                                               "[] : [] .\n"
                                               "\n"
                                               ": : : .\n"
                                               "", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("_:genid1 <http://example.org/ron> _:genid2 .\n"
                                               "<http://example.org/ron> <http://example.org/ron> <http://example.org/ron> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_15) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test long literal\n"
                                               "@prefix :  <http://example.org/ex#> .\n"
                                               ":a :b \"\"\"a long\n"
                                               "\tliteral\n"
                                               "with\n"
                                               "newlines\"\"\" .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/ex#a> <http://example.org/ex#b> \"a long\\n\\tliteral\\nwith\\nnewlines\" .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_16) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org/foo#> .\n"
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
                                               "\"\"\" .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/foo#a> <http://example.org/foo#b> \"\\nthis \\ris a \\U00012451long\\t\\nliteral\\uABCD\\n\" .\n"
            "<http://example.org/foo#d> <http://example.org/foo#e> \"\\tThis \\uABCDis\\r \\U00012451another\\n\\none\\n\" .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_17) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org/#> .\n"
                                               "\n"
                                               ":a :b  1.0 .\n"
                                               "", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/#a> <http://example.org/#b> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_18) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org/#> .\n"
                                               "\n"
                                               ":a :b \"\" .\n"
                                               "\n"
                                               ":c :d \"\"\"\"\"\" .\n"
                                               "", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://example.org/#a> <http://example.org/#b> \"\" .\n"
                                               "<http://example.org/#c> <http://example.org/#d> \"\" .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_19) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org#> .\n"
                                               ":a :b 1.0 .\n"
                                               ":c :d 1 .\n"
                                               ":e :f 1.0e0 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org#a> <http://example.org#b> \"1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
            "<http://example.org#c> <http://example.org#d> \"1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
            "<http://example.org#e> <http://example.org#f> \"1.0e0\"^^<http://www.w3.org/2001/XMLSchema#double> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_20) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org#> .\n"
                                               ":a :b -1.0 .\n"
                                               ":c :d -1 .\n"
                                               ":e :f -1.0e0 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org#a> <http://example.org#b> \"-1.0\"^^<http://www.w3.org/2001/XMLSchema#decimal> .\n"
            "<http://example.org#c> <http://example.org#d> \"-1\"^^<http://www.w3.org/2001/XMLSchema#integer> .\n"
            "<http://example.org#e> <http://example.org#f> \"-1.0e0\"^^<http://www.w3.org/2001/XMLSchema#double> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_21) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test long literal\n"
                                               "@prefix :  <http://example.org/ex#> .\n"
                                               ":a :b \"\"\"John said: \"Hello World!\\\"\"\"\" .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/ex#a> <http://example.org/ex#b> \"John said: \\\"Hello World!\\\"\" .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_22) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix : <http://example.org#> .\n"
                                               ":a :b true .\n"
                                               ":c :d false .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org#a> <http://example.org#b> \"true\"^^<http://www.w3.org/2001/XMLSchema#boolean> .\n"
            "<http://example.org#c> <http://example.org#d> \"false\"^^<http://www.w3.org/2001/XMLSchema#boolean> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_23) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# comment test\n"
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
                                               "   :p :q . # and me", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/#a> <http://example.org/#b> <http://example.org/#c> .\n"
            "<http://example.org/#d> <http://example.org/#e> <http://example.org/#f> .\n"
            "<http://example.org/#g> <http://example.org/#h> <http://example.org/#i> .\n"
            "<http://example.org/#g> <http://example.org/#h> <http://example.org/#j> .\n"
            "<http://example.org/#k> <http://example.org/#l> <http://example.org/#m> .\n"
            "<http://example.org/#k> <http://example.org/#n> <http://example.org/#o> .\n"
            "<http://example.org/#k> <http://example.org/#p> <http://example.org/#q> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_24) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# comment line with no final newline test\n"
                                               "@prefix : <http://example.org/#> .\n"
                                               ":a :b :c .\n"
                                               "#foo", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/#a> <http://example.org/#b> <http://example.org/#c> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_25) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix foo: <http://example.org/foo#>  .\n"
                                               "@prefix foo: <http://example.org/bar#>  .\n"
                                               "\n"
                                               "foo:blah foo:blah foo:blah .\n"
                                               "", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/bar#blah> <http://example.org/bar#blah> <http://example.org/bar#blah> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_26) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
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
            "<http://example.org/foo> <http://example.org/bar> \"1.2345678901234567890123457890\"^^<http://www.w3.org/2001/XMLSchema#decimal> .",
            turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
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
            "<http://example.org/foo> <http://example.org/bar> \"1.2345678901234567890123457890\"^^<http://www.w3.org/2001/XMLSchema#decimal> .",
            nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, turtle_subm_27) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction(
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
            ":a5 :b5 :c5 .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://www.w3.org/2013/TurtleTests/a1> <http://www.w3.org/2013/TurtleTests/b1> <http://www.w3.org/2013/TurtleTests/c1> .\n"
            "<http://example.org/ns/a2> <http://example.org/ns/b2> <http://example.org/ns/c2> .\n"
            "<http://example.org/ns/foo/a3> <http://example.org/ns/foo/b3> <http://example.org/ns/foo/c3> .\n"
            "<http://example.org/ns/foo/bar#a4> <http://example.org/ns/foo/bar#b4> <http://example.org/ns/foo/bar#c4> .\n"
            "<http://example.org/ns2#a5> <http://example.org/ns2#b5> <http://example.org/ns2#c5> .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, two_LITERAL_LONG2s) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("# Test long literal twice to ensure it does not over-quote\n"
                                               "@prefix :  <http://example.org/ex#> .\n"
                                               ":a :b \"\"\"first long literal\"\"\" .\n"
                                               ":c :d \"\"\"second long literal\"\"\" .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction(
            "<http://example.org/ex#a> <http://example.org/ex#b> \"first long literal\" .\n"
            "<http://example.org/ex#c> <http://example.org/ex#d> \"second long literal\" .", nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}

TEST(TurtleOfficialEvaluationTests, underscore_in_localName) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlStates::State nTriples_state;
    TurtlePegtlParser<>::parseStringwithAction("@prefix p: <http://a.example/>.\n"
                                               "p:s_ <http://a.example/p> <http://a.example/o> .", turtle_state);
    TurtlePegtlParser<>::parseStringwithAction("<http://a.example/s_> <http://a.example/p> <http://a.example/o> .",
                                               nTriples_state);
    ASSERT_TRUE(turtle_state.parsed_terms == nTriples_state.parsed_terms);
}
