#ifndef RDF_PARSER_TURTLEPEGTLGRAMMER_HPP
#define RDF_PARSER_TURTLEPEGTLGRAMMER_HPP

/**
All grammers for turtle are defined here.PEGTL is used for parsing.
For more information about how to define grammers and rules using PEGTl please check "https://github.com/taocpp/PEGTL/blob/master/doc/Rules-and-Grammars.md"
*/


#include <tao/pegtl.hpp>

namespace {
    using namespace tao::pegtl;
}


namespace rdf_parser::Turtle::Grammer {

//      Terminals

    struct PN_LOCAL_ESC
            : seq<one<'\\'>,
                    sor<one<'_'>,
                            one<'~'>,
                            one<'.'>,
                            one<'-'>,
                            one<'!'>,
                            one<'$'>,
                            one<'&'>,
                            one<'\''>,
                            one<'('>,
                            one<')'>,
                            one<'*'>,
                            one<'+'>,
                            one<','>,
                            one<';'>,
                            one<'='>,
                            one<'/'>,
                            one<'?'>,
                            one<'#'>,
                            one<'@'>,
                            one<'%'>>> {
    };

    struct HEX :
            ranges<'a', 'z', 'A', 'Z', '0', '9'> {
    };

    struct PERCENT :
            seq<one<'%'>, HEX, HEX> {
    };

    struct PLX :
            sor<PERCENT, PN_LOCAL_ESC> {
    };

    struct PN_CHARS_BASE
            : sor<lower, upper, utf8::ranges<
                    0x00C0, 0x00D6, 0x00D8, 0x00F6, 0x00F8, 0x02FF, 0x0370, 0x037D, 0x037F, 0x1FFF, 0x200C, 0x200D, 0x2070, 0x218F, 0x2C00, 0x2FEF, 0x3001, 0xD7FF, 0xF900, 0xFDCF, 0xFDF0, 0xFFFD, 0x10000, 0xEFFFF>> {
    };

    struct PN_CHARS_U :
            sor<PN_CHARS_BASE, one<'_'>> {
    };

    struct PN_CHARS
            : sor<PN_CHARS_U, one<'-'>,
                    digit,
                    utf8::one<0x00B7>,
                    utf8::range<0x0300, 0x036F>,
                    utf8::range<0x203F, 0x2040>> {
    };

    struct PN_LOCAL
            : seq<
                    sor<
                            PN_CHARS_U,
                            one<':'>,
                            digit,
                            PLX
                    >,
                    star<
                            star<
                                    one<'.'>
                            >,
                            plus<
                                    sor<
                                            PN_CHARS,
                                            one<':'>,
                                            PLX
                                    >
                            >
                    >
            > {
    };

    struct PN_PREFIX :
            seq<
                    PN_CHARS_BASE,
                    star<
                            star<one<'.'>>,
                            PN_CHARS
                    >
            > {
    };

    struct ANON_WS :
            one<' ', '\t', '\r', '\n'> {
    };

    struct ANON :
            seq<one<'['>, star<ANON_WS>, one<']'>> {
    };

    struct UCHAR
            : sor<
                    seq<one<'\\'>, one<'u'>, HEX, HEX, HEX, HEX>,
                    seq<one<'\\'>, one<'U'>, HEX, HEX, HEX, HEX, HEX, HEX, HEX, HEX>
            > {
    };

    struct ECHAR
            : seq<one<'\\'>, sor<one<'t'>, one<'b'>, one<'n'>, one<'r'>, one<'f'>, one<'"'>, one<'\''>, one<'\\'>>> {
    };

    struct STRING_LITERAL_LONG_QUOTE :
            seq<
                    one<'\"'>, one<'\"'>, one<'\"'>,
                    star<
                            opt<
                                    sor<
                                            seq<one<'\"'>, one<'\"'>>,
                                            one<'\"'>
                                    >
                            >,
                            sor<not_one<'\"', '\\'>, ECHAR, UCHAR>
                    >,
                    one<'\"'>, one<'\"'>, one<'\"'>
            > {
    };

    struct STRING_LITERAL_QUOTE
            : seq<
                    one<'\"'>,
                    star<
                            sor<
                                    not_one<'\"', '\\', '\r', '\n'>,
                                    ECHAR,
                                    UCHAR
                            >

                    >,
                    one<'\"'>
            > {
    };

    struct STRING_LITERAL_SINGLE_QUOTE
            : seq<
                    one<'\''>,
                    star<
                            sor<
                                    not_one<'\'', '\\', '\r', '\n'>,
                                    ECHAR,
                                    UCHAR
                            >

                    >,
                    one<'\''>
            > {
    };

    struct STRING_LITERAL_LONG_SINGLE_QUOTE
            : seq<
                    one<'\''>, one<'\''>, one<'\''>,
                    star<
                            opt<
                                    sor<
                                            seq<one<'\''>, one<'\''>>,
                                            one<'\''>
                                    >
                            >,
                            sor<not_one<'\'', '\\'>, ECHAR, UCHAR>
                    >,
                    one<'\''>, one<'\''>, one<'\''>
            > {
    };

    struct INTEGER :
            seq<opt<sor<one<'+'>, one<'-'>>>, plus<digit>> {
    };

    struct DECIMAL :
            seq<opt<sor<one<'+'>, one<'-'>>>, star<digit>, one<'.'>, plus<digit>> {
    };

    struct EXPONENT
            : seq<sor<one<'e'>, one<'E'>>, opt<sor<one<'+'>, one<'-'>>>, plus<digit>> {
    };

    struct DOUBLE
            : seq<opt<sor<one<'+'>, one<'-'>>>, sor<
                    seq<plus<digit>, one<'.'>, star<digit>, EXPONENT>,
                    seq<one<'.'>, plus<digit>, EXPONENT>,
                    seq<plus<digit>, EXPONENT>
            > > {
    };

    struct LANGTAG :
            seq<one<'@'>, plus<alpha>, star<seq<one<'-'>, plus<alnum>>>> {
    };

    struct BLANK_NODE_LABEL :
            seq<
                    one<'_'>,
                    one<':'>,
                    sor<
                            PN_CHARS_U,
                            digit
                    >,
                    star<
                            star<one<'.'>>,
                            PN_CHARS
                    >
            > {
    };

    struct PNAME_NS :
            seq<opt<PN_PREFIX>, one<':'>> {
    };

    struct PNAME_LN :
            seq<PNAME_NS, PN_LOCAL> {
    };

    struct IRIREF :
            seq<
                    one<'<'>,
                    star<sor<
                            minus<minus<any, one<'<', '>', '"', '{', '}', '|', '^', '`', '\\'>>, tao::pegtl::range<0x00, 0x20>>,
                            UCHAR
                    >>,
                    one<'>'>
            > {
    };

    struct comment :
            seq<
                    one<'#'>,
                    star<not_one<'\n', '\r', '\f'>>,
                    one<'\n', '\r'>> {
    };



//       Grammar rules



    struct ignored :
            star<sor<space, comment>> {
    };

    struct NumericLiteral :
            sor<DOUBLE, DECIMAL, INTEGER> {
    };

    struct turtleString
            : sor<STRING_LITERAL_LONG_QUOTE, STRING_LITERAL_LONG_SINGLE_QUOTE, STRING_LITERAL_SINGLE_QUOTE, STRING_LITERAL_QUOTE> {
    };

    struct BlankNode :
            sor<BLANK_NODE_LABEL, ANON> {
    };

    struct PrefixedName :
            sor<PNAME_LN, PNAME_NS> {
    };

    struct iri :
            sor<IRIREF, PrefixedName> {
    };

    struct prefixID :
            seq<string<'@', 'p', 'r', 'e', 'f', 'i', 'x'>, ignored, PNAME_NS, ignored, IRIREF, ignored, one<'.'>> {
    };

    struct sparqlPrefix :
            seq<one<'P', 'p'>,
                    one<'R', 'r'>,
                    one<'E', 'e'>,
                    one<'F', 'f'>,
                    one<'I', 'i'>,
                    one<'X', 'x'>,
                    ignored,
                    PNAME_NS,
                    ignored,
                    IRIREF> {
    };

    struct base :
            seq<string<'@', 'b', 'a', 's', 'e'>, ignored, IRIREF, ignored, one<'.'>> {
    };

    struct sparqlBase :
            seq<one<'B', 'b'>, one<'A', 'a'>, one<'S', 's'>, one<'E', 'e'>, ignored, IRIREF> {
    };

    struct directive :
            sor<prefixID, base, sparqlBase, sparqlPrefix> {
    };

    struct RdfLiteralTypeTag :
            seq<string<'^', '^'>, iri> {
    };

    struct RdfLiteral :
            seq<turtleString, opt<sor<LANGTAG, RdfLiteralTypeTag>>> {
    };

    struct BooleanLiteral :
            sor<string<'t', 'r', 'u', 'e'>, string<'f', 'a', 'l', 's', 'e'>> {
    };

    struct literal :
            sor<RdfLiteral, NumericLiteral, BooleanLiteral> {
    };


    struct term :
            must<sor<RdfLiteral, BlankNode, iri>> {
    };

    //The following grammers are not part of turtle.they are part of sparql language.but used here to make it
    //possible to parse some sparql grammer which has very similar context to turtle.

    struct varname :
            seq<
                    sor<PN_CHARS_U,digit>,
                    star<sor<PN_CHARS_U,digit,utf8::one<0x00B7>,utf8::range<0x0300, 0x036F>,utf8::range<0x203F, 0x2040>>>
            >{
    };

    struct var1 :
            seq<one<'?'>,varname> {
    };

    struct var2 :
            seq<one<'$'>,varname> {
    };

    struct var :
            sor<var1,var2> {
    };

    struct varOrTerm:
            sor<var,term>{};

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<bool sparqlQuery=false>
    struct collection;
    template<bool sparqlQuery=false>
    struct blankNodePropertyList;
    template<bool sparqlQuery=false>
    struct object :
            std::conditional_t<sparqlQuery,
            sor<varOrTerm, collection<sparqlQuery>, blankNodePropertyList<sparqlQuery>>,
            sor<term, collection<sparqlQuery>, blankNodePropertyList<sparqlQuery>>
            >{};

    template<bool sparqlQuery=false>
    struct objectList :
            seq<object<sparqlQuery>, star<seq<ignored, one<','>, ignored, object<sparqlQuery>>>> {
    };

    struct predicate :
            iri {
    };

    struct collectionBegin :
            one<'('> {
    };

    template<bool sparqlQuery>
    struct collection :
                    seq<collectionBegin,
                            star<seq<ignored, object<sparqlQuery>>>,
                            ignored,
                            one<')'>
                    >{};

    struct verb_a :
            one<'a'> {
    };

    template<bool sparqlQuery=false>
    struct verb :
            sor<std::conditional_t<sparqlQuery,sor<var,predicate>,predicate>, verb_a> {
    };

    template<bool sparqlQuery=false>
    struct predicateObjectListInner :
            seq<verb<sparqlQuery>, ignored, objectList<sparqlQuery>> {
    };

    template<bool sparqlQuery= false>
    struct predicateObjectList :
            seq<
                    predicateObjectListInner<sparqlQuery>,
                    star<
                            seq<
                                    ignored,
                                    one<';'>,
                                    opt<
                                            seq<
                                                    ignored,
                                                    predicateObjectListInner<sparqlQuery>
                                            >
                                    >
                            >
                    >
            > {
    };

    struct blankNodePropertyListBegin :
            one<'['> {
    };

    template<bool sparqlQuery>
    struct blankNodePropertyList
            : seq<blankNodePropertyListBegin, ignored, predicateObjectList<sparqlQuery>, ignored, one<']'>> {
    };

    template<bool sparqlQuery=false>
    struct subject :
            std::conditional_t<sparqlQuery,
                               varOrTerm,
                               sor<iri, BlankNode, collection<false>>
                               >{};

    template<bool sparqlQuery=false>
    struct tripleSeq1 :
            seq<
                    subject<sparqlQuery>,
                    ignored,
                    predicateObjectList<sparqlQuery>
            > {
    };

    template<bool sparqlQuery=false>
    struct tripleSeq2 :
            seq<
                    blankNodePropertyList<sparqlQuery>,
                    ignored,
                    opt<predicateObjectList<sparqlQuery>>
            > {
    };

    template<bool sparqlQuery=false>
    struct triple :
            sor<
                    tripleSeq1<sparqlQuery>, tripleSeq2<sparqlQuery>> {
    };


    struct tripleExtended :
            seq<
                    triple<false>, ignored, one<'.'>
            > {
    };

    struct statement :
            sor<
                    tripleExtended,
                    directive
            > {
    };


    struct statementsCollection :
            sor<rep<10, seq<ignored, statement>>, seq<ignored, statement>> {
    };


    struct turtleDoc :
            seq<
                    plus<
                            seq<ignored, statement>
                    >, ignored
            > {
    };


    struct triplesBlock :
            seq<
                    triple<true>, ignored
//                    ,opt<
//                                             sor<
//                                               seq<triplesBlock,ignored,one<'.'>>,
//                                               one<'.'>
//                                                >
//                                             >
            >
            {
    };


    template<bool sparqlQuery=false>
    struct grammer :
            std::conditional_t<sparqlQuery,
                                must<triplesBlock, eof>,
                                sor<
                                        must<turtleDoc, eof>,
                                        seq<ignored, eof>
                                >
                              >
                              {};


}

#endif //RDF_PARSER_TURTLEPEGTLGRAMMER_HPP
