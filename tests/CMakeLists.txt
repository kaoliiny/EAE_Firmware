add_executable(
  test_EAE_Firmware
  test_sys_init.cc
  ../srcs/sys_init.c
  test_coolant_controller.cc
  ../srcs/coolant_controller.c
)

target_link_libraries(
  test_EAE_Firmware
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_EAE_Firmware)
