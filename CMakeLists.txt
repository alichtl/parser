cmake_minimum_required(VERSION 3.14)
project(parser)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(parser parser.cc)
add_executable(parser_test parser_test.cc)
target_link_libraries(parser_test GTest::gtest_main)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/cb455a71fb23303e37ce8ee5b1cde6a2c18f66a5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
gtest_discover_tests(parser_test)
