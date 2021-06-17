#include <gtest/gtest.h>

#include "SparqlTriplesBlockParsingTests.cpp"
#include "TermTests.cpp"
#include "TurtleOfficalExamplesTest.cpp"
#include "TurtleOfficialEvaluationTests.cpp"
#include "TurtleOfficialNegativeEvaluationTests.cpp"
#include "TurtleOfficialNegativeTests.cpp"
#include "TurtleOfficialPositiveTests.cpp"
#include "TurtleParserFilesTests.cpp"
#include "LiteralsTest.cpp"

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
