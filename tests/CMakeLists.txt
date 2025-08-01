add_executable(
  test1
  test1.cc
)
target_link_libraries(
  test1
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test1)
