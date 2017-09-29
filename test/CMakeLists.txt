add_subdirectory(lib/googletest)

add_executable(wordCountTest wordCountTest.cpp)
target_link_libraries(wordCountTest src gtest gtest_main)