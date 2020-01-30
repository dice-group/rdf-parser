#ifndef RDF_PARSER_BASICACTIONS_HPP
#define RDF_PARSER_BASICACTIONS_HPP


/**
Actions define how to deal with the parsed grammers during the parsing and allow to store information in the states.
For more information about actions please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#

This file contains the actions required for pasrsing RDF term .
*/


#include "Dice/rdf_parser/Parser/Turtle/Grammer.hpp"
#include "Dice/rdf_parser/Parser/Turtle/States/BasicState.hpp"

namespace {
    using namespace tao::pegtl;
}

namespace rdf_parser::Turtle {
    namespace Actions {

        template<typename Rule>
        struct action
                : nothing<Rule> {
        };


        template<>
        struct action<Grammer::directive> : tao::pegtl::discard_input {
        };

        template<>
        struct action<Grammer::tripleExtended> : tao::pegtl::discard_input {
        };


        template<>
        struct action<Grammer::UCHAR> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                //std::cout << in.string();
            }
        };

        template<>
        struct action<Grammer::PN_PREFIX> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                //std::cout << in.string();
            }
        };


        template<>
        struct action<Grammer::PN_LOCAL> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                //std::cout << "PN_LOCAL" << in.string() << std::endl;
            }
        };

        template<>
        struct action<Grammer::base> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string ignore;
                std::string value;

                ss >> ignore; //read PREFIX and ignore it
                ss >> value; //read the value
                value.erase(0, 1);
                value.erase(value.length() - 1, 1);

                state.setBase(value);
            }
        };

        template<>
        struct action<Grammer::prefixID> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string prefix;
                std::string ignore;
                std::string value;

                ss >> ignore; //read @prefix and ignore it
                ss >> prefix; //read the prefix
                prefix.erase(prefix.length() - 1, 1); // erase : at the end of the prefix
                ss >> value; //read the value
                value.erase(0, 1);
                value.erase(value.length() - 1, 1);

                state.addPrefix(prefix, value);

            }
        };

        template<>
        struct action<Grammer::sparqlPrefix> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string prefix;
                std::string ignore;
                std::string value;

                ss >> ignore; //read PREFIX and ignore it
                ss >> prefix; //read the prefix
                prefix.erase(prefix.length() - 1, 1); // erase : at the end of the prefix
                ss >> value; //read the value
                value.erase(0, 1);
                value.erase(value.length() - 1, 1);

                state.addPrefix(prefix, value);

            }
        };


        template<>
        struct action<Grammer::sparqlBase> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string ignore;
                std::string value;

                ss >> ignore; //read PREFIX and ignore it
                ss >> value; //read the value
                value.erase(0, 1);
                value.erase(value.length() - 1, 1);

                state.setBase(value);
            }
        };

        template<>
        struct action<Grammer::PrefixedName> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string statement;
                std::string prefix;
                std::string value;

                ss >> statement; //read the whole statement
                int pos = statement.find(':');
                prefix = statement.substr(0, pos);
                value = statement.substr(pos + 1, statement.length() - prefix.length());


                if (state.hasPrefix(prefix)) {
                    std::string mappedPrefix = state.getPrefixValue(prefix);
                    value = mappedPrefix + value;
                    state.setTerm(URIRef(value));
                    state.setIri_is_IRIREF(false);
                } else {
                    throw std::runtime_error("undefined prefix");
                }
            };

        };

        template<>
        struct action<Grammer::IRIREF> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string s;
                s = ss.str().substr(1, ss.str().length() - 2);
                //check for @base
                if (not state.getBase().empty())
                    s = s.insert(1, state.getBase());

                state.setTerm(URIRef(s));
                state.setIri_is_IRIREF(true);
            }
        };

        template<>
        struct action<Grammer::ANON> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                state.setBlank_node_string(state.createBlankNodeLabel());
            };
        };

        template<>
        struct action<Grammer::BooleanLiteral> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string s;
                s = ss.str();

                state.setLiteral_string(s);
                state.setTerm(Literal(s, std::nullopt, "xsd:boolean"));
            }
        };

        template<>
        struct action<Grammer::DOUBLE> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                state.setType_tag("xsd:double");
            }
        };

        template<>
        struct action<Grammer::DECIMAL> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                state.setType_tag("xsd:decimal");
            }
        };

        template<>
        struct action<Grammer::INTEGER> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                state.setType_tag("xsd:integer");
            }
        };

        template<>
        struct action<Grammer::NumericLiteral> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string s;
                s = ss.str();
                s = '"' + s + '"';

                state.setTerm(Literal(s, std::nullopt, state.getType_tag()));
            }
        };

        template<>
        struct action<Grammer::RdfLiteral> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                state.proccessRdfLiteral();
            }
        };

        template<>
        struct action<Grammer::RdfLiteralTypeTag> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {

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
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
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
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string s;
                s = ss.str().substr(1, ss.str().length() - 1 - 1);
                state.setLiteral_string(s);

            }
        };


        template<>
        struct action<Grammer::BlankNode> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                state.setTerm(BNode(state.getBlank_node_string()));
            }
        };


        template<>
        struct action<Grammer::verb_a> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::string fixedURI = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#type>";
                state.setTerm(URIRef(fixedURI));
            };
        };


        template<>
        struct action<Grammer::BLANK_NODE_LABEL> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                std::stringstream ss;
                ss << in.string();
                std::string s;
                s = ss.str().substr(2);

                state.setLiteral_string(s);
                state.setBlank_node_string(s);
            };
        };

        template<>
        struct action<Grammer::term> {
            template<typename Input>
            static void apply(const Input &in, States::BasicState &state) {
                //Here parsingIsDone lock is set to true
            }
        };

    }
}

#endif //RDF_PARSER_BASICACTIONS_HPP
