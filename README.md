# Tentris RDF Parser

This is the RDF parser used by [Tentris](https://github.com/dice-group/tentris). It uses [PEGTL](https://github.com/taocpp/PEGTL), Parsing Expression Grammar Library, to parse RDF files (currently supported: ntriple, turtle).
 It also supports parsing the triplesBlock part of Sparql queries.

It has buffered streaming support so that you can load files that are too big to fit in main memory. 

Currently it is not fully supporting comments. It fails to parse comments in some scenarios.

## how to build
### prerequisites

install conan, cmake and a C++17 compiler

add conan remotes
```
conan remote add conan "https://api.bintray.com/conan/conan/public-conan" ; conan remote add taocpp https://api.bintray.com/conan/taocpp/public-conan ; conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
 
```

### build
```
mkdir build
cd build
conan install .. --build=missing --settings compiler.libcxx="libstdc++11"
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make -j
```


### conan 

recipe : rdf-parser/0.13.0@dice-group/stable
```
conan remote add dice "https://api.bintray.com/conan/dice-group/tentris"

```

## Documentation

### Introduction

A header-only library designed to allow efficient and controlled parsing for RDF languages.
Currently it supports ntriples and turtle languages, as well as triplesBlock part of sparql queries.
It uses tao's PEGTL library for parsing.

###  Usage

The library is easy to use, for parsing turtle or ntriples include the header for the required parser.
for example, to use the File parser, include `<Dice/rdf-parser/TurtleFileParser.hpp>` 

Rdf parsers' constructor accept one string parameter which is either the string which is the document to be parsed in case of `TurtleStringParser` or the filename of the file that contains the document to be parsed oin case of `TurtleFileParser` .

Example :
```c++
 TurtleFileParser parser("datasets/g.nt");
```
where `"datasets/g.nt"` is the file name of the file we want to parse.

Now an iterator can be created:
```c++
auto iterator=parser.begin();
```

We can iterate over the triples and used the triples:

```c++
for(const Triple &triple : parser) {
    // do something with triple
    std::cout << triple.subject().getIdentifier() << " " << triple.predicate().getIdentifier() << " " << triple.object().getIdentifier() << std::endl;
}
```

### Parsers types
There are four types of parsers which can be used:
- `TurtleStringParser`: It can be used to parse Rdf Strings immediately. It accepts one parameter which is the string of the document to be parsed.
- `TurtleFileParser`: It can be used to parse a whole document file that contains a Rdf. It can process very big files with low memory usage by parsing chunk by chunk. It also uses a separated thread for parsing and writes the results in a concurrent queue.
Therefore, the already parsed triples can be accessed during the parsing process. It accepts one parameter which is the name of the file.

- `TriplesBlockStringParser`: It is used for parsing Sparql's TripleBlocks Strings immediately. It accepts one parameter which is the string of the document to be parsed. And another
optional parameter which is either a std::unordered_map (or robin_hood::unordered_map which is more opimized) contains the prefixes.
  
### Examples

1-Here we create a full example for parsing a turtle file. we use here the `TurtleFileParser`. We are assuming there is an turtle file at `datasets/dataset1.ttl`. The file is parsed and the triples are printed to `std::out`.
Dice::rdf_parser::Turtle::parsers
 ```c++

#include <Dice/rdf-parser/TurtleFileParser.hpp>

int main()
{
Dice::rdf_parser::Turtle::parsers::TurtleFileParser parser("datasets/dataset1.ttl");
 auto it=Parser.begin();
 while (it){
         Dice::rdf::Triple triple= *it;
         std::cout << triple.subject().getIdentifier() << " "
                   << triple.predicate().getIdentifier() << " "
                   << triple.object().getIdentifier()
                   << std::endl;
         it++;
     }
}
```

2-Here we create a full example for parsing The tripleBlock part of SparqlQuery Using the TriplesBlockStringParser.

```c++
#include <Dice/sparql-parser/internal/TriplesBlockStringParser.hpp>
#include<unordered_map>

int main()
{
//create a map of prefixes
robin_hood::unordered_map<std::string,std::string> prefixes;
prefixes.emplace("wde","http://www.wikidata.org/entity/");
prefixes.emplace("wdt","http://www.wikidata.org/prop/direct/");

// create the parser with 2 parameters: the query and the prefixes map
Dice::sparql_parser::internal::TriplesBlockStringParser parser("?var1 <http://www.wikidata.org/prop/P463> _:b0 . _:b0 <http://www.wikidata.org/prop/statement/P463> wde:Q202479 ; <http://www.wikidata.org/prop/qualifier/P580> ?var2 .", prefixes) ;

//get an iterator 
auto it= parser.begin();

while (it)
{
    TriplePatternElement triplePatternElement=*it;
    Dice::sparql::VarOrTerm subject=TriplePatternElement.subject();
    Dice::sparql::VarOrTerm subject=TriplePatternElement.predicate();
    Dice::sparql::VarOrTerm subject=TriplePatternElement.object();
    it++;
}
}
```
