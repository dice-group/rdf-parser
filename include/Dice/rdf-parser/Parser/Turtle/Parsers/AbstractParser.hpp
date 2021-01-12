#ifndef RDF_PARSER_ABSTRACTPARSER_HPP
#define RDF_PARSER_ABSTRACTPARSER_HPP

#include "Dice/RDF/Triple.hpp"
#include "Dice/SPARQL/TriplePattern.hpp"


/**
 * Base class for parsing triples from different sources.
 */

namespace Dice::rdf_parser::Turtle::parsers {

	template<class Derived, bool sparqlQuery>
	class Iterator;

	template<class Derived, bool sparqlQuery>
	class AbstractParser {
		using Term = Dice::rdf::Term;
		using URIRef = Dice::rdf::URIRef;
		using Literal = Dice::rdf::Literal;
		using BNode = Dice::rdf::BNode;
		using Variable = Dice::sparql::Variable;
		using VarOrTerm = Dice::sparql::VarOrTerm;
		using Triple = Dice::rdf::Triple;
		using TriplePattern = Dice::sparql::TriplePattern;
		using Element_t = std::conditional_t<sparqlQuery, VarOrTerm, Term>;
		using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

	protected:
		using element_type = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

		explicit AbstractParser() {
			current_triple = std::make_shared<element_type>();
		};
		std::shared_ptr<element_type> current_triple;


	public:
		/**
         * process to the next parsed triple.
         */
		virtual void nextTriple() = 0;

		/**
         * check whether there is a further triple
         */
		virtual bool hasNextTriple() const = 0;

		/**
         * get the current triple
         */
		const element_type &getCurrentTriple() {
			return *current_triple;
		}


		virtual ~AbstractParser() = default;


		Iterator<Derived, sparqlQuery> begin() {
			return static_cast<Derived *>(this)->begin_implementation();
		}

		bool end() { return false; }
	};

	template<class Derived, bool sparqlQuery>
	class Iterator {
		using Term = Dice::rdf::Term;
		using URIRef = Dice::rdf::URIRef;
		using Literal = Dice::rdf::Literal;
		using BNode = Dice::rdf::BNode;
		using Variable = Dice::sparql::Variable;
		using VarOrTerm = Dice::sparql::VarOrTerm;
		using Triple = Dice::rdf::Triple;
		using TriplePattern = Dice::sparql::TriplePattern;
		using Element_t = std::conditional_t<sparqlQuery, VarOrTerm, Term>;
		using Triple_t = std::conditional_t<sparqlQuery, TriplePattern, Triple>;

	private:
		bool done_;
		bool parser_done_;
		Derived *triplesParser = nullptr;

	public:
		explicit Iterator(Derived *triplesParser) : done_{false}, parser_done_{false}, triplesParser{triplesParser} {
			//check if there is at least one parsed triple
			if (triplesParser->hasNextTriple())
				this->operator++();
			else
				parser_done_ = true;
		};


		void operator++() {
			if (parser_done_) {
				done_ = true;
			} else {
				triplesParser->nextTriple();
				if (not triplesParser->hasNextTriple())
					parser_done_ = true;
			}
		}

		void operator++(int) { operator++(); }

		operator bool() { return not done_; }

		const Triple_t &operator*() { return triplesParser->getCurrentTriple(); }
	};


};// namespace Dice::rdf_parser::Turtle::parsers


#endif//RDF_PARSER_ABSTRACTPARSER_HPP
