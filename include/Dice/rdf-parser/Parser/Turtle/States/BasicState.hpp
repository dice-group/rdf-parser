
#ifndef RDF_PARSER_BASICSTATE_HPP
#define RDF_PARSER_BASICSTATE_HPP





#include <map>
#include <memory>
#include <optional>
#include <string>

#include "Dice/rdf-parser/RDF/Term.hpp"
#include "Dice/rdf-parser/Sparql/TriplePatternElement.hpp"


/**
 * States store information needed during and after the parsing.
 * For more information about states please check https://github.com/taocpp/PEGTL/blob/master/doc/Actions-and-States.md#states
 */
namespace rdf_parser::Turtle::States {

		/*
         * BasicState defines the data structures related to rdf term
         */
		template<bool sparqlQuery = false>
		class BasicState {
			using Term = rdf_parser::store::rdf::Term;
			using Literal = rdf_parser::store::rdf::Literal;
			using Element_t = std::conditional_t<sparqlQuery, SparqlQuery::VarOrTerm, Term>;
		public:
			BasicState() {
				element_ = std::make_shared<Element_t>();
			}

		protected:
			std::shared_ptr<Element_t> element_;

			//variables to deal with type and lan tags in literals
			bool type_tag_found = false;
			bool lang_tag_found = false;
			bool iri_is_IRIREF;
			std::string lan_tag_;
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

			inline void setLan_tag(std::string lan_tag) { this->lan_tag_ = std::move(lan_tag); }

			inline void setType_tag(std::string type_tag) { this->type_tag_ = std::move(type_tag); }


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
				if (type_tag_found) {
					std::string tag;
					//set it again to false
					type_tag_found = false;
					//check if the type tag is iri or PREFIXED NAME and process it accordingly
					if (not iriIsIRIREF()) {
						size_t pos = type_tag_.find(':');
						std::string prefix = type_tag_.substr(0, pos);
						if (auto prefix_iter = prefix_map.find(prefix);
								prefix_iter != prefix_map.end()){
							const auto &mappedPrefix = prefix_iter->second;
							tag = mappedPrefix + type_tag_.substr(pos + 1, type_tag_.length());
						} else {
							tag = type_tag_;
						}
					} else {
						tag = type_tag_;
					}
					*element_ = (Literal(literal_string_, std::nullopt, tag));
				}
				//check if this RdfLiteral has langTag part
				else if (lang_tag_found) {
					//set it again to false
					lang_tag_found = false;
					*element_ = Literal(literal_string_, lan_tag_, std::nullopt);
				} else {
					*element_ = Literal(literal_string_, std::nullopt, std::nullopt);
				}
			}

			std::string getType_tag() {
				return type_tag_;
			}

			bool iriIsIRIREF() {
				return iri_is_IRIREF;
			}

			std::string getBlank_node_string() {
				return blank_node_string_;
			}

			inline void setLiteral_string(std::string literal_string) { this->literal_string_ = std::move(literal_string); }

			inline void setBlank_node_string(std::string blank_node_string) { this->blank_node_string_ = std::move(blank_node_string); }

			inline void setBase(std::string base) { this->base_ = std::move(base); }

			std::string getBase() { return base_; }

			// create a unique label for a BlankNode
			std::string createBlankNodeLabel() {
				return fmt::format("b{}", latest_BN_label++);
			}

			/**
			 * Checks if the prefix already exits
			 * @param prefix the prefix you are looking for
			 * @return if it exists or not
			 */
			inline bool hasPrefix(const std::string &prefix) {
				auto found = prefix_map.find(prefix);
				if (found != prefix_map.end())
					return true;
				return false;
			}

			inline std::string getPrefixValue(const std::string& prefix) {
				auto found = prefix_map.find(prefix);
				return found->second;
			}
		};
	}// namespace rdf_parser::Turtle


#endif//RDF_PARSER_BASICSTATE_HPP
