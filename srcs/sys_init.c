/***********************************************************************
* Filename: sys_init.c
* File description: This file is corresponding for all system's componnents
* initialization and deinitialization.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include <stdlib.h>
#include "drivers/drivers.h"
#include "sys_init.h"

static void canopen_init(void) {
    
}

static void setpoints_init(coolant_t *coolant, void *temperature_sp) {
    coolant->temperature_setpoint = atoi(temperature_sp);
}

void turn_off_components(void) {
    drv_fan_turn_off();
    drv_pump_turn_off();
}

void sys_deinit(void) {
    /* drivers deinit. Currently no drivers so nothing to deitit. All dummy */
}

int8_t sys_init(coolant_t *coolant, void *temperature_sp) {
    /* drivers init. Currently no drivers no init. All dummy */
    drv_pump_init();
    drv_fan_init();
    /* setpoints_init */
    setpoints_init(coolant, temperature_sp);
    /* CAN bus init */
    canopen_init();

    return 0;
}
