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


    class ConcurrentState : public State<sparqlQuery,std::queue<std::conditional_t<sparqlQuery, Dice::sparql::TriplePattern, Dice::rdf::Triple>>>
    {
    private:


    };
}

#endif //RDF_PARSER_SEQUENTIALSTATE_HPP
