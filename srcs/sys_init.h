/***********************************************************************
* Filename: sys_init.h
* File description: Header for all system's componnents
* initialization and deinitialization.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _SYS_INIT_H_
#define _SYS_INIT_H_

#include "main.h"

enum coolant_error_status_e sys_init(coolant_t *coolant, void *temperature_sp);
void sys_deinit(void);
void sys_shutdown(void);
void turn_off_components(void);

#endif
