/***********************************************************************
* Filename: drv_ignition_switch.h
* File description: This header emulates ignition switch behavior.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _IGNITION_SWITCH_H_
#define _IGNITION_SWITCH_H_

#include <stdint.h>

enum ignition_switch_error_status_e {
    IGNITION_SWITCH_OFF,
    IGNITION_SWITCH_ON,
    IGNITION_SWITCH_ERROR
};

/* This function emulates ignition switch states.
 * We assume that it has three states ON/OFF/ERROR.
 * For simplicity, currently our dummy ignition switch always returns `ON` state.
 */
enum ignition_switch_error_status_e drv_ignition_switch_get_state(void);

#endif
