#ifndef RDF_PARSER_BASICACTIONS_HPP
#define RDF_PARSER_BASICACTIONS_HPP


/**
Actions define how to deal with the parsed grammers during the parsing and allow to store information in the states.
For more information about actions please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#

This file contains the actions required for pasrsing RDF term .
*/


#include "Dice/rdf-parser/Sparql/TripleVariable.hpp"
#include "Dice/rdf-parser/Parser/Turtle/Grammer.hpp"
#include "Dice/rdf-parser/Parser/Turtle/States/BasicState.hpp"

namespace rdf_parser::Turtle::Actions {

		template<typename Rule>
		struct action : ::tao::pegtl::nothing<Rule> {};

		template<>
		struct action<Grammer::directive> : ::tao::pegtl::discard_input {};

		template<bool SparqlQuery>
		struct action<Grammer::tripleExtended<SparqlQuery>> : tao::pegtl::discard_input {};

		template<>
		struct action<Grammer::base> {
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

				state.setBase(value);
			}
		};

		template<>
		struct action<Grammer::prefixID> {
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
		struct action<Grammer::sparqlPrefix> {
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
		struct action<Grammer::sparqlBase> {
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

				state.setBase(value);
			}
		};

		template<>
		struct action<Grammer::PrefixedName> {
			using URIRef = rdf_parser::store::rdf::URIRef;
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
					mappedPrefix_opt.has_value()){
					const std::string &mappedPrefix = mappedPrefix_opt.value();
					state.setElement(URIRef(mappedPrefix + statement.substr(pos + 1, statement.length() - prefix.length())));
					state.setIri_is_IRIREF(false);
				} else {
					throw std::runtime_error("undefined prefix");
				}
			};
		};

		template<>
		struct action<Grammer::IRIREF> {
			using URIRef = rdf_parser::store::rdf::URIRef;
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
		struct action<Grammer::ANON> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				state.setBlank_node_string(state.createBlankNodeLabel());
			};
		};

		template<>
		struct action<Grammer::BooleanLiteral> {
			using Literal = rdf_parser::store::rdf::Literal;
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				std::stringstream ss;
				ss << in.string();
				std::string s;
				s = ss.str();

				state.setLiteral_string(s);
				state.setElement(Literal(s, std::nullopt, "xsd:boolean"));
			}
		};

		template<>
		struct action<Grammer::DOUBLE> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				state.setType_tag("xsd:double");
			}
		};

		template<>
		struct action<Grammer::DECIMAL> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				state.setType_tag("xsd:decimal");
			}
		};

		template<>
		struct action<Grammer::INTEGER> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				state.setType_tag("xsd:integer");
			}
		};

		template<>
		struct action<Grammer::NumericLiteral> {
			using Literal = rdf_parser::store::rdf::Literal;

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
		struct action<Grammer::RdfLiteral> {
			using Literal = rdf_parser::store::rdf::Literal;
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
		struct action<Grammer::RdfLiteralTypeTag> {
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
		struct action<Grammer::LANGTAG> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				std::stringstream ss;
				ss << in.string();
				std::string s;
				s = ss.str().substr(1);


				state.setLang_tag_found(true);
				state.setLan_tag(s);
			}
		};

		template<>
		struct action<Grammer::turtleString> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				std::stringstream ss;
				ss << in.string();
				std::string s;
				s = ss.str().substr(1, ss.str().length() - 1 - 1);
				state.setLiteral_string(s);
			}
		};


		template<>
		struct action<Grammer::BlankNode> {
			using BNode = rdf_parser::store::rdf::BNode;
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				if constexpr (not SparqlQuery)
					state.setElement(BNode(state.getBlank_node_string()));
				else
					state.setElement(rdf_parser::SparqlQuery::TripleVariable(state.getBlank_node_string()));
			}
		};


		template<>
		struct action<Grammer::verb_a> {
			using URIRef = rdf_parser::store::rdf::URIRef;
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				std::string fixedURI = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
				state.setElement(URIRef(fixedURI));
			};
		};


		template<>
		struct action<Grammer::BLANK_NODE_LABEL> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				std::stringstream ss;
				ss << in.string();
				std::string s;
				s = ss.str().substr(2);

				state.setLiteral_string(s);
				state.setBlank_node_string(s);
			};
		};

		template<>
		struct action<Grammer::var> {
			template<typename Input, bool SparqlQuery>
			static void apply(const Input &in, States::BasicState<SparqlQuery> &state) {
				std::stringstream ss;
				ss << in.string();
				std::string s;
				s = ss.str().substr(1, ss.str().length() - 1);
				state.setElement(SparqlQuery::TripleVariable(s));
				;
			}
		};
	}// namespace rdf_parser::Turtle

#endif//RDF_PARSER_BASICACTIONS_HPP
