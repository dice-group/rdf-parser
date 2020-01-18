
#ifndef RDF_PARSER_TURTLEPEGTLSTRINGPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLSTRINGPARSER_HPP


/**
 * StringParser is responsible for parsing triples from string sources.
 * It parse the string one time and put the parsed triples in a std::queue
 */

#include <chrono>

#include "TriplesParser.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Actions/Actions.hpp"

namespace {
    using namespace tao::pegtl;
}


namespace rdf_parser::Turtle {


    class StringParser : public TriplesParser {


    private:
        /**
         * a queue for storing parsed triples .
         */
        std::shared_ptr<std::queue<Triple>> parsedTerms;

    public:

        /**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param text the string to parse
         */
        StringParser(std::string text) {
            try {
                string_input input(text, "the text");
                States::State<> state(parsedTerms);
                parse<Grammer::grammer, Actions::action>(input, state);

            }
            catch (std::exception &e) {
                throw e;
            }

            //get the first triple
            if (hasNextTriple())
                nextTriple();
            else
                std::runtime_error("there is no triple to parse");
        }

        bool hasNextTriple() const override {
            return not parsedTerms->empty();
        }

        ~StringParser() override {

        }

        void nextTriple() override {
            current_triple = parsedTerms->front();
            parsedTerms->pop();

        }

        /**
         * checks whether a string is valid rdf turtle file
         */
        static bool isParsable(const std::string &input) {
            try {
                string_input in(input, "the text");
                parse<Grammer::grammer>(in);
                return true;
            }
            catch (std::exception &e) {
                return false;
            }

        }

        /**
         * calculate the time for parsing a rdf turtle string.
         * Note that the calculated time is only for parsing without using processing the input(creating and storing the triples out of the string)
         */
        static long calculateParsingTime(const std::string &input) {
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            isParsable(input);
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            return duration;
        }
    };
}

#endif //RDF_PARSER_TURTLEPEGTLSTRINGPARSER_HPP
