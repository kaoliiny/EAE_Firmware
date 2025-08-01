/***********************************************************************
* Filename: drv_pump.h
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _DRV_PUMP_H_
#define _DRV_PUMP_H_

enum pump_state_e {
    PUMP_OFF,
    PUMP_ON,
    PUMP_MALFUNCTION
};

enum pump_speed_state_e {
    PUMP_SPEED_OFF,
    PUMP_SPEED_LOW,
    PUMP_SPEED_AVERAGE,
    PUMP_SPEED_HIGH,
    PUMP_SPEED_MAX
};

typedef struct pump_s {
    enum pump_state_e state;
    enum pump_speed_state_e speed;
} pump_t;

void drv_pump_set_state(enum pump_state_e state);
void drv_pump_set_speed(enum pump_speed_state_e speed);
enum pump_state_e drv_pump_get_state(void);
enum pump_speed_state_e drv_pump_get_speed(void);
void drv_turn_off_pump(void);

#endif
