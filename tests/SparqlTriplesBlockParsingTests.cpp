
#include <gtest/gtest.h>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/TriplesBlockStringParser.hpp>

using namespace rdf_parser::Turtle;


TEST(SparqlTriplesBlockParsingTests, F1) {

    rdf_parser::Turtle::parsers::TriplesBlockStringParser parser("?g <sad> ?who . ") ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}

TEST(SparqlTriplesBlockParsingTests, AddedprefixTest) {

    std::map<std::string,std::string > prefixes;
    prefixes.insert(std::pair<std::string,std::string>("foaf","http://xmlns.com/foaf/0.1/"));
    rdf_parser::Turtle::parsers::TriplesBlockStringParser parser("?x foaf:name ?name .", prefixes) ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}

TEST(SparqlTriplesBlockParsingTests, AddedprefixTest2) {

    std::map<std::string,std::string> prefixes;
    //prefixes.insert(std::pair<std::string,std::string>("","http://example.org/book/"));
    prefixes.insert(std::pair<std::string,std::string>("dc","http://purl.org/dc/elements/1.1/"));
    prefixes.insert(std::pair<std::string,std::string>("ns","http://example.org/ns#"));
    rdf_parser::Turtle::parsers::TriplesBlockStringParser parser("?book dc:title ?title ;\n"
                                                  "         ns:price ?price .", prefixes) ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}


TEST(SparqlTriplesBlockParsingTests, tripleBlock) {


rdf_parser::Turtle::parsers::TriplesBlockStringParser parser("?x <http://xmlns.com/foaf/0.1/knows> ?y .\n"
                                                       "?x <http://xmlns.com/foaf/0.1/name> ?nameX . ") ;
auto it= parser.begin();
while (it)
{
auto x=*it;
it++;
}
}

TEST(SparqlTriplesBlockParsingTests, tripleBlock2) {

    std::map<std::string,std::string> prefixes;
    prefixes.insert(std::pair<std::string,std::string>("ex","http://example.org/"));
    rdf_parser::Turtle::parsers::TriplesBlockStringParser parser("?buch ex:hatVerlag <http://springer.com/Verlag> . ?buch ex:titel ?title . ?buch ex:autor ?autor . ", prefixes) ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        it++;
    }
}


TEST(SparqlTriplesBlockParsingTests, BlankNodes) {

    std::map<std::string,std::string> prefixes;
    prefixes.insert(std::pair<std::string,std::string>("wde","http://www.wikidata.org/entity/"));
    prefixes.insert(std::pair<std::string,std::string>("wdt","http://www.wikidata.org/prop/direct/"));
    rdf_parser::Turtle::parsers::TriplesBlockStringParser parser("?var1 <http://www.wikidata.org/prop/P463> _:b0 . _:b0 <http://www.wikidata.org/prop/statement/P463> wde:Q202479 ; <http://www.wikidata.org/prop/qualifier/P580> ?var2 .", prefixes) ;
    auto it= parser.begin();
    while (it)
    {
        auto x=*it;
        rdf_parser::SparqlQuery::VarOrTerm object=x.object();
        rdf_parser::SparqlQuery::VarOrTerm predicate=x.predicate();
        rdf_parser::SparqlQuery::VarOrTerm subject=x.subject();
        it++;
    }
}