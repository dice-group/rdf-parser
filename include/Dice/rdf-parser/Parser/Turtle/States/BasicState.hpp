
#ifndef RDF_PARSER_BASICSTATE_HPP
#define RDF_PARSER_BASICSTATE_HPP


/**
States store information needed during and after the parsing.
For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states

*/



#include <memory>
#include <map>
#include <string>
#include <optional>

#include "Dice/rdf-parser/RDF/Term.hpp"
#include "Dice/rdf-parser/Sparql/TriplePatternElement.hpp"


namespace {
    using namespace rdf_parser::store::rdf;
}


namespace rdf_parser::Turtle {
    namespace States {

        /*
         * BasicState defines the data structures realted to rdf term
         */
        template<bool sparqlQuery=false>
        class BasicState {
        public:
            BasicState()
            {
                element=std::make_shared<std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>>();
            }
        protected:

            std::shared_ptr<std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term>> element;

            //variables to deal with type and lan tags in literals
            bool type_tag_found = false;
            bool lang_tag_found = false;
            bool iri_is_IRIREF;
            std::string lan_tag;
            std::string type_tag;
            std::string literal_string;
            std::string Blank_node_string;

            //dealing with base directives
            std::string base = "";

            int latest_BN_label = 1;

            std::map<std::string, std::string> prefix_map;


        public:
            inline std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term> &getElement() { return *element; }

            inline void setElement(std::conditional_t<sparqlQuery,SparqlQuery::VarOrTerm ,Term> element) { *(this->element) = std::move(element); }


            inline void addPrefix(std::string prefix, std::string value) {
                prefix_map.insert(std::pair<std::string, std::string>(prefix, value));
            }

            inline void setLan_tag(std::string lan_tag) { this->lan_tag = lan_tag; }

            inline void setType_tag(std::string type_tag) { this->type_tag = type_tag; }


            inline void setType_tag_found(bool found) {
                this->type_tag_found = found;
            }

            inline void setLang_tag_found(bool found) {
                this->lang_tag_found = found;
            }

            inline void setIri_is_IRIREF(bool found) {
                this->iri_is_IRIREF = found;
            }

            void proccessRdfLiteral() {
                //check if this RdfLiteral has IRI part
                if (type_tag_found == true) {
                    std::string tag;
                    //set it again to false
                    type_tag_found = false;
                    //check if the type tag is iri or PREFIXED NAME and process it accordingly
                    if (iriIsIRIREF()) {
                        tag = type_tag;
                    } else {
                        int pos = type_tag.find(':');
                        std::string prefix = type_tag.substr(0, pos);
                        tag = type_tag.substr(pos + 1, type_tag.length());
                        if (hasPrefix(prefix)) {
                            std::string mappedPrefix = getPrefixValue(prefix);
                            tag = mappedPrefix + tag;
                        } else
                            tag = type_tag;
                    }
                    *element = (Literal(literal_string, std::nullopt,
                                    tag));
                }
                    //check if this RdfLiteral has langTag part
                else if (lang_tag_found == true) {
                    //set it again to false
                    lang_tag_found = false;
                    *element = Literal(literal_string, lan_tag,
                                   std::nullopt);
                } else
                    *element = Literal(literal_string, std::nullopt,
                                   std::nullopt);
            }

            std::string getType_tag() {
                return type_tag;
            }

            bool iriIsIRIREF() {
                return iri_is_IRIREF;
            }

            std::string getBlank_node_string() {
                return Blank_node_string;
            }

            inline void setLiteral_string(std::string literal_string) { this->literal_string = literal_string; }

            inline void
            setBlank_node_string(std::string Blank_node_string) { this->Blank_node_string = Blank_node_string; }

            inline void setBase(std::string base) { this->base = base; }

            std::string getBase() { return base; }

            // create a unique label for a BlankNode
            std::string createBlankNodeLabel() {
                //TODO
                return "b" + std::to_string(latest_BN_label++);
            }

            inline bool hasPrefix(std::string prefix) {
                auto found = prefix_map.find(prefix);
                if (found != prefix_map.end())
                    return true;
                return false;
            }

            inline std::string getPrefixValue(std::string prefix) {
                auto found = prefix_map.find(prefix);
                return found->second;

            }

//            std::string processVar(std::string var)
//            {
//
//            }
        };
    }
}


#endif //RDF_PARSER_BASICSTATE_HPP
