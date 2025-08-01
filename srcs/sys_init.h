/***********************************************************************
* Filename: sys_init.h
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _SYS_INIT_H_
#define _SYS_INIT_H_

#include "main.h"

int8_t sys_init(coolant_t *coolant, void *temperature_sp);
void sys_deinit(void);
void turn_off_components(void);

#endif
