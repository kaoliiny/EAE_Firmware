/***********************************************************************
* Filename: drv_fan.h
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _DRV_FAN_H_
#define _DRV_FAN_H_

#include <stdint.h>

enum fan_state_e {
    FAN_OFF,
    FAN_ON,
    FAN_MALFUNCTION
};

enum fan_speed_e {
    FAN_SPEED_OFF,
    FAN_SPEED_LOW,
    FAN_SPEED_AVERAGE,
    FAN_SPEED_HIGH,
    FAN_SPEED_MAX
};

typedef struct fan_s {
    enum fan_state_e state;
    enum fan_speed_e speed;
} fan_t;

void drv_fan_set_state(enum fan_state_e state);
void drv_fan_set_speed(enum fan_speed_e speed);
enum fan_state_e drv_fan_get_state(void);
enum fan_speed_e drv_fan_get_speed(void);
void drv_fan_turn_off(void);
void drv_fan_init(void);

#endif
