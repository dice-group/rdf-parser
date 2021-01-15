//
// Created by fakhr on 15.01.21.
//

#ifndef RDF_PARSER_INTERNALERROR_HPP
#define RDF_PARSER_INTERNALERROR_HPP

namespace Dice::rdf_parser::internal::Exceptions
{
    class InternalError : public std::exception {
    public:
        [[nodiscard]] const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
            return "Internal error. This should not happen. Contact the maintainer";
        }
    };
}


#endif//RDF_PARSER_INTERNALERROR_HPP
