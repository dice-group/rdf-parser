

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

//ToDo This class is now looks not nessecery,try to integrate it in the lower level.
namespace rdf_parser::Turtle {
    template<bool sparqlQuery = false, class ParserType=CuncurrentStreamParser<sparqlQuery>>
    class TurtleParser {


    private:
        /**
         * content could be the filename of the file to parse or the string which we want to parse.
         * Depending on the type of the parser we are using.
         */
        std::string content;
        std::map<std::string, std::string> prefix_map;

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

            explicit Iterator(std::string content,std::map<std::string, std::string> prefix_map) :
                    turtle_parser_{std::move(content),std::move(prefix_map)},
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

            const std::conditional_t<sparqlQuery, SparqlQuery::TriplePatternElement, Triple> &
            operator*() { return turtle_parser_.getCurrentTriple(); }
        };


    public:
        explicit TurtleParser(std::string content) :
                content{std::move(content)} {}

        explicit TurtleParser(std::string content,std::map<std::string, std::string> prefix_map) :
                content{std::move(content)},prefix_map{std::move(prefix_map)} {}

        Iterator begin() {
            if constexpr(std::is_same_v<ParserType, StringParser<sparqlQuery>>) {
                if(prefix_map.empty())
                   return Iterator(content);
                else
                  return Iterator(content, prefix_map);
            } else
                return Iterator(content);
        }

        bool end() { return false; }


        bool isContentParsable() {
            if constexpr(std::is_same_v<ParserType, StringParser<sparqlQuery>>)
                return StringParser<true>::isParsable(this->content);
            else
                return FileParser<false>::isParsable(this->content);

        }


    };
}
#endif //RDF_PARSER_TURTLEPARSER_HPP