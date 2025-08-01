/***********************************************************************
* Filename: drv_fan.c
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include "drv_fan.h"

static fan_t fan;

enum fan_state_e drv_fan_get_state(void) {
    return fan.state;
}

enum fan_speed_state_e drv_fan_get_speed(void) {
    return fan.speed;
}

void drv_fan_set_state(enum fan_state_e state) {
    fan.state = state;
}

void drv_fan_set_speed(enum fan_speed_state_e speed) {
    fan.speed = speed;
}

void drv_turn_off_fan(void) {
    drv_fan_set_speed(FAN_SPEED_OFF);
    drv_fan_set_state(FAN_OFF);
}

