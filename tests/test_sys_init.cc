#include <gtest/gtest.h>
extern "C" {
    #include "../srcs/sys_init.h"
    #include "../srcs/drivers/drv_pump.h"
    #include "../srcs/drivers/drv_fan.h"
}

/* Mock init functions */

static enum fan_state_e fan_err_no = FAN_OFF;
static enum pump_state_e pump_err_no = PUMP_OFF;

class SysInitFixture : public ::testing::Test {
protected:
    void SetUp() override {
        // Runs before each TEST_F
        memset(&coolant, 0, sizeof(coolant_t));
        temperature = 25;
    }

    void TearDown() override {
        // Runs after each TEST_F
    }

    // Shared variables for test cases
    coolant_t coolant;
    uint8_t temperature;

};

// coolant_t SysInitFixture::coolant;
// uint8_t CoolantTest::temperature;

extern "C" void can_init(void) {
}

extern "C" enum fan_state_e drv_fan_init(void) {
    return fan_err_no;
}

extern "C" enum pump_state_e drv_pump_init(void) {
    return pump_err_no;
}

extern "C" void drv_fan_turn_off(void) {
}

extern "C" void drv_pump_turn_off(void) {
}

TEST_F(SysInitFixture, FanMalfunction) {
    enum coolant_error_status_e err_no = COOLANT_MALFUNCTION;
    fan_err_no = FAN_MALFUNCTION;

    EXPECT_EQ(err_no, sys_init(&coolant, temperature));
    // Ensure error bits properly set
    EXPECT_EQ(true, coolant.err_bits.fan_malfunction);
    EXPECT_EQ(false, coolant.err_bits.pump_malfunction);
}

TEST_F(SysInitFixture, PumpMalfunction) {
    enum coolant_error_status_e err_no = COOLANT_MALFUNCTION;
    pump_err_no = PUMP_MALFUNCTION;

    EXPECT_EQ(err_no, sys_init(&coolant, temperature));
    // Ensure error bits properly set
    EXPECT_EQ(false, coolant.err_bits.fan_malfunction);
    EXPECT_EQ(true, coolant.err_bits.pump_malfunction);
}

TEST_F(SysInitFixture, PositiveScenario) {
    enum coolant_error_status_e err_no = COOLANT_OFF;
    fan_err_no = FAN_OFF;
    pump_err_no = PUMP_OFF;

    EXPECT_EQ(err_no, sys_init(&coolant, temperature));
    // Ensure error bits was set properly
    EXPECT_EQ(false, coolant.err_bits.fan_malfunction);
    EXPECT_EQ(false, coolant.err_bits.pump_malfunction);
    // Ensure twmperature setpoint was set properly
    EXPECT_EQ(temperature, coolant.temperature_setpoint);
}
