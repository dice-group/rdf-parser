
#ifndef SPARQL_QUERY_TRIPLEVARIABLE_HPP
#define SPARQL_QUERY_TRIPLEVARIABLE_HPP

namespace rdf_parser::SparqlQuery {
    class TripleVariable {
    private:
        std::string name;
        bool is_anonym;

    public:

        TripleVariable(){};
        explicit TripleVariable(std::string var_name, bool anonym = false) : name{std::move(var_name)},
                                                                             is_anonym{anonym} {}

        inline bool operator==(const TripleVariable &rhs) const {
            return name == rhs.name;
        }

        inline bool operator!=(const TripleVariable &rhs) const {
            return name != rhs.name;
        }

        inline bool operator<(const TripleVariable &rhs) const {
            return name < rhs.name;
        }

        inline bool operator>(const TripleVariable &rhs) const {
            return name > rhs.name;
        }

        inline void setName(std::string name){
            this->name=name;
        }

        inline void setIs_anonym(bool is_anonym){
            this->is_anonym=is_anonym;
        }

    };
}
#endif //SPARQL_QUERY_TRIPLEVARIABLE_HPP
