#include <gtest/gtest.h>
#include <Parser/Turtle/AbstractParser.hpp>

TEST(TurtleOfficialNegativeEvaluationTests, turtle_eval_bad_01) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlParser<>::parseStringwithAction("# Bad IRI : good escape, bad charcater\n"
                                               "<http://www.w3.org/2013/TurtleTests/\\u0020> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .",
                                               turtle_state);
}

TEST(TurtleOfficialNegativeEvaluationTests, turtle_eval_bad_02) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlParser<>::parseStringwithAction("# Bad IRI : hex 3C is <\n"
                                               "<http://www.w3.org/2013/TurtleTests/\\u003C> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .",
                                               turtle_state);
}

TEST(TurtleOfficialNegativeEvaluationTests, turtle_eval_bad_03) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlParser<>::parseStringwithAction("# Bad IRI : hex 3E is >\n"
                                               "<http://www.w3.org/2013/TurtleTests/\\u003E> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .",
                                               turtle_state);
}

TEST(TurtleOfficialNegativeEvaluationTests, turtle_eval_bad_04) {
    TurtlePegtlStates::State turtle_state;
    TurtlePegtlParser<>::parseStringwithAction("# Bad IRI\n"
                                               "<http://www.w3.org/2013/TurtleTests/{abc}> <http://www.w3.org/2013/TurtleTests/p> <http://www.w3.org/2013/TurtleTests/o> .",
                                               turtle_state);
}