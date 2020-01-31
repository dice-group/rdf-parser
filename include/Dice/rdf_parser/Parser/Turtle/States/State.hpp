#ifndef RDF_PARSER_STATE_HPP
#define RDF_PARSER_STATE_HPP

/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/

#include <stack>
#include <queue>

#include "BasicState.hpp"
#include "Dice/rdf_parser/RDF/Triple.hpp"

namespace {
    using BnplCollectionList=std::vector<Term>;
    using VerbObjectPair=std::pair<Term, Term>;
}


namespace rdf_parser::Turtle {
    namespace States {

        /*
        * State defines the data structures realted to the whole grammer (stores the parsed triples)
        */
        template<typename T=std::queue<Triple>>
        class State : public BasicState {

        protected:

            std::shared_ptr<T> parsed_terms;


            //we use this to slove the case when 2 verbs are pushed into the stack without a pop between
            //to solve the PredicateObjectList recursive problem.
            std::stack<Term> verb_stack;
            int verb_stack_one_step_pre_size = 0;
            int verb_stack_two_step_pre_size = 0;

            Term subject;


            //deal with multi terms and nesting
            BnplCollectionList bnpl_collection_list;
            //stack for dealing with collections
            std::stack<BnplCollectionList> bnpl_collection_list_stack;

            std::vector<VerbObjectPair> verb_object_pair_list;
            std::stack<std::vector<VerbObjectPair>> verb_object_pair_list_stack;
            //to deal with the case when there are BNPL + optional predicateObjectList
            Term first_BNPL;


        public:

            explicit State(std::shared_ptr<T> &parsingQueue) {
                if (parsingQueue == nullptr)
                    parsingQueue = std::make_shared<T>();
                parsed_terms = parsingQueue;
            }

            virtual inline void syncWithMainThread() {
            }

            virtual inline void insertTriple(Triple triple) {
                this->parsed_terms->push(std::move(triple));
            }

            virtual void setPasrsingIsDone() {
            }



            inline void clearTripleParameters() {
//                first_BNPL = nullptr;
                verb_stack_two_step_pre_size = 0;
                verb_stack_one_step_pre_size = 0;
                bnpl_collection_list.clear();
                verb_object_pair_list.clear();
                bnpl_collection_list.clear();
            }


            inline void setSubject(Term subject) {
                this->subject = std::move(subject);
            }


            void proccessVerb() {
                verb_stack_two_step_pre_size = verb_stack_one_step_pre_size;
                verb_stack_one_step_pre_size = verb_stack.size();
                verb_stack.push(term);
                //
                if (verb_stack.size() == verb_stack_two_step_pre_size + 2) {
                    verb_object_pair_list_stack.push(verb_object_pair_list);
                    verb_object_pair_list.clear();
                }
            }

            void proccessCollection() {
                std::vector<Triple> LocalParsedTerms;
                URIRef first("rdf:first");
                URIRef rest("rdf:rest");
                URIRef nil("rdf:nil");
                if (bnpl_collection_list.size() == 0) {
                    BNode unlabeledNode(createBlankNodeLabel());
                    Triple triple(unlabeledNode, first, nil);
                    LocalParsedTerms.push_back(triple);
                    term = unlabeledNode;
                } else {
                    bool lastElement = true;
                    for (auto object = bnpl_collection_list.rbegin();
                         object != bnpl_collection_list.rend(); object++) {
                        BNode unlabeledNode(createBlankNodeLabel());
                        Triple triple1;
                        triple1.setSubject(unlabeledNode);
                        triple1.setPredicate(rest);

                        Triple triple2(unlabeledNode, first, *object);
                        //case 1 :last element :
                        if (lastElement) {
                            lastElement = false;
                            triple1.setObject(nil);

                        } else {
                            triple1.setObject((LocalParsedTerms[LocalParsedTerms.size() - 1]).subject());
                        }
                        term = unlabeledNode;
                        LocalParsedTerms.push_back(triple1);
                        LocalParsedTerms.push_back(triple2);

                    }
                }
                for (auto triple:LocalParsedTerms)
                    insertTriple(triple);
                bnpl_collection_list.clear();
                bnpl_collection_list = bnpl_collection_list_stack.top();
                bnpl_collection_list_stack.pop();

            }

            void proccessBlankNodePropertyList() {
                //ToDO : manage the unlabeled nodes names
                //create new Blank Node as subject
                BNode unlabeledNode(createBlankNodeLabel());
                //add the the unlabeledNode to object list
                term = unlabeledNode;
                auto verbobjectPairList = verb_object_pair_list;
                //go through all the VerbObject pairs and make triples out of them with the unlabeled subject
                for (auto &pair:verbobjectPairList) {
                    Triple triple(unlabeledNode, pair.first, pair.second);
                    insertTriple(triple);
                }
                verb_object_pair_list.clear();


                if (!verb_object_pair_list_stack.empty()) {
                    verb_object_pair_list = verb_object_pair_list_stack.top();
                    verb_object_pair_list_stack.pop();
                } else {
                    first_BNPL = unlabeledNode;
                }
                bnpl_collection_list = bnpl_collection_list_stack.top();
                bnpl_collection_list_stack.pop();

            }

            void proccessPredicateObjectListInner() {
                auto verb = verb_stack.top();
                verb_stack.pop();
                for (auto &object:bnpl_collection_list) {
                    verb_object_pair_list.push_back(std::make_pair<>(verb, object));
                }
                bnpl_collection_list.clear();
            }


            inline void proccessTripleSeq() {
                //add the subject to each pair in verbObjectsList and create a triple out of that
                for (auto &pair:verb_object_pair_list) {
                    Triple triple(subject, pair.first, pair.second);
                    //add the created triple into the store
                    insertTriple(triple);
                }
            }

            inline void moveBnpl_collection_listIntoStack() {
                bnpl_collection_list_stack.push(bnpl_collection_list);
                bnpl_collection_list.clear();

            }

            inline void pushCurrentTermIntoBnpl_collection_list() {
                bnpl_collection_list.push_back(term);
            }


            Term &getFirst_BNPL() {
                return first_BNPL;
            }


        };
    }
}


#endif //RDF_PARSER_STATE_HPP
