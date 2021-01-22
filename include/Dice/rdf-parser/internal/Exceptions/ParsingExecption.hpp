#ifndef RDF_PARSER_PARSINGEXECPTION_HPP
#define RDF_PARSER_PARSINGEXECPTION_HPP

namespace Dice::rdf_parser::internal::Exceptions
{
    class ParsingException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "The rdf document can't be parsed";
        }
    };
}

#endif//RDF_PARSER_PARSINGEXECPTION_HPP
