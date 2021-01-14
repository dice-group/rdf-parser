#ifndef RDF_PARSER_BASICACTIONS_HPP
#define RDF_PARSER_BASICACTIONS_HPP


/**
Actions define how to deal with the parsed grammars during the parsing and allow to store information in the states.
For more information about actions please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#

This file contains the actions required for parsing RDF term .
*/


#include "Dice/SPARQL/Variable.hpp"
#include "Dice/rdf-parser/Parser/Turtle/Grammar.hpp"
#include "Dice/rdf-parser/Parser/Turtle/States/BasicState.hpp"

namespace Dice::rdf_parser::Turtle::Actions {

	template<typename Rule>
	struct action : ::tao::pegtl::nothing<Rule> {};

	template<>
	struct action<Grammar::directive> : ::tao::pegtl::discard_input {};

	template<bool SparqlQuery>
	struct action<Grammar::tripleExtended<SparqlQuery>> : tao::pegtl::discard_input {};


	template<>
	struct action<Grammar::base> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string ignore;
			std::string value;

			ss >> ignore;//read PREFIX and ignore it
			ss >> value; //read the value
			value.erase(0, 1);
			value.erase(value.length() - 1, 1);

			state.setBase(std::move(value));
		}
	};

	template<>
	struct action<Grammar::prefixID> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string prefix;
			std::string ignore;
			std::string value;

			ss >> ignore;                        //read @prefix and ignore it
			ss >> prefix;                        //read the prefix
			prefix.erase(prefix.length() - 1, 1);// erase : at the end of the prefix
			ss >> value;                         //read the value
			value.erase(0, 1);
			value.erase(value.length() - 1, 1);

			state.addPrefix(prefix, value);
		}
	};

	template<>
	struct action<Grammar::sparqlPrefix> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string prefix;
			std::string ignore;
			std::string value;

			ss >> ignore;                        //read PREFIX and ignore it
			ss >> prefix;                        //read the prefix
			prefix.erase(prefix.length() - 1, 1);// erase : at the end of the prefix
			ss >> value;                         //read the value
			value.erase(0, 1);
			value.erase(value.length() - 1, 1);

			state.addPrefix(prefix, value);
		}
	};


	template<>
	struct action<Grammar::sparqlBase> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string ignore;
			std::string value;

			ss >> ignore;//read PREFIX and ignore it
			ss >> value; //read the value
			value.erase(0, 1);
			value.erase(value.length() - 1, 1);

			state.setBase(std::move(value));
		}
	};

	template<>
	struct action<Grammar::PrefixedName> {
		using URIRef = Dice::rdf::URIRef;
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string statement;
			std::string prefix;
			std::string value;

			ss >> statement;//read the whole statement
			int pos = statement.find(':');
			prefix = statement.substr(0, pos);

			if (auto mappedPrefix_opt = state.getPrefixValue(prefix);
				mappedPrefix_opt.has_value()) {
				const std::string &mappedPrefix = mappedPrefix_opt.value();
				state.setElement(URIRef(mappedPrefix + statement.substr(pos + 1, statement.length() - prefix.length())));
				state.setIri_is_IRIREF(false);
			} else {
				throw std::runtime_error("undefined prefix");
			}
		};
	};

	template<>
	struct action<Grammar::IRIREF> {
		using URIRef = Dice::rdf::URIRef;
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str().substr(1, ss.str().length() - 2);
			//check for @base
			if (not state.getBase().empty())
				s = s.insert(1, state.getBase());

			state.setElement(URIRef(s));
			state.setIri_is_IRIREF(true);
		}
	};

	template<>
	struct action<Grammar::ANON> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			state.setBlank_node_string(state.createBlankNodeLabel());
		};
	};

	template<>
	struct action<Grammar::BooleanLiteral> {
		using Literal = Dice::rdf::Literal;
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str();

			state.setLiteral_string(std::move(s));// TODO: is that necessary
			state.setElement(Literal(state.getLiteral_string(), std::nullopt, "xsd:boolean"));
		}
	};

	template<>
	struct action<Grammar::DOUBLE> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			state.setType_tag("xsd:double");
		}
	};

	template<>
	struct action<Grammar::DECIMAL> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			state.setType_tag("xsd:decimal");
		}
	};

	template<>
	struct action<Grammar::INTEGER> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			state.setType_tag("xsd:integer");
		}
	};

	template<>
	struct action<Grammar::NumericLiteral> {
		using Literal = Dice::rdf::Literal;

		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str();

			state.setElement(Literal(s, std::nullopt, state.getType_tag()));
		}
	};

	template<>
	struct action<Grammar::RdfLiteral> {
		using Literal = Dice::rdf::Literal;

		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			//check if this RdfLiteral has IRI part
			if (state.isTypeTagFound()) {
				std::string tag;
				//set it again to false
				state.setType_tag_found(false);

				const std::string &type_tag = state.getType_tag();
				//check if the type tag is iri or PREFIXED NAME and process it accordingly
				if (not state.iriIsIRIREF()) {
					size_t pos = type_tag.find(':');
					std::string prefix = type_tag.substr(0, pos);
					if (auto mappedPrefix_opt = state.getPrefixValue(prefix);
						mappedPrefix_opt.has_value()) {
						const std::string &mappedPrefix = mappedPrefix_opt.value();
						tag = mappedPrefix + type_tag.substr(pos + 1, type_tag.length());
					} else {
						tag = type_tag;
					}
				} else {
					tag = type_tag;
				}
				state.setElement(Literal{state.getLiteral_string(), std::nullopt, tag});
			}
			//check if this RdfLiteral has langTag part
			else if (state.isLangTagFound()) {
				//set it again to false
				state.setLang_tag_found(false);
				state.setElement(Literal(state.getLiteral_string(), state.getLang_tag(), std::nullopt));
			} else {
				state.setElement(Literal(state.getLiteral_string(), std::nullopt, std::nullopt));
			}
		}
	};

	template<>
	struct action<Grammar::RdfLiteralTypeTag> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {

			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str();

			state.setType_tag_found(true);
			//check if the iri is IRIREF or a PerfixedName
			if (state.iriIsIRIREF())
				// set the Literal type tag without the "^^<" at the beginning amd without ">" at the end .
				state.setType_tag(s.substr(3, s.length() - 3 - 1));
			else
				state.setType_tag(s.substr(2));
		}
	};

	template<>
	struct action<Grammar::LANGTAG> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str().substr(1);


			state.setLang_tag_found(true);
			state.setLan_tag(std::move(s));
		}
	};

	template<>
	struct action<Grammar::turtleString> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str().substr(1, ss.str().length() - 1 - 1);
			state.setLiteral_string(std::move(s));
		}
	};


	template<>
	struct action<Grammar::BlankNode> {
		using BNode = Dice::rdf::BNode;
		using Variable = Dice::sparql::Variable;


		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			if constexpr (not SparqlQuery)
				state.setElement(BNode(state.getBlank_node_string()));
			else
				state.setElement(Variable(state.getBlank_node_string()));
		}
	};


	template<>
	struct action<Grammar::verb_a> {
		using URIRef = Dice::rdf::URIRef;
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::string fixedURI = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
			state.setElement(URIRef(fixedURI));
		};
	};


	template<>
	struct action<Grammar::BLANK_NODE_LABEL> {
		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str().substr(2);

			state.setLiteral_string(std::move(s));// TODO: is that necessary
			state.setBlank_node_string(state.getLiteral_string());
		};
	};

	template<>
	struct action<Grammar::var> {
		using Variable = Dice::sparql::Variable;

		template<typename Input, bool SparqlQuery>
		static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
			std::stringstream ss;
			ss << in.string();
			std::string s;
			s = ss.str().substr(1, ss.str().length() - 1);
			state.setElement(Variable(s));
			;
		}
	};
}// namespace Dice::rdf_parser::Turtle::Actions

#endif//RDF_PARSER_BASICACTIONS_HPP
