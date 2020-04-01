from conans import ConanFile, CMake


class RDFParser(ConanFile):
    name = "rdf-parser"
    version = "0.9"
    author = "DICE Group <info@dice-research.org>"
    description = "RDF parser used by [Tentris](https://github.com/dice-group/tentris). It uses [PEGTL](https://github.com/taocpp/PEGTL), Parsing Expression Grammar Library, to parse RDF files (currently supported: ntriple, turtle). "
    homepage = "https://github.com/dice-group/rdf-parser"
    url = homepage
    license = "AGPL"
    topics = ("dice-group", "RDF", "parser", "semantic web", "turtle", "ntriple")
    settings = "build_type", "compiler", "os", "arch"
    requires = "boost/1.71.0@conan/stable", "pegtl/2.8.1@taocpp/stable", "gtest/1.8.1@bincrafters/stable", "fmt/6.0.0@bincrafters/stable", "abseil/20181200@bincrafters/stable"
    generators = "cmake", "cmake_find_package", "cmake_paths"
    exports = "LICENSE"
    exports_sources = "include/*", "CMakeLists.txt", "cmake/dummy-config.cmake.in"
    no_copy_source = True


    def package(self):
        cmake = CMake(self)
        cmake.definitions["rdf_parser_BUILD_TESTS"] = "OFF"
        cmake.configure()
        cmake.install()

    def package_id(self):
        self.info.header_only()
