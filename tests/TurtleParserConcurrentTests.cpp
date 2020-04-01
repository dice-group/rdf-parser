#include <gtest/gtest.h>
#include <Dice/rdf_parser/TurtleParser.hpp>

namespace {
    using namespace rdf_parser::Turtle;
    using namespace rdf_parser::store::rdf;
}


TEST(TurtleParserConcurrentTests,ntripleFileCon1) {
    TurtleParser<CuncurrentStreamParser> parser("../datasets/instances-labels.nt");
    auto it= parser.begin();
    while (it)
        it++;

}

TEST(TurtleParserConcurrentTests,turtleFileCon1) {
    TurtleParser<CuncurrentStreamParser> parser("../datasets/instance-types_transitive.ttl");
    auto it= parser.begin();
    while (it)
        it++;

}
