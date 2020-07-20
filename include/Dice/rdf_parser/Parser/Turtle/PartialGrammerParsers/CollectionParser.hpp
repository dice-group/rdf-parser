//
// Created by fakhr on 24.06.20.
//

#ifndef RDF_PARSER_COLLECTIONPARSER_HPP
#define RDF_PARSER_COLLECTIONPARSER_HPP


#include "Dice/rdf_parser/Parser/Turtle/States/State.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Actions/Actions.hpp"
#include <queue>
#include <tao/pegtl.hpp>

namespace {
using namespace  rdf_parser::store::rdf;
}

namespace rdf_parser::Turtle::PartialGrammerParsers {



    class CollectionParser {


    public:

        static std::shared_ptr<std::queue<SparqlQuery::TriplePatternElement>> ParseSparqlCollection(std::string text) {
            try {
                using namespace tao::pegtl;
                string_input input(text, "the collection");
                std::shared_ptr<std::queue<SparqlQuery::TriplePatternElement>> parsedTerms;
                States::State<true> state(parsedTerms);
                parse<Grammer::collection<true>, Actions::action>(input, state);
                return std::move(parsedTerms);
            }
            catch (std::exception &e) {
                throw e;
            }
        }
//        static bool isCollectionParsable(std::string text) {
//            try {
//                using namespace tao::pegtl;
//                string_input input(text, "the collection");
//                std::shared_ptr<std::queue<Triple>> parsedTerms;
//                parse<Grammer::collection,Actions::action>(input, state);
//                return true;
//            }
//            catch (std::exception &e) {
//                return false;
//            }
//        }


    };

};

#endif //RDF_PARSER_COLLECTIONPARSER_HPP
