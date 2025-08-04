add_executable(
  test_sys_init
  test_sys_init.cc
  ../srcs/sys_init.c
)
target_link_libraries(
  test_sys_init
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_sys_init)
