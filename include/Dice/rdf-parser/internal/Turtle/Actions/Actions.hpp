#ifndef RDF_PARSER_ACTIONS_HPP
#define RDF_PARSER_ACTIONS_HPP

#include "Dice/rdf-parser/internal/Turtle/Actions/BasicActions.hpp"
#include "Dice/rdf-parser/internal/Turtle/States/State.hpp"

/**
 * Actions define how to deal with the parsed grammars during the parsing and allow to store information in the states.
 * For more information about actions please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#
 * This file contains the actions required for parsing RDF triples  in a whole file,stream or string.
*/
namespace Dice::rdf_parser::internal::Turtle::Actions {

	template<>
	struct action<Grammar::statement> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.syncWithMainThread();
		}
	};


	template<bool SparqlQuery>
	struct action<Grammar::triple<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.clearTripleParameters();
		}
	};

	template<bool SparqlQuery>
	struct action<Grammar::tripleSeq1<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.processTripleSeq();
		}
	};

	template<bool SparqlQuery>
	struct action<Grammar::tripleSeq2<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			//add the unlabeled blank node from BNPL as subject
			state.setSubject(state.getFirst_BNPL());
			state.processTripleSeq();
		}
	};


	template<bool SparqlQuery>
	struct action<Grammar::subject<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.setSubject(state.getElement());
		}
	};

	template<bool SparqlQuery>
	struct action<Grammar::verb<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.processVerb();
		}
	};

	template<bool SparqlQuery>
	struct action<Grammar::object<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.pushCurrentTermIntoBnpl_collection_list();
		}
	};


	template<>
	struct action<Grammar::collectionBegin> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.moveBnpl_collection_listIntoStack();
		}
	};

	template<bool SparqlQuery>
	struct action<Grammar::collection<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.processCollection();
		}
	};

	template<>
	struct action<Grammar::blankNodePropertyListBegin> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.moveBnpl_collection_listIntoStack();
		}
	};

	template<bool SparqlQuery>
	struct action<Grammar::blankNodePropertyList<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.processBlankNodePropertyList();
		}
	};


	template<bool SparqlQuery>
	struct action<Grammar::predicateObjectListInner<SparqlQuery>> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			state.processPredicateObjectListInner();
		}
	};


	template<>
	struct action<Grammar::turtleDoc> {
		template<typename Input, bool sparqlQuery, class Derived>
		static void apply(const Input &in, States::State<sparqlQuery, Derived> &state) {
			//Here parsingIsDone lock is set to true
			state.setParsingIsDone();
		}
	};
}// namespace Dice::rdf_parser::internal::Turtle::Actions

#endif//RDF_PARSER_ACTIONS_HPP
