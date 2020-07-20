#ifndef RDF_PARSER_ACTIONS_HPP
#define RDF_PARSER_ACTIONS_HPP

#include "BasicActions.hpp"
#include "Dice/rdf_parser/Parser/Turtle/States/State.hpp"

/**
Actions define how to deal with the parsed grammers during the parsing and allow to store information in the states.
For more information about actions please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#

This file contains the actions required for pasrsing RDF triples  in a whole file,stream or string.
*/


namespace rdf_parser::Turtle {
    namespace Actions {

        template<>
        struct action<Grammer::statement<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {

                state.syncWithMainThread();

            }
        };



        template<>
        struct action<Grammer::triple<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.clearTripleParameters();

            }
        };

        template<>
        struct action<Grammer::tripleSeq1<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {

                state.proccessTripleSeq();

            }
        };

        template<>
        struct action<Grammer::tripleSeq2<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {

                //add the unlabeled blank node from BNPL as subject
                state.setSubject(state.getFirst_BNPL());

                state.proccessTripleSeq();

            }
        };


        template<>
        struct action<Grammer::subject<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.setSubject(state.getElement());
            }
        };

        template<>
        struct action<Grammer::verb> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.proccessVerb();
            }
        };

        template<>
        struct action<Grammer::object<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
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

        template<>
        struct action<Grammer::collection<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
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

        template<>
        struct action<Grammer::blankNodePropertyList<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.proccessBlankNodePropertyList();
            }
        };


        template<>
        struct action<Grammer::predicateObjectListInner<> > {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                state.proccessPredicateObjectListInner();
            }
        };


        template<>
        struct action<Grammer::turtleDoc<>> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                //Here parsingIsDone lock is set to true
                state.setPasrsingIsDone();
            }
        };

        template<>
        struct action<Grammer::var> {
            template<typename Input, typename Queue,bool SparqlQuery>
            static void apply(const Input &in, States::State<SparqlQuery,Queue> &state) {
                //;
                ;
            }
        };


    }
}

#endif //RDF_PARSER_ACTIONS_HPP
