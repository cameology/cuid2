# executable
set(TEST ${CMAKE_CURRENT_SOURCE_DIR})
add_executable(cuidtest ${TEST}/suites.cc)


# include dirs
target_include_directories(cuidtest PRIVATE ${PROJECT_SOURCE_DIR}/includes)
target_include_directories(cuidtest PRIVATE ${MAIN})


# Test Suites
enable_testing()
target_link_libraries(cuidtest PRIVATE
    GTest::gtest_main
)