/***********************************************************************
* Filename: drv_pump.c
* File description: pump driver's emulation.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include "drv_pump.h"

static pump_t pump;

enum pump_state_e drv_pump_get_state(void) {
    return pump.state;
}

enum pump_speed_e drv_pump_get_speed(void) {
    return pump.speed;
}

void drv_pump_set_state(enum pump_state_e state) {
    pump.state = state;
}

void drv_pump_set_speed(enum pump_speed_e speed) {
    pump.speed = speed;
}

void drv_pump_turn_off(void) {
    drv_pump_set_speed(PUMP_SPEED_OFF);
    drv_pump_set_state(PUMP_OFF);
}

enum pump_state_e drv_pump_init(void) {
    drv_pump_set_state(PUMP_ON);
    drv_pump_set_speed(PUMP_SPEED_OFF);

    return PUMP_ON;
}
