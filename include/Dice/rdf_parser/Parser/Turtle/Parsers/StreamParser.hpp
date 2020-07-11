
#ifndef RDF_PARSER_TURTLEPEGTLSTREAMPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLSTREAMPARSER_HPP


/**
 * StreamParser is responsible for parsing triples from stream sources.
 * It parse a file as a stream and put the parsed triples increasingly in a std::queue
 */

#include "TriplesParser.hpp"

#include "Dice/rdf_parser/Parser/Turtle/Actions/Actions.hpp"

namespace {
    using namespace tao::pegtl;
}


namespace rdf_parser::Turtle {


    class StreamParser : public TriplesParser {

    private:
        /**
        * a queue for storing parsed triples .
        */
        std::shared_ptr<std::queue<Triple>> parsedTerms;

        /**
         * defines the size of the stream buffer
         */
        const std::size_t defaultBufferSize = 10000000;

        std::ifstream stream;

    public:

        /**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param filename the filename of the file we want to parse
         */
        StreamParser(std::string filename) : stream{filename} {
            try {
                read_input file(filename);
                parsedTerms = std::make_shared<std::queue<Triple>>();
                States::State<> state(parsedTerms);
                parse<Grammer::grammer<>, Actions::action>(istream_input(stream, defaultBufferSize, filename), state);

            }
            catch (std::exception &e) {
                throw e;
            }

        }

        ~StreamParser() override {
            stream.close();
        }

        StreamParser(std::string filename, std::size_t bufferSize) {
            try {
                std::ifstream stream(filename);
                read_input file(filename);
                parsedTerms = std::make_shared<std::queue<Triple>>();
                States::State<> state(parsedTerms);
                parse<Grammer::grammer<>, Actions::action>(istream_input(stream, bufferSize, filename), state);

            }
            catch (std::exception &e) {
                throw e;
            }
        }


        void nextTriple() override {
            current_triple = parsedTerms->front();
            parsedTerms->pop();

        }


        bool hasNextTriple() const override {
            return not parsedTerms->empty();
        }

    };
}


#endif //RDF_PARSER_TURTLEPEGTLSTREAMPARSER_HPP
