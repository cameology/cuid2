include(FetchContent)
Set(FETCHCONTENT_QUIET false)


# OpenSSL
find_package(OpenSSL REQUIRED)

if(ENABLE_TESTS)
    # GoogleTest
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.16.0
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()