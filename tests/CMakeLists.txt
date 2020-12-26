project(Google_tests)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(binary_search_tree_tests BSTTest.cpp)
target_link_libraries(binary_search_tree_tests gtest gtest_main)
