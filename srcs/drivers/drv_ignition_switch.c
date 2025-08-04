/***********************************************************************
* Filename: drv_ignition_switch.c
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include <stdbool.h>
#include "drv_ignition_switch.h"

/* For simplicity, currently our dummy ignition switch always returns `ON` state. */
enum ignition_switch_error_status_e drv_ignition_switch_get_state(void) {
    return IGNITION_SWITCH_ON;
}
