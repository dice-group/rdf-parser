#include <gtest/gtest.h>

#include <Dice/rdf-parser/TurtleStringParser.hpp>


namespace Dice::tests::rdf_parser::turtle_official_examples_tests {

	using namespace Dice::rdf_parser;


	TEST(TurtleOfficalExamplesTests, EXAMPLE1) {
		TurtleStringParser parser(
				"@base <http://example.org/> .\n"
				"@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
				"@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n"
				"@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
				"@prefix rel: <http://www.perceive.net/schemas/relationship/> .\n"
				"\n"
				"<#green-goblin>\n"
				"    rel:enemyOf <#spiderman> ;\n"
				"    a foaf:Person ;  \n"
				"    foaf:name \"Green Goblin\" .\n"
				"\n"
				"<#spiderman>\n"
				"    rel:enemyOf <#green-goblin> ;\n"
				"    a foaf:Person ;\n"
				"    foaf:name \"Spiderman\", \"Человек-паук\"@ru .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE2) {

		TurtleStringParser parser(
				"<http://example.org/#spiderman> <http://www.perceive.net/schemas/relationship/enemyOf> <http://example.org/#green-goblin> .\n");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE3) {

		TurtleStringParser parser(
				"<http://example.org/#spiderman> <http://www.perceive.net/schemas/relationship/enemyOf> <http://example.org/#green-goblin> ;\n"
				"\t\t\t\t<http://xmlns.com/foaf/0.1/name> \"Spiderman\" .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE4) {

		TurtleStringParser parser(
				"<http://example.org/#spiderman> <http://www.perceive.net/schemas/relationship/enemyOf> <http://example.org/#green-goblin> .\n"
				"<http://example.org/#spiderman> <http://xmlns.com/foaf/0.1/name> \"Spiderman\" .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE5) {

		TurtleStringParser parser(
				"<http://example.org/#spiderman> <http://xmlns.com/foaf/0.1/name> \"Spiderman\", \"Человек-паук\"@ru .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE6) {

		TurtleStringParser parser(
				"<http://example.org/#spiderman> <http://xmlns.com/foaf/0.1/name> \"Spiderman\" .\n"
				"<http://example.org/#spiderman> <http://xmlns.com/foaf/0.1/name> \"Человек-паук\"@ru .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE7) {

		TurtleStringParser parser(
				"@prefix somePrefix: <http://www.perceive.net/schemas/relationship/> .\n"
				"\n"
				"<http://example.org/#green-goblin> somePrefix:enemyOf <http://example.org/#spiderman> .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE8) {

		TurtleStringParser parser(
				"PREFIX somePrefix: <http://www.perceive.net/schemas/relationship/>\n"
				"\n"
				"<http://example.org/#green-goblin> somePrefix:enemyOf <http://example.org/#spiderman> .\n"
				"\t\t\t\t  ");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE9) {

		TurtleStringParser parser(
				"<http://one.example/subject1> <http://one.example/predicate1> <http://one.example/object1> .\n"
				"@base <http://one.example/> .\n"
				"<subject2> <predicate2> <object2> .     \n"
				"BASE <http://one.example/>\n"
				"<subject2> <predicate2> <object2> .     \n"
				"@prefix p: <http://two.example/> .\n"
				"p:subject3 p:predicate3 p:object3 .     \n"
				"PREFIX p: <http://two.example/>\n"
				"p:subject3 p:predicate3 p:object3 .     \n"
				"@prefix p: <path/> .                    \n"
				"p:subject4 p:predicate4 p:object4 .    \n"
				"@prefix : <http://another.example/> .    \n"
				":subject5 :predicate5 :object5 .       \n"
				":subject6 a :subject7 .                \n"
				"<http://伝言.example/?user=أكرم&amp;channel=R%26D> a :subject8 .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE10) {

		TurtleStringParser parser(
				"@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
				"\n"
				"<http://example.org/#green-goblin> foaf:name \"Green Goblin\" .\n"
				"\n"
				"<http://example.org/#spiderman> foaf:name \"Spiderman\" .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE11) {

		TurtleStringParser parser(
				"@prefix show: <http://example.org/vocab/show/> .\n"
				"show:218 show:blurb '''This is a multi-line  \n"
				"literal with many quotes''' .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE12) {

		TurtleStringParser parser(
				"@prefix : <http://example.org/elements> .                                                                              \n"
				"<http://en.wikipedia.org/wiki/Helium>                                                                                  \n"
				"    :atomicNumber 2 ;                                                                                    \n"
				"    :atomicMass 4.002602 ;                                                                              \n"
				"    :specificGravity 1.663E-4 .       ");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE13) {

		TurtleStringParser parser(
				"@prefix : <http://example.org/stats> .\n"
				"<http://somecountry.example/census2007>\n"
				"    :isLandlocked false .     ");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE14) {

		TurtleStringParser parser(
				"@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
				"\n"
				"_:alice foaf:knows _:bob .\n"
				"_:bob foaf:knows _:alice .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE15) {

		TurtleStringParser parser(
				"@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
				"\n"
				"[] foaf:knows [ foaf:name \"Bob\" ] .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE16) {

		TurtleStringParser parser(
				"@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n"
				"\n"
				"[ foaf:name \"Alice\" ] foaf:knows [\n"
				"    foaf:name \"Bob\" ;\n"
				"    foaf:knows [\n"
				"        foaf:name \"Eve\" ] ;\n"
				"    foaf:mbox <bob@example.com> ] .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE17) {

		TurtleStringParser parser(
				"_:a <http://xmlns.com/foaf/0.1/name> \"Alice\" .\n"
				"_:a <http://xmlns.com/foaf/0.1/knows> _:b .\n"
				"_:b <http://xmlns.com/foaf/0.1/name> \"Bob\" .\n"
				"_:b <http://xmlns.com/foaf/0.1/knows> _:c .\n"
				"_:c <http://xmlns.com/foaf/0.1/name> \"Eve\" .\n"
				"_:b <http://xmlns.com/foaf/0.1/mbox> <bob@example.com> .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE18) {

		TurtleStringParser parser(
				"@prefix : <http://example.org/foo> .\n"
				":subject :predicate ( :a :b :c ) .\n"
				"\n"
				":subject :predicate2 () .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE19) {

		TurtleStringParser parser(
				"@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
				"@prefix dc: <http://purl.org/dc/elements/1.1/> .\n"
				"@prefix ex: <http://example.org/stuff/1.0/> .\n"
				"\n"
				"<http://www.w3.org/TR/rdf-syntax-grammar>\n"
				"  dc:title \"RDF/XML Syntax Specification (Revised)\" ;\n"
				"  ex:editor [\n"
				"    ex:fullname \"Dave Beckett\";\n"
				"    ex:homePage <http://purl.org/net/dajobe/>\n"
				"  ] .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE20) {

		TurtleStringParser parser(
				"PREFIX : <http://example.org/stuff/1.0/>\n"
				":a :b ( \"apple\" \"banana\" ) .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE21) {

		TurtleStringParser parser(
				"@prefix : <http://example.org/stuff/1.0/> .\n"
				"@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
				":a :b\n"
				"  [ rdf:first \"apple\";\n"
				"    rdf:rest [ rdf:first \"banana\";\n"
				"               rdf:rest rdf:nil ]\n"
				"  ] .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE22) {

		TurtleStringParser parser(
				"@prefix : <http://example.org/stuff/1.0/> .\n"
				"\n"
				":a :b \"The first line\\nThe second line\\n  more\" .\n"
				"\n"
				":a :b \"\"\"The first line\n"
				"The second line\n"
				"  more\"\"\" .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE23) {

		TurtleStringParser parser(
				"@prefix : <http://example.org/stuff/1.0/> .\n"
				"(1 2.0 3E1) :p \"w\" .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE24) {

		TurtleStringParser parser(
				"@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
				"PREFIX : <http://example.org/stuff/1.0/> \n"
				"    _:b0  rdf:first  1 ;\n"
				"          rdf:rest   _:b1 .\n"
				"    _:b1  rdf:first  2.0 ;\n"
				"          rdf:rest   _:b2 .\n"
				"    _:b2  rdf:first  3E1 ;\n"
				"          rdf:rest   rdf:nil .\n"
				"    _:b0  :p         \"w\" . ");
		auto it = parser.begin();
		std::cout << std::endl;
		it++;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}


	TEST(TurtleOfficalExamplesTests, EXAMPLE25) {

		TurtleStringParser parser(
				"PREFIX : <http://example.org/stuff/1.0/>\n"
				"(1 [:p :q] ( 2 ) ) :p2 :q2 .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}

	TEST(TurtleOfficalExamplesTests, EXAMPLE26) {

		TurtleStringParser parser(
				"@prefix rdf: <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n"
				"PREFIX : <http://example.org/stuff/1.0/> \n"
				"    _:b0  rdf:first  1 ;\n"
				"          rdf:rest   _:b1 .\n"
				"    _:b1  rdf:first  _:b2 .\n"
				"    _:b2  :p         :q .\n"
				"    _:b1  rdf:rest   _:b3 .\n"
				"    _:b3  rdf:first  _:b4 .\n"
				"    _:b4  rdf:first  2 ;\n"
				"          rdf:rest   rdf:nil .\n"
				"    _:b3  rdf:rest   rdf:nil .");
		auto it = parser.begin();
		std::cout << std::endl;
		while (it) {
			auto triple = *it;
			std::cout << triple.subject().getIdentifier() << " "
					  << triple.predicate().getIdentifier() << " "
					  << triple.object().getIdentifier()
					  << std::endl;
			it++;
		}
	}
}// namespace Dice::tests::rdf_parser::turtle_official_examples_tests