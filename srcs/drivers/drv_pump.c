/***********************************************************************
* Filename: drv_pump.c
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include "drv_pump.h"

static pump_t pump;

enum pump_state_e drv_pump_get_state(void) {

}
enum pump_speed_state_e drv_pump_get_speed(void) {

}

void drv_pump_set_state(enum pump_state_e state) {
    pump.state = state;
}

void drv_pump_set_speed(enum pump_speed_state_e speed) {
    pump.speed = speed;
}

void drv_turn_off_pump(void) {
    drv_pump_set_speed(PUMP_SPEED_OFF);
    drv_pump_set_state(PUMP_OFF);
}
