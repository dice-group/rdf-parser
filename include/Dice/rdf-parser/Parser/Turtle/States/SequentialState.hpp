//
// Created by fakhr on 14.01.21.
//

#ifndef RDF_PARSER_SEQUENTIALSTATE_HPP
#define RDF_PARSER_SEQUENTIALSTATE_HPP



/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/



#include "Dice/rdf-parser/Parser/Turtle/States/State.hpp"


namespace Dice::rdf_parser::Turtle::States {

    /*
       * SequentialState deal with the logic of Sequential parsing  (parsed triples cant be accessed until all the file or the string is parsed). It is a base class for SequentialState and ConcurrentState
       */
    template<bool sparqlQuery>
    class SequentialState : public State<sparqlQuery> {
        using Term = Dice::rdf::Term;
        using Triple = Dice::rdf::Triple;
        using TriplePattern = Dice::sparql::TriplePattern;
        using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

    private:
        std::shared_ptr<std::queue<Triple_t>> parsed_elements;

    public:
        SequentialState(std::shared_ptr<std::queue<Triple_t>> parsingQueue) : parsed_elements(parsingQueue) {};

        inline void syncWithMainThread() {
        }

        inline void insertTriple(Triple_t triple) {
            this->parsed_elements->push(std::move(triple));
        }

        void setParsingIsDone() {
        }


    };
}

#endif //RDF_PARSER_SEQUENTIALSTATE_HPP
