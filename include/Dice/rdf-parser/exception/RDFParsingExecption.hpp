#ifndef RDF_PARSER_RDFPARSINGEXECPTION_HPP
#define RDF_PARSER_RDFPARSINGEXECPTION_HPP

namespace Dice::rdf_parser::exception
{
    class RDFParsingException : public std::exception {
    public:
        [[nodiscard]] const char *what() const noexcept override {
            return "The rdf document can't be parsed";
        }
    };
}

#endif//RDF_PARSER_RDFPARSINGEXECPTION_HPP
