from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps

class FlightwaveConan(ConanFile):
    name = "flightwave"
    version = "3.0.0"
    license = "MIT"
    author = "Johnathan Flaggs"
    url = "https://example.com"
    description = "Flightwave Interview C++ Library"
    topics = ("cpp", "library")
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "src/*", "include/*", "cmake/*", "CMakeLists.txt"
    generators = "CMakeDeps", "CMakeToolchain"
    no_copy_source = True

    def layout(self):
        self.folders.source = "."
        self.folders.build = "build"

#    def generate(self):
#        tc = CMakeToolchain(self)
#        tc.generate()
#        deps = CMakeDeps(self)
#        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def package_info(self):
        self.cpp_info.set_property("cmake_file_name", "Flightwave")
        self.cpp_info.set_property("cmake_target_name", "Flightwave::Flightwave")
        self.cpp_info.includedirs = ["include"]
