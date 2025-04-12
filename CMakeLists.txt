cmake_minimum_required(VERSION 3.14.0)
project(cuid2 VERSION 0.1.0 DESCRIPTION "")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/target/bin)


# Dependencies
include(cmake/macros.cmake)
include(cmake/dependencies.cmake)


# Define Library
set(CUID_SRC ${PROJECT_SOURCE_DIR}/src)

addLibrary(cuid2 
    VERSION     ${PROJECT_VERSION}
    SOVERSION   ${PROJECT_VERSION_MAJOR}
    INCLUDE     ${PROJECT_SOURCE_DIR}/include

    LINK_LIBRARIES
        OpenSSL::SSL
        OpenSSL::Crypto

    SOURCES     
        ${CUID_SRC}/cuid2.cc
        ${CUID_SRC}/utils.cc
)


# Test Suites
enable_testing()
set(CUID2_TEST ${PROJECT_SOURCE_DIR}/test)

addExecutable(utils ${CUID2_TEST}/utils.cc
    cuid2
    GTest::gtest_main
)
