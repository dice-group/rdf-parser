#ifndef RDF_PARSER_ACTIONS_HPP
#define RDF_PARSER_ACTIONS_HPP

#include "BasicActions.hpp"
#include "Dice/rdf-parser/Parser/Turtle/States/State.hpp"

/**
Actions define how to deal with the parsed grammers during the parsing and allow to store information in the states.
For more information about actions please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#

This file contains the actions required for pasrsing RDF triples  in a whole file,stream or string.
*/


namespace rdf_parser::Turtle {
    namespace Actions {

        template<>
        struct action<Grammer::statement> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {

                state.syncWithMainThread();

            }
        };



        template<bool SparqlQuery>
        struct action<Grammer::triple<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.clearTripleParameters();

            }
        };

        template<bool SparqlQuery>
        struct action<Grammer::tripleSeq1<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {

                state.proccessTripleSeq();

            }
        };

        template<bool SparqlQuery>
        struct action<Grammer::tripleSeq2<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {

                //add the unlabeled blank node from BNPL as subject
                state.setSubject(state.getFirst_BNPL());

                state.proccessTripleSeq();

            }
        };


        template<bool SparqlQuery>
        struct action<Grammer::subject<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.setSubject(state.getElement());
            }
        };

        template<bool SparqlQuery>
        struct action<Grammer::verb<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.proccessVerb();
            }
        };

        template<bool SparqlQuery>
        struct action<Grammer::object<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.pushCurrentTermIntoBnpl_collection_list();
            }
        };


        template<>
        struct action<Grammer::collectionBegin> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.moveBnpl_collection_listIntoStack();
            }
        };

        template<bool SparqlQuery>
        struct action<Grammer::collection<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.proccessCollection();
            }
        };

        template<>
        struct action<Grammer::blankNodePropertyListBegin> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.moveBnpl_collection_listIntoStack();
            }
        };

        template<bool SparqlQuery>
        struct action<Grammer::blankNodePropertyList<SparqlQuery>> {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.proccessBlankNodePropertyList();
            }
        };


        template<bool SparqlQuery>
        struct action<Grammer::predicateObjectListInner<SparqlQuery> > {
            template<typename Input, typename Queue>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.proccessPredicateObjectListInner();
            }
        };


        template<>
        struct action<Grammer::turtleDoc> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                //Here parsingIsDone lock is set to true
                state.setPasrsingIsDone();
            }
        };





    }
}

#endif //RDF_PARSER_ACTIONS_HPP
