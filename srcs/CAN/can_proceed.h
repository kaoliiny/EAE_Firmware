/***********************************************************************
* Filename: can_proceed.h
* File description: highlevel wrappers over CAN specific protocol.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 03 08 2025
***********************************************************************/

#include "../main.h"

void can_init(void);

void can_over_temperature_error_report(coolant_t *coolant, int16_t temp, uint8_t is_error_active);

void can_malfunction_error_report(coolant_t *coolant, uint8_t is_error_active);

void can_proceed(coolant_t *coolant);
