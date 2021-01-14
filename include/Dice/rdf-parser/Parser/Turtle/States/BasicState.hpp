#ifndef RDF_PARSER_BASICSTATE_HPP
#define RDF_PARSER_BASICSTATE_HPP


#include <Dice/RDF/Triple.hpp>
#include <map>
#include <memory>
#include <optional>
#include <string>

#include "Dice/RDF/Term.hpp"
#include "Dice/RDF/Triple.hpp"
#include "Dice/SPARQL/TriplePattern.hpp"


/**
 * States store information needed during and after the parsing.
 * For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states
 */
namespace Dice::rdf_parser::Turtle::States {

    /*
     * BasicState defines the data structures related to rdf term
     */


    template<bool sparqlQuery = false>
    class BasicState {
    public:
        BasicState() {
            element_ = std::make_shared<Element_t>();
        }

        using Term = Dice::rdf::Term;
        using VarOrTerm = Dice::sparql::VarOrTerm;
        using Triple = Dice::rdf::Triple;
        using Element_t = std::conditional_t<sparqlQuery, VarOrTerm, Term>;

    protected:
        std::shared_ptr<Element_t> element_;

        //variables to deal with type and lan tags in literals
        bool type_tag_found = false;
        bool lang_tag_found = false;
        bool iri_is_IRIREF;
        std::string lang_tag_;
        std::string type_tag_;
        std::string literal_string_;
        std::string blank_node_string_;

        //dealing with base directives
        std::string base_;

        int latest_BN_label = 1;

        // todo: use something optimized
        std::map<std::string, std::string> prefix_map;


    public:
        inline Element_t &getElement() { return *element_; }

        inline void setElement(Element_t element) { *(this->element_) = std::move(element); }


        inline void addPrefix(std::string prefix, std::string value) {
            prefix_map.insert(std::pair<std::string, std::string>(std::move(prefix), std::move(value)));
        }

        inline void setLan_tag(std::string lan_tag) { this->lang_tag_ = std::move(lan_tag); }

        inline void setType_tag(std::string type_tag) { this->type_tag_ = std::move(type_tag); }


        [[nodiscard]] bool isTypeTagFound() const {
            return type_tag_found;
        }

        inline void setType_tag_found(bool found) {
            this->type_tag_found = found;
        }


        [[nodiscard]] bool isLangTagFound() const {
            return lang_tag_found;
        }

        inline void setLang_tag_found(bool found) {
            this->lang_tag_found = found;
        }

        inline void setIri_is_IRIREF(bool found) {
            this->iri_is_IRIREF = found;
        }

        const std::string &getType_tag() {
            return type_tag_;
        }

        const std::string &getLang_tag() {
            return lang_tag_;
        }

        bool iriIsIRIREF() {
            return iri_is_IRIREF;
        }

        const std::string &getBlank_node_string() {
            return blank_node_string_;
        }

        const std::string &getLiteral_string() {
            return literal_string_;
        }

        inline void setLiteral_string(std::string literal_string) { this->literal_string_ = std::move(literal_string); }

        inline void setBlank_node_string(std::string blank_node_string) {
            this->blank_node_string_ = std::move(blank_node_string);
        }

        inline void setBase(std::string base) { this->base_ = std::move(base); }

        const std::string &getBase() { return base_; }

        // create a unique label for a BlankNode
        std::string createBlankNodeLabel() {
            return fmt::format("b{}", latest_BN_label++);
        }

        [[nodiscard]] inline std::optional<std::reference_wrapper<const std::string>>
        getPrefixValue(const std::string &prefix) const {
            if (auto prefix_iter = prefix_map.find(prefix);
                    prefix_iter != prefix_map.end()) {
                const auto &mappedPrefix = prefix_iter->second;
                return std::optional<std::reference_wrapper<const std::string>>{mappedPrefix};
            } else {
                return std::nullopt;
            }
        }
    };
}// namespace Dice::rdf_parser::Turtle::States


#endif//RDF_PARSER_BASICSTATE_HPP
