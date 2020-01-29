# Tentris RDF Parser

This is the RDF parser used by [Tentris](https://github.com/dice-group/tentris). It uses [PEGTL](https://github.com/taocpp/PEGTL), Parsing Expression Grammar Library, to parse RDF files (currently supported: ntriple, turtle). 

It has buffered streaming support so that you can load files that are too big to fit in main memory. 

Currently it is not fully supporting comments.it fails to parse comments in some senarios .

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
**TODO: update this as soon as it is published**
```
conan remote add dice "https://api.bintray.com/conan/dice-group/tentris"

```

## Documentation

### Introduction

A header-only library designed to allow efficient and controlled parsing for RDF languages.
Currently it supports ntriples and turtle languages .
It uses tao's PEGTL library for parsing.

### Usage

The library is easy to use, for parsing turtle or ntriples include the header `<Dice/rdf_parser/TurtleParser.hpp>` and use the class `TurtleParser<>` (which is a wrapper to use any parser type) for parsing. 
`TurtleParser` accept one template parameter which determine the parser type (more information about that on the next section), and it's constructor accept one string parameter which is either the string which is the document to be parsed in case of `StringParser` or the filename of the file that contains the document to be parsed.

Example :
```c++
TurtleParser<FileParser> turtleParser("datasets/g.nt");
```
where `"datasets/g.nt"` is the file name of the file we want to parse.

Now an iterator can be created:
```c++
auto iterator=turtleParser.begin();
```

We can iterate over the triples and used the triples:

```c++
while(it)
{
 Triple triple= *it;
 it++;
}
```

### Parsers types
There are four types of parsers which can be used:
- `StringParser`: It is used for parsing Strings immediately. It accepts one parameter which is the string of the document to be parsed.
- `FileParser`: It is used for parsing a whole document file at a time. The parsed triples cannot be accessed before the parsing of the whole document is done. It is faster than the `StreamParser` (below) but require much more memory and thus may run out of memory for large inputs.
- `StreamParser`: It is used for parsing streams or large files. It can process very big files with low memory usage by parsing chunk by chunk. However, triples are not accessible until the parsing is done. 
- `ConcurrentStreamParser`: It can be used the same way as the `StreamParser` but uses a separated thread for parsing and uses Intel's TBB `concurrent_queue`
for storing the parsed triples. Therefore, the already parsed triples can be accessed during the parsing process. It is the default template parameter for `TurtleParser`.
And it is the recommended parser to use for large files or streams and for simultaneous parsing and accessing to the already parsed triples.

### Example
Here we create a full example for parsing a turtle file. It is by default using the `ConcurrentStreamParser`. We assuming there is an turtle file at `datasets/dataset1.ttl`. The file is parsed and the triples are printed to `std::out`.

```c++
#include <Dice/rdf_parser/TurtleParser.hpp>

namespace {
    using namespace rdf_parser::Turtle;
    using namespace rdf_parser::store::rdf;
}

int main()
{
 TurtleParser<> Parser("datasets/dataset1.ttl");
 auto it=Parser.begin();
 //or we can use: TurtleParser<>::Iterator it=Parser.begin();
 while (it){
         Triple triple= *it;
         std::cout<<"subject :"<<triple.subject().getIdentifier()<<",predicit :"<<triple.predicate().getIdentifier()
         <<",object :"<<triple.object().getIdentifier()<<std::endl;
         it++;
     }
}
```
