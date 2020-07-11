
#ifndef RDF_PARSER_SPARQLACTIONS_HPP
#define RDF_PARSER_SPARQLACTIONS_HPP

#include "Dice/rdf_parser/Parser/Turtle/Grammer.hpp"
#include "Dice/rdf_parser/Parser/Turtle/States/BasicState.hpp"
#include "Dice/rdf_parser/Sparql/TripleVariable.hpp"
/**
Actions define how to deal with the parsed grammers during the parsing and allow to store information in the states.
For more information about actions please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#

The following actions are not part of turtle.they are part of sparql language.but used here to make it
 possible to parse some sparql grammer which has very similar context to turtle.
*/


template<>
struct action<Grammer::var> {
    template<typename Input>
    static void apply(const Input &in, States::BasicState &state) {
        state.proccessRdfLiteral();
    }
};



#endif //RDF_PARSER_SPARQLACTIONS_HPP
