#ifndef RDF_PARSER_MAKE_TERM_HPP
#define RDF_PARSER_MAKE_TERM_HPP

#include "Dice/RDF/Term.hpp"
#include "Dice/rdf-parser/internal/Turtle/Actions/BasicActions.hpp"
#include "Dice/rdf-parser/internal/Turtle/Grammar.hpp"
#include "Dice/rdf-parser/internal/Turtle/States/BasicState.hpp"

namespace Dice::rdf {
	/**
	 * Parses a RDF Term string.
	 * @param identifier rdf term string
	 * @throws std::logic_error is thrown if identifier is not parsable
	 * @return RDF Term
	 */
	inline Term parse_term(const std::string &identifier) {
		try {
			using namespace tao::pegtl;
			string_input input(identifier, "the text");
			Dice::rdf_parser::internal::Turtle::States::BasicState state;
			parse<Dice::rdf_parser::internal::Turtle::Grammar::term, Dice::rdf_parser::internal::Turtle::Actions::action>(input, state);
			return std::move(state.getElement());
		} catch (const std::exception &e) {
			throw std::logic_error{fmt::format("{} is not a valid term.", identifier)};
		}
	}

	/**
	 * Checks whether a Term string is parsable.
	 * @param identifier identifier rdf term string
	 * @return if identifier is parsable.
	 */
	inline bool term_parsable(const std::string &identifier) {
		try {
			parse_term(identifier);
			return true;
		} catch (const std::logic_error &e) {
			return false;
		}
	}

};    // namespace Dice::rdf
#endif//RDF_PARSER_MAKE_TERM_HPP
