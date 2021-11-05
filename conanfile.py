from conans import ConanFile, CMake
from conans.tools import load
import re, os


class RDFParser(ConanFile):
    name = "rdf-parser"
    author = "DICE Group <info@dice-research.org>"
    description = "RDF parser used by [Tentris](https://github.com/dice-group/tentris). It uses [PEGTL](https://github.com/taocpp/PEGTL), Parsing Expression Grammar Library, to parse RDF files (currently supported: ntriple, turtle). "
    homepage = "https://github.com/dice-group/rdf-parser"
    url = homepage
    license = "AGPL"
    options = {}
    default_options = { }
    topics = ("dice-group", "RDF", "parser", "semantic web", "turtle", "ntriple")
    settings = "build_type", "compiler", "os", "arch"
    requires = "boost/1.77.0", "taocpp-pegtl/3.1.0", "fmt/8.0.1", "dice-hash/0.2.0@dice-group/stable", "robin-hood-hashing/3.11.3"
    generators = "cmake", "cmake_find_package", "cmake_paths"
    exports = "LICENSE"
    exports_sources = "include/*", "CMakeLists.txt", "cmake/dummy-config.cmake.in"
    no_copy_source = True

    def set_version(self):
        if not hasattr(self, 'version') or self.version is None:
            cmake_file = load(os.path.join(self.recipe_folder, "CMakeLists.txt"))
            self.version = re.search("project\(rdf-parser VERSION (.*)\)", cmake_file).group(1)

    def package(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.install()

    def package_id(self):
        self.info.header_only()
