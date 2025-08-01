/***********************************************************************
* Filename: coolant_controller.c
* File description: Proportional integral Derivative controller.
* Used formula is
* u(t) = kp * temp_error + ki * integral + kd * derivative
*
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 31 07 2025
***********************************************************************/

#include "main.h"
#include "coolant_controller.h"
#include "drivers/drivers.h"

/* Those values are approximate. Shoul be tuned */
static pid_controller_t pid_controller_val = {
    .kp = 1,
    /* shows how much we must react on integral changes */
    .ki = 0,
    .kd = 0,
    .prev_error = 0,
    .integral = 0,
};

int8_t pid_controller(coolant_t *coolant, int8_t current_temperature) {
    int8_t temp_error = coolant->temperature_setpoint - current_temperature;
    pid_controller_val.integral += temp_error;
    int8_t derivative = temp_error - pid_controller_val.prev_error;
    int8_t output = pid_controller_val.kp * temp_error + pid_controller_val.ki
                    * pid_controller_val.integral + pid_controller_val.kd * derivative;

    return output;
}

enum coolant_error_status_e coolant_logic_proceed(coolant_t *coolant) {
    int8_t current_temperature = drv_temperature_sensor_get_temperature();

    /* Sensor could't read temperature properly. Malfunction */
    if (current_temperature == DRV_TEMPERATURE_SENSOR_ERROR)
        return COOLANT_MALFUNCTION;
    if (current_temperature >= DCDC_TEMPERATURE_LIMIT)
        return COOLANT_OVERHEAT_ERROR;
    else
        printf("pid=%d\n", pid_controller(coolant, current_temperature));

    return COOLANT_OK;
}

enum coolant_error_status_e get_ignition_switch_state() {
    enum ignition_switch_error_status_e ignition_switch_state = drv_get_ignition_switch_state();

    if (ignition_switch_state == IGNITION_SWITCH_OFF)
        return COOLANT_OFF;
    else if (ignition_switch_state == IGNITION_SWITCH_ERROR)
        return COOLANT_MALFUNCTION;

    return COOLANT_OK;
}
