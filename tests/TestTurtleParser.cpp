#include <gtest/gtest.h>
#include <Dice/rdf_parser/TurtleParser.hpp>
#include <Dice/rdf_parser/Parser/Turtle/Parsers/FileParser.hpp>

namespace {
    using namespace rdf_parser::Turtle;
    using namespace rdf_parser::store::rdf;
}






//TEST(TestParser, StreamParser_swdfu8s_1MBChunk) {
//    int counter=0;
//    StreamParser parser("datasets/swdfu8.ttl",1024*1000);
//    while (parser.hasNextTriple()) {
//        parser.nextTriple();
//        counter++;
//    }
//    std::cout<<counter;
//
//}
//
//
//TEST(TestParser, FileParser_swdfu8s_1MBChunk) {
//    int counter=0;
//    FileParser parser("datasets/swdfu8.ttl");
//    while (parser.hasNextTriple()) {
//        //std::cout<<"1A1"<<std::endl;
//        parser.nextTriple();
//        if (counter%1000==0)
//         //std::cout<<counter<<std::endl;
//        counter++;
//    }
//    std::cout<<counter;
//
//}
//
////
////TEST(TestParser, CuncurrentStreamParser_swdfu8s_1MBChunk) {
////    int counter=0;
////    CuncurrentStreamParser parser("datasets/swdfu8.ttl",1024*1024,100000);
////    while (parser.hasTriple()) {
////        auto a= parser.getNextTriple();
//////        std::cout<<std::get<0>(a)->getValue()<<std::get<1>(a)->getValue()<<std::get<2>(a)->getValue()<<std::endl;
////        //counter++;
////    }
////    //std::cout<<counter;
////
////}
////
////
////
////TEST(TestParser, CuncurrentStreamParser_dbpedia_2GB_subset_1MBChunk) {
////    int counter=0;
////    CuncurrentStreamParser parser("datasets/dbpedia_2GB_subset.ttl",1024*1024*10,100000);
////    while (parser.hasTriple()) {
////        auto a= parser.getNextTriple();
////        counter++;
////    }
////    std::cout<<counter<<std::endl;
////
////}
//
//
//
//
//TEST(TestParser, swdfu8sStream2) {
//    int counter=0;
//    FileParser parser("datasets/swdfu8.ttl");
//    while (parser.hasNextTriple()) {
//         parser.nextTriple();
//        counter++;
//    }
//    std::cout<<counter;
//
//}
//
//
//
//TEST(TestParser,Parser_dbpedia_2GB_subset_1MBChunk) {
//    Parser Parser("datasets/dbpedia_2GB_subset.ttl");
//    int counter=0;
//    auto it=Parser.begin();
////    while (it){
////        it++;
////        counter++;
////    }
//    std::cout<<counter;
//}
//
//TEST(TestParser,Parser_swdfu8_1MBChunk) {
//    Parser Parser("datasets/swdfu8.ttl");
//    int counter=0;
//    auto it=Parser.begin();
//    while (it){
////        it++;
////        counter++;
//   }
//    std::cout<<counter;
//}
//
//
//
//TEST(TestParser,s) {
//    Parser<CuncurrentStreamParser> Parser("../datasets/g.nt");
//    auto it=Parser.begin();
//    while (it){
//        auto a=*it;
//        it++;
//    }
//}
//
//
//
//
TEST(TestParser,ss) {

     auto i=rdf_parser::Turtle::TermParser::makeTerm("\" hello  \"");
     auto i3=rdf_parser::Turtle::TermParser::isTermParsable("\" hello  \"");
     auto i4=rdf_parser::Turtle::TermParser::isTermParsable("\" hello  ");
     std::cout<<i.getIdentifier()<<std::endl;
     std::cout<<i3<<std::endl;
     std::cout<<i4<<std::endl;
}
//
//
TEST(TestParser,ssss) {

    rdf_parser::store::rdf::Term i("\" hello  \"");
    auto i3=rdf_parser::Turtle::TermParser::isTermParsable("\" hello  \"");
    auto i4=rdf_parser::Turtle::TermParser::isTermParsable("\" hello  ");
    std::cout<<i.getIdentifier()<<std::endl;
    std::cout<<i3<<std::endl;
    std::cout<<i4<<std::endl;
}
//
TEST(TestParser,sss) {
    TurtleParser<> Parser("../datasets/g.nt");
    int counter=0;
    //auto it=Parser.begin();
    TurtleParser<>::Iterator  it=Parser.begin();
    while (it){
        Triple triple= *it;
        std::cout<<"subject :"<<triple.subject().getIdentifier()<<",predicit :"<<triple.predicate().getIdentifier()<<",object :"<<triple.object().getIdentifier()<<std::endl;
        it++;
        counter++;
    }
    std::cout<<counter;
}