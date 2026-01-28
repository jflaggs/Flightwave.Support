cmake_minimum_required(
VERSION 3.21
)

project(Flightwave
    VERSION 1.0.0
    LANGUAGES CXX
)

# ---- Library ----
add_library(Flightwave
    src/Flightwave.cpp
)

# ---- Include directories ----
target_include_directories(Flightwave
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# ---- C++ standard ----
set_target_properties(Flightwave PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# ---- Install library ----
install(TARGETS Flightwave
    EXPORT FlightwaveTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# ---- Install headers ----
install(DIRECTORY include/
    DESTINATION include
)

# ---- Export targets with namespace ----
install(EXPORT FlightwaveTargets
    NAMESPACE Flightwave::
    DESTINATION lib/cmake/Flightwave
)

# ---- Generate config files ----
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    FlightwaveConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/FlightwaveConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/FlightwaveConfig.cmake
    INSTALL_DESTINATION lib/cmake/Flightwave
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/FlightwaveConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/FlightwaveConfigVersion.cmake
    DESTINATION lib/cmake/Flightwave
)

