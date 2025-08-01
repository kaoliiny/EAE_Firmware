/***********************************************************************
* Filename: coolant_controller.h
* File description: This file process main logic of cooler and
* regulates pump and fan power using
* Proportional integral Derivative controller. 
* Used formula is:
* ` u(t) = kp * temp_error + ki * integral + kd * derivative `
*
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 31 07 2025
***********************************************************************/

#ifndef _PID_CONTROLLER_H_
#define _PID_CONTROLLER_H_

/* Celsius */
#define DCDC_TEMPERATURE_LIMIT 110

typedef struct pid_controller_s {
    const int8_t kp;
    const int8_t ki;
    const int8_t kd;
    int8_t prev_error;
    int16_t integral;
} pid_controller_t;

/* Wrapper over drives function drv_ignition_switch to achive proper error handling. */
enum coolant_error_status_e get_ignition_switch_state(void);

enum coolant_error_status_e coolant_logic_proceed(coolant_t *coolant);

#endif
