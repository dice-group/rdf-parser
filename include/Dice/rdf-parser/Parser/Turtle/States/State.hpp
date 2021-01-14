#ifndef RDF_PARSER_STATE_HPP
#define RDF_PARSER_STATE_HPP

/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/

#include <queue>
#include <stack>

#include "Dice/RDF/Triple.hpp"
#include "Dice/SPARQL/TriplePattern.hpp"
#include "Dice/rdf-parser/Parser/Turtle/States/BasicState.hpp"


namespace Dice::rdf_parser::Turtle::States {

	/*
        * State defines the data structures related to the whole grammar (stores the parsed triples)
        */
	template<bool sparqlQuery = false, typename Queue_t<class s>>
	class State : public BasicState<sparqlQuery> {
    protected:
		using Term = Dice::rdf::Term;
		using URIRef = Dice::rdf::URIRef;
		using Literal = Dice::rdf::Literal;
		using BNode = Dice::rdf::BNode;
		using VarOrTerm = Dice::sparql::VarOrTerm;
		using Triple = Dice::rdf::Triple;
		using TriplePattern = Dice::sparql::TriplePattern;
		using Element_t = std::conditional_t<sparqlQuery, VarOrTerm, Term>;
		using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

	protected:
		/**
			 * Blank Node Property List
			 */
		using BnplCollectionList = std::vector<Element_t>;
		using VerbObjectPair = std::pair<Element_t, Element_t>;

		std::shared_ptr<T> parsed_elements;


		//we use this to solve the case when 2 verbs are pushed into the stack without a pop between
		//to solve the PredicateObjectList recursive problem.
		std::stack<Element_t> verb_stack;
		int verb_stack_one_step_pre_size = 0;
		int verb_stack_two_step_pre_size = 0;

		Element_t subject_;


		//deal with multi terms and nesting
		BnplCollectionList bnpl_collection_list;
		//stack for dealing with collections
		std::stack<BnplCollectionList> bnpl_collection_list_stack;

		std::vector<VerbObjectPair> verb_object_pair_list;
		std::stack<std::vector<VerbObjectPair>> verb_object_pair_list_stack;
		//to deal with the case when there are BNPL + optional predicateObjectList
		Element_t first_BNPL;


	public:
		explicit State(std::shared_ptr<T> &parsingQueue) {
			if (parsingQueue == nullptr)
				parsingQueue = std::make_shared<T>();
			parsed_elements = parsingQueue;
		}

		virtual inline void syncWithMainThread() {
		}

		virtual inline void insertTriple(Triple_t triple) {
			this->parsed_elements->push(std::move(triple));
		}

		virtual void setParsingIsDone() {
		}


		inline void clearTripleParameters() {
			verb_stack_two_step_pre_size = 0;
			verb_stack_one_step_pre_size = 0;
			bnpl_collection_list.clear();
			verb_object_pair_list.clear();
			bnpl_collection_list.clear();
		}


		inline void setSubject(Element_t subject) {
			this->subject_ = std::move(subject);
		}


		void processVerb() {
			verb_stack_two_step_pre_size = verb_stack_one_step_pre_size;
			verb_stack_one_step_pre_size = verb_stack.size();
			verb_stack.push(this->getElement());
			//
			if (verb_stack.size() == verb_stack_two_step_pre_size + 2) {
				verb_object_pair_list_stack.push(verb_object_pair_list);
				verb_object_pair_list.clear();
			}
		}

		void processCollection() {
			std::vector<Triple_t> LocalParsedTerms;
			URIRef first("rdf:first");
			URIRef rest("rdf:rest");
			URIRef nil("rdf:nil");
			if (bnpl_collection_list.size() == 0) {
				BNode unlabeledNode(this->createBlankNodeLabel());
				Triple_t triple(unlabeledNode, first, nil);
				LocalParsedTerms.push_back(triple);
				*(this->element_) = unlabeledNode;
			} else {
				bool lastElement = true;
				for (auto object = bnpl_collection_list.rbegin();
					 object != bnpl_collection_list.rend(); object++) {
					BNode unlabeledNode(this->createBlankNodeLabel());
					Triple_t triple1;
					triple1.setSubject(unlabeledNode);
					triple1.setPredicate(rest);

					Triple_t triple2(unlabeledNode, first, *object);
					//case 1 :last element_ :
					if (lastElement) {
						lastElement = false;
						triple1.setObject(nil);

					} else {
						triple1.setObject((LocalParsedTerms[LocalParsedTerms.size() - 1]).subject());
					}
					*(this->element_) = unlabeledNode;
					LocalParsedTerms.push_back(triple1);
					LocalParsedTerms.push_back(triple2);
				}
			}
			for (auto triple : LocalParsedTerms)
				insertTriple(triple);
			bnpl_collection_list.clear();
			bnpl_collection_list = bnpl_collection_list_stack.top();
			bnpl_collection_list_stack.pop();
		}

		void processBlankNodePropertyList() {
			//create new Blank Node as subject
			BNode unlabeledNode(this->createBlankNodeLabel());
			//add the the unlabeledNode to object list
			*(this->element_) = unlabeledNode;
			auto verbObjectPairList = verb_object_pair_list;
			//go through all the VerbObject pairs and make triples out of them with the unlabeled subject
			for (auto &pair : verbObjectPairList) {
				Triple_t triple(unlabeledNode, pair.first, pair.second);
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

		void processPredicateObjectListInner() {
			auto verb = verb_stack.top();
			verb_stack.pop();
			for (auto &object : bnpl_collection_list) {
				verb_object_pair_list.push_back(std::make_pair<>(verb, object));
			}
			bnpl_collection_list.clear();
		}


		inline void processTripleSeq() {
			//add the subject to each pair in verbObjectsList and create a triple out of that
			for (auto &pair : verb_object_pair_list) {
				Triple_t triple(subject_, pair.first, pair.second);
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


		Element_t &getFirst_BNPL() {
			return first_BNPL;
		}
	};
}// namespace Dice::rdf_parser::Turtle::States


#endif//RDF_PARSER_STATE_HPP
