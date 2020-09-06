#ifndef RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP
#define RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP


/**
 * FileParser is responsible for parsing triples from file sources.
 * It parse the file one time and put the parsed triples in a std::queue
 */


#include <fstream>
#include <chrono>

#include "TriplesParser.hpp"
#include "Dice/rdf_parser/Parser/Turtle/Actions/Actions.hpp"

namespace {
    using namespace tao::pegtl;
}

namespace rdf_parser::Turtle {

    template<bool sparqlQuery=false>
    class FileParser : public TriplesParser<sparqlQuery> {

    private:
        /**
         * a queue for storing parsed triples .
         */
        std::shared_ptr<std::queue<std::conditional_t<sparqlQuery,SparqlQuery::TriplePatternElement ,Triple>>> parsedTerms;

    public:


        /**
         * The constructor start the parsing.if the input is not valid it will throws and exception.
         * it also invoke nextTriple to have the first triple ready for using .
         * @param filename the filename of the file we want to parse
         */
        FileParser(std::string filename) {
            try {
                std::ifstream infile(filename);
                read_input file(filename);
                States::State<> state(parsedTerms);
                parse<Grammer::grammer<sparqlQuery>, Actions::action>(file, state);

            }
            catch (std::exception &e) {
                throw e;
            }

        }

        ~FileParser() override {
//           The constructors that take a FILE* argument take ownership of the file pointer, i.e. they fclose() it in the destructor.Therfore, no need to close the file in this destructor
//           see https://github.com/taocpp/PEGTL/blob/master/doc/Inputs-and-Parsing.md#file-input
        }

        bool hasNextTriple() const override {
            return not parsedTerms->empty();
        }

        void nextTriple() override {
            this->current_triple = parsedTerms->front();
            parsedTerms->pop();

        }


        /**
         * checks whether a file is valid rdf turtle file
         */
        static bool isParsable(std::string filename) {
            try {
                std::ifstream infile(filename);
                read_input file(filename);
                parse<Grammer::grammer<sparqlQuery>>(file);
                return true;
            }
            catch (std::exception &e) {
                return false;
            }
        }


        /**
         * calculate the time for parsing a rdf turtle file.
         * Note that the calculated time is only for parsing without using processing the input(creating and storing the triples out of the string)
         */
        static long calculateParsingTime(const std::string filename) {
            std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
            isParsable(filename);
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
            return duration;
        }

    };
}


#endif //RDF_PARSER_TURTLEPEGTLFILEPARSER_HPP
