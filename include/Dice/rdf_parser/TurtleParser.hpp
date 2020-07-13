

#ifndef RDF_PARSER_TURTLEPARSER_HPP
#define RDF_PARSER_TURTLEPARSER_HPP

/**
 * TurtleParser is a wrapper to use the other parsers
 */

#include <string>
#include <utility>

#include "Dice/rdf_parser/Parser/Turtle/Parsers/ConcurrentStreamParser.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Parsers/FileParser.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Parsers/StringParser.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Parsers/StreamParser.hpp"

namespace rdf_parser::Turtle {
    template<class ParserType=CuncurrentStreamParser<false>>
    class TurtleParser {


    private:
        /**
         * content could be the filename of the file to parse or the string which we ant to parse.
         * Depending on the type of the parser we are using.
         */
        std::string content;

    public:
        class Iterator {

        private:
            ParserType turtle_parser_;
            bool done_;
            bool parser_done_;

        public:
            explicit Iterator(std::string content) :
                    turtle_parser_{std::move(content)},
                    done_{false}, parser_done_{false} {
                //check if there is at least one parsed triple
                if (turtle_parser_.hasNextTriple())
                    this->operator++();
                else
                    parser_done_ = true;
            };

            void operator++() {
                if (parser_done_) {
                    done_ = true;
                } else {
                    turtle_parser_.nextTriple();
                    if (not turtle_parser_.hasNextTriple())
                        parser_done_ = true;
                }
            }

            void operator++(int) { operator++(); }

            operator bool() { return not done_; }

            const Triple &operator*() { return turtle_parser_.getCurrentTriple(); }
        };


    public:
        explicit TurtleParser(std::string content) :
                content{std::move(content)} {}

        Iterator begin() { return Iterator(content); }

        bool end() { return false; }

        bool isContentParsable() {
            if constexpr(std::is_same_v<ParserType, StringParser>)
                return StringParser<>::isParsable(this->content);
            else
                return FileParser<>::isParsable(this->content);

        }
    };

}
#endif //RDF_PARSER_TURTLEPARSER_HPP