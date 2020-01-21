#include <gtest/gtest.h>
#include "TurtleOfficalExamplesTest.cpp"
#include "TurtleOfficialPositiveTests.cpp"
#include "TurtleOfficialNegativeTests.cpp"
#include "TurtleOfficialEvaluationTests.cpp"
//#include "TurtleOfficialNegativeEvaluationTests.cpp"

//#include "TurtleParserFilesTests.cpp"
#include "TermParserTests.cpp"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
