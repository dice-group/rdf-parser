#ifndef RDF_PARSER_STATE_HPP
#define RDF_PARSER_STATE_HPP

/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/

#include <stack>
#include <queue>

#include <Dice/rdf_parser/RDF/Triple.hpp>
#include "BasicState.hpp"




namespace rdf_parser::Turtle {
    namespace States {

        /*
        * State defines the data structures realted to the whole grammer (stores the parsed triples)
        */
        template<bool sparqlQuery=false,typename T=std::queue< std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple>>>
        class State : public BasicState<sparqlQuery> {

        protected:

            using BnplCollectionList=std::vector<std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>>;
            using VerbObjectPair=std::pair<std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>, std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>>;

            std::shared_ptr<T> parsed_elements;


            //we use this to slove the case when 2 verbs are pushed into the stack without a pop between
            //to solve the PredicateObjectList recursive problem.
            std::stack<std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>> verb_stack;
            int verb_stack_one_step_pre_size = 0;
            int verb_stack_two_step_pre_size = 0;

            std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>  subject;


            //deal with multi terms and nesting
            BnplCollectionList bnpl_collection_list;
            //stack for dealing with collections
            std::stack<BnplCollectionList> bnpl_collection_list_stack;

            std::vector<VerbObjectPair> verb_object_pair_list;
            std::stack<std::vector<VerbObjectPair>> verb_object_pair_list_stack;
            //to deal with the case when there are BNPL + optional predicateObjectList
            std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>  first_BNPL;


        public:

            explicit State(std::shared_ptr<T> &parsingQueue) {
                if (parsingQueue == nullptr)
                    parsingQueue = std::make_shared<T>();
                parsed_elements = parsingQueue;
            }

            virtual inline void syncWithMainThread() {
            }

            virtual inline void insertTriple(std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple> triple) {
                this->parsed_elements->push(std::move(triple));
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


            inline void setSubject(std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>  subject) {
                this->subject = std::move(subject);
            }


            void proccessVerb() {
                verb_stack_two_step_pre_size = verb_stack_one_step_pre_size;
                verb_stack_one_step_pre_size = verb_stack.size();
                verb_stack.push(this->getElement());
                //
                if (verb_stack.size() == verb_stack_two_step_pre_size + 2) {
                    verb_object_pair_list_stack.push(verb_object_pair_list);
                    verb_object_pair_list.clear();
                }
            }

            void proccessCollection() {
                std::vector<std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple>> LocalParsedTerms;
                URIRef first("rdf:first");
                URIRef rest("rdf:rest");
                URIRef nil("rdf:nil");
                if (bnpl_collection_list.size() == 0) {
                    BNode unlabeledNode(this->createBlankNodeLabel());
                    std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple> triple(unlabeledNode, first, nil);
                    LocalParsedTerms.push_back(triple);
                    *(this->element)= unlabeledNode;
                } else {
                    bool lastElement = true;
                    for (auto object = bnpl_collection_list.rbegin();
                         object != bnpl_collection_list.rend(); object++) {
                        BNode unlabeledNode(this->createBlankNodeLabel());
                        std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple> triple1;
                        triple1.setSubject(unlabeledNode);
                        triple1.setPredicate(rest);

                        std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple> triple2(unlabeledNode, first, *object);
                        //case 1 :last element :
                        if (lastElement) {
                            lastElement = false;
                            triple1.setObject(nil);

                        } else {
                            triple1.setObject((LocalParsedTerms[LocalParsedTerms.size() - 1]).subject());
                        }
                        *(this->element) = unlabeledNode;
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
                BNode unlabeledNode(this->createBlankNodeLabel());
                //add the the unlabeledNode to object list
                *(this->element) = unlabeledNode;
                auto verbobjectPairList = verb_object_pair_list;
                //go through all the VerbObject pairs and make triples out of them with the unlabeled subject
                for (auto &pair:verbobjectPairList) {
                    std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple> triple(unlabeledNode, pair.first, pair.second);
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
                    std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple> triple(subject, pair.first, pair.second);
                    //add the created triple into the store
                    insertTriple(triple);
                }
            }

            inline void moveBnpl_collection_listIntoStack() {
                bnpl_collection_list_stack.push(bnpl_collection_list);
                bnpl_collection_list.clear();

            }

            inline void pushCurrentTermIntoBnpl_collection_list() {
                bnpl_collection_list.push_back(this->getElement());
            }


            std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term> &getFirst_BNPL() {
                return first_BNPL;
            }


        };
    }
}


#endif //RDF_PARSER_STATE_HPP
