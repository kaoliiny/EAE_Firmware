/***********************************************************************
* Filename: sys_init.c
* File description: This file is corresponding for all system's componnents
* initialization and deinitialization.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include <stdlib.h>
#include <stdbool.h>

#include "CAN/can_proceed.h"
#include "drivers/drivers.h"
#include "sys_init.h"

static void setpoints_init(coolant_t *coolant, uint8_t temperature_sp) {
    coolant->temperature_setpoint = temperature_sp;
}

void turn_off_components(void) {
    drv_fan_turn_off();
    drv_pump_turn_off();
}

void sys_deinit(void) {
    /* drivers deinit. Currently no drivers so nothing to deitit. All dummy */
    /* CAN bus deinit */
}

void sys_shutdown(void) {
    turn_off_components();
    sys_deinit();
}

enum coolant_error_status_e sys_init(coolant_t *coolant, uint8_t temperature_sp) {
    /* drivers init. Currently no drivers no init. All dummy */
    if (drv_pump_init() == PUMP_MALFUNCTION) {
        coolant->err_bits.pump_malfunction = true;
        return COOLANT_MALFUNCTION;
    }
    if (drv_fan_init() == FAN_MALFUNCTION) {
        coolant->err_bits.fan_malfunction = true;
        return COOLANT_MALFUNCTION;
    }
    /* setpoints_init */
    setpoints_init(coolant, temperature_sp);
    /* CAN bus init */
    can_init();

    return COOLANT_OFF;
}
