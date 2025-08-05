#include <gtest/gtest.h>
extern "C" {
    #include "../srcs/main.h"
    #include "../srcs/coolant_controller.h"
    #include "../srcs/drivers/drv_pump.h"
    #include "../srcs/drivers/drv_fan.h"
    #include "../srcs/drivers/drv_temperature_sensor.h"
    #include "../srcs/drivers/drv_ignition_switch.h"
    #include "../srcs/CAN/can_proceed.h"
}

static int16_t temperature;
static enum ignition_switch_error_status_e ignition_switch_state;
static enum fan_speed_e fan_speed = FAN_SPEED_OFF;
static enum pump_speed_e pump_speed = PUMP_SPEED_OFF;

class CoolantControllerFixture : public ::testing::Test {
    protected:
        void SetUp() override {
            // Runs before each TEST_F
            memset(&coolant, 0, sizeof(coolant_t));
            temperature = 25;
            ignition_switch_state = IGNITION_SWITCH_OFF;
        }
        
        void TearDown() override {
            // Runs after each TEST_F
        }
    public:
    
    // Shared variables for test cases
    coolant_t coolant;
};

// coolant_t CoolantControllerFixture::coolant;
// uint8_t CoolantControllerFixture::temperature;


////////////////// Mock driver functions //////////////////
int16_t drv_temperature_sensor_get_temperature(void) {
    return temperature;
}

enum ignition_switch_error_status_e drv_ignition_switch_get_state(void) {
    return ignition_switch_state;
}

void can_over_temperature_error_report(coolant_t *coolant, int16_t temp, uint8_t is_error_active) {
}

void can_malfunction_error_report(coolant_t *coolant, uint8_t is_error_active){

}

void drv_pump_set_speed(enum pump_speed_e speed) {

}

enum pump_speed_e drv_pump_get_speed(void) {
    return pump_speed;
}

void drv_fan_set_speed(enum fan_speed_e speed) {

}

enum fan_speed_e drv_fan_get_speed(void) {
    return fan_speed;
}

TEST_F(CoolantControllerFixture, TempSensorMalfunction) {
    enum coolant_error_status_e err_no = COOLANT_MALFUNCTION;
    temperature = DRV_TEMPERATURE_SENSOR_ERROR;

    EXPECT_EQ(err_no, coolant_logic_proceed(&coolant));
    // Ensure error bits properly set
    EXPECT_EQ(true, coolant.err_bits.temp_sensor_malfunction);
    EXPECT_EQ(false, coolant.err_bits.fan_malfunction);
    EXPECT_EQ(false, coolant.err_bits.pump_malfunction);
}

TEST_F(CoolantControllerFixture, TempSensorOverheat) {
    enum coolant_error_status_e err_no = COOLANT_OVERHEAT_ERROR;
    temperature = DCDC_TEMPERATURE_HIGH_LIMIT;

    EXPECT_EQ(err_no, coolant_logic_proceed(&coolant));
    // Ensure error bits properly set
    EXPECT_EQ(false, coolant.err_bits.temp_sensor_malfunction);
    EXPECT_EQ(false, coolant.err_bits.fan_malfunction);
    EXPECT_EQ(false, coolant.err_bits.pump_malfunction);
    EXPECT_EQ(true, coolant.err_bits.overheat);
}

// Temperature normalized to normal state
TEST_F(CoolantControllerFixture, TempSensorOverheatNormalized) {
    enum coolant_error_status_e err_no = COOLANT_ON_OK;
    temperature = 42;
    coolant.err_bits.overheat = 1;

    EXPECT_EQ(err_no, coolant_logic_proceed(&coolant));

    // Ensure error bits properly set
    EXPECT_EQ(false, coolant.err_bits.temp_sensor_malfunction);
    EXPECT_EQ(false, coolant.err_bits.fan_malfunction);
    EXPECT_EQ(false, coolant.err_bits.pump_malfunction);
    EXPECT_EQ(false, coolant.err_bits.overheat);
}
