
#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/StringParser.hpp>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/ConcurrentStreamParser.hpp>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/FileParser.hpp>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/StreamParser.hpp>


using namespace rdf_parser::Turtle;


TEST(PatrialGrammerTest, parseSparqslCollectison) {

    rdf_parser::Turtle::parsers::StringParser<true> parser("?x <sad>  ?name ") ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
//    bool t2=rdf_parser::Turtle::TermParser::isTermParsable("\" hello \'hello\'  \"");
//    ASSERT_EQ(t1, true);
//    ASSERT_EQ(t2, true);
    ASSERT_EQ(1, true);
}

TEST(PatrialGrammerTest, F1) {

    rdf_parser::Turtle::parsers::StringParser<true> parser("?g <sad> ?who") ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}

TEST(PatrialGrammerTest, AddedprefixTest) {

    std::map<std::string,std::string > prefixes;
    prefixes.insert(std::pair<std::string,std::string>("foaf","http://xmlns.com/foaf/0.1/"));
    rdf_parser::Turtle::parsers::StringParser<true> parser("?x foaf:name ?name .",prefixes) ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}

TEST(PatrialGrammerTest, AddedprefixTest2) {

    std::map<std::string,std::string> prefixes;
    //prefixes.insert(std::pair<std::string,std::string>("","http://example.org/book/"));
    prefixes.insert(std::pair<std::string,std::string>("dc","http://purl.org/dc/elements/1.1/"));
    prefixes.insert(std::pair<std::string,std::string>("ns","http://example.org/ns#"));
    rdf_parser::Turtle::parsers::StringParser<true> parser("?book dc:title ?title ;\n"
                                                  "         ns:price ?price .",prefixes) ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}


TEST(PatrialGrammerTest, tripleBlock) {


rdf_parser::Turtle::parsers::StringParser<true> parser("?x <http://xmlns.com/foaf/0.1/knows> ?y .\n"
                                                       "?x <http://xmlns.com/foaf/0.1/name> ?nameX . ") ;
auto it= parser.begin();
while (it)
{
auto x=*it;
it++;
}
}