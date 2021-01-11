
#ifndef RDF_PARSER_TURTLEPEGTLSTREAMPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLSTREAMPARSER_HPP


/**
 * StreamParser is responsible for parsing triples from stream sources.
 * It parse a file as a stream and put the parsed triples increasingly in a std::queue
 */
#include "AbstractParser.hpp"
#include "Dice/rdf-parser/Parser/Turtle/Actions/Actions.hpp"
#include "../Configurations.hpp"

namespace {
    using namespace tao::pegtl;
}


namespace rdf_parser::Turtle::parsers {


    class RdfStreamParser : public AbstractParser<RdfStreamParser, false> {

    private:
        /**
        * a queue for storing parsed triples .
        */
        std::shared_ptr<std::queue<Triple>> parsedTerms;
        std::ifstream stream;

    protected:


        /**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param filename the filename of the file we want to parse
         */
        RdfStreamParser(std::string filename) : stream{filename} {
            try {
                read_input file(filename);
                parsedTerms = std::make_shared<std::queue<Triple>>();
                States::State<> state(parsedTerms);
                parse<Grammer::grammer<>, Actions::action>(
                        istream_input(stream, Configurations::RdfStreamParser_BufferSize, filename), state);

            }
            catch (std::exception &e) {
                throw e;
            }

        }


    public:


        ~RdfStreamParser() override {
            stream.close();
        }


        void nextTriple() override {
            *(this->current_triple) = parsedTerms->front();
            parsedTerms->pop();

        }


        bool hasNextTriple() const override {
            return not parsedTerms->empty();
        }


        Iterator<RdfStreamParser, false> begin_implementation() {
            return Iterator<RdfStreamParser, false>(this);
        }

    };
}

#endif //RDF_PARSER_TURTLEPEGTLSTREAMPARSER_HPP
