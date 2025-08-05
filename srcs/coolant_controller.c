/***********************************************************************
* Filename: coolant_controller.c
* File description: This file process main logic of cooler and
* regulates pump and fan power using
* Proportional integral Derivative controller. 
* Used formula is:
* ` u(t) = kp * temp_error + ki * integral + kd * derivative `
*
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 31 07 2025
***********************************************************************/

#include <stdbool.h>

#include "CAN/can_proceed.h"
#include "coolant_controller.h"
#include "drivers/drivers.h"
#include "main.h"

/* Those values are approximate. Should be tuned */
static pid_controller_t pid_controller_val = {
    /* shows how much we must react on error */
    .kp = 3,
    /* shows how much we must react on integral changes */
    .ki = 1,
    .kd = 3,
    .prev_error = 0,
    /* Summarize all errors */
    .integral = 0,
};

static int16_t pid_controller(coolant_t *coolant, int16_t current_temperature) {
    int16_t temp_error = coolant->temperature_setpoint - current_temperature;
    pid_controller_val.integral += temp_error;
    int16_t derivative = temp_error - pid_controller_val.prev_error;
    pid_controller_val.prev_error = temp_error;
    int16_t output = (pid_controller_val.kp * temp_error) + (pid_controller_val.ki * pid_controller_val.integral) + 
                    (pid_controller_val.kd * derivative);
    printf("p = %d i = %d d = %d\n",
        pid_controller_val.kp * temp_error, pid_controller_val.ki * pid_controller_val.integral, pid_controller_val.kd * derivative);
 
    return output;
}

void regulate_cooling(int16_t pid_value) {
    enum fan_speed_e fan_speed;
    enum pump_speed_e pump_speed;

    if (pid_value <= -50) {
        /* Too hot. Go full power */
        fan_speed = FAN_SPEED_MAX;
        pump_speed = PUMP_SPEED_MAX;
    } else if (pid_value <= -40) {
        fan_speed = FAN_SPEED_MAX;
        pump_speed = PUMP_SPEED_HIGH;
    } else if (pid_value <= -30) {
        fan_speed = FAN_SPEED_HIGH;
        pump_speed = PUMP_SPEED_AVERAGE;
    } else if (pid_value <= -20) {
        fan_speed = FAN_SPEED_AVERAGE;
        pump_speed = PUMP_SPEED_LOW;
    } else if (pid_value <= -10) {
        fan_speed = FAN_SPEED_LOW;
        pump_speed = PUMP_SPEED_LOW;
    } else if (pid_value > 0) {
        /* Systems temperarure is below setpoint. All good */
        fan_speed = FAN_SPEED_OFF;
        pump_speed = PUMP_SPEED_OFF;
    }
    /* TODO: check previous values and compare with current
     * to not overwrite if unnesessary */
    drv_fan_set_speed(fan_speed);
    drv_pump_set_speed(pump_speed);
}

enum coolant_error_status_e coolant_logic_proceed(coolant_t *coolant) {
    int16_t current_temperature = drv_temperature_sensor_get_temperature();
    int16_t pid_coefficient;
    enum coolant_error_status_e ret_value = COOLANT_ON_OK;

    printf("current_temperature = %d\n", current_temperature);
    /* Sensor could't read temperature properly. Malfunction */
    if (current_temperature == DRV_TEMPERATURE_SENSOR_ERROR) {
        coolant->err_bits.temp_sensor_malfunction = true;
        ret_value = COOLANT_MALFUNCTION;
    } else if (current_temperature >= DCDC_TEMPERATURE_HIGH_LIMIT) {
        coolant->err_bits.overheat = true;
        /* set pump and fan full power */
        drv_fan_set_speed(FAN_SPEED_MAX);
        drv_pump_set_speed(PUMP_SPEED_MAX);
        /* Report over temperature error */
        can_over_temperature_error_report(coolant, current_temperature, true);
        ret_value = COOLANT_OVERHEAT_ERROR;
    } else if (current_temperature <= DCDC_TEMPERATURE_LOW_LIMIT(coolant->temperature_setpoint)) {
        /* If current temperature much cooler than setpoint we're good. Nothing to do. */
        drv_fan_set_speed(FAN_SPEED_OFF);
        drv_pump_set_speed(PUMP_SPEED_OFF);
    } else {
        if (coolant->err_bits.overheat) {
            /* Danger has gone. We're safe */
            coolant->err_bits.overheat = false;
            /* Report over temperature error has gone */
            can_over_temperature_error_report(coolant, current_temperature, false);
        }

        pid_coefficient = pid_controller(coolant, current_temperature);
        regulate_cooling(pid_coefficient);
        printf("pid=%d\n", pid_coefficient);
    }

    return ret_value;
}

/* Wrapper over drv_ignition_switch_get_state() */
enum coolant_error_status_e get_ignition_switch_state(void) {
    enum ignition_switch_error_status_e ignition_switch_state = drv_ignition_switch_get_state();

    if (ignition_switch_state == IGNITION_SWITCH_OFF) {
        return COOLANT_OFF;
    } else if (ignition_switch_state == IGNITION_SWITCH_ERROR) {
        return COOLANT_MALFUNCTION;
    }

    return COOLANT_ON_OK;
}
