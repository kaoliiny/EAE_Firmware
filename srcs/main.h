/***********************************************************************
* Filename: main.h
* File description: This file is the main header for coolant project.
* It contains definitions for main routine and FSM.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdint.h>
#include <stdio.h>

/* ! CANopen isn't defined by default. This is only a simulation example.
 * Do not define it as it will crush the build.
 * TODO: add real CanOpenNode support https://github.com/CANopenNode/CANopenNode/. 
 * In current implementation we only pretend to use it.
 */
#define CAN_OPEN 0

/* Low edge value in Celsius degrees to be set as reference  */
#define TEMPERATURE_LOW_SETPOINT 20
/* High edge value in Celsius degrees to be set as reference  */
#define TEMPERATURE_HIGH_SETPOINT 92

#define CYCLE_TAKT_NS 500000000 /* 0.5s */

enum coolant_state_e {
    /* System boot and init. */
    STARTUP,
    /* Ignition switch is off. Nothing to do. */
    IDLE,
    /* Normal active state when fan and pump are fuctioning and the temperature whithin normal limils. */
    ACTIVE,
    /* An error state/measurements were received from one of the components */
    MALFUNCTION_ERROR_SHUTDOWN,
};

/* High level error handle for coolant */
enum coolant_error_status_e {
    /* Ignition switch OFF */
    COOLANT_OFF,
    /* Ignition switch ON. System OK */
    COOLANT_ON_OK,
    /* One of the components returned malfunction */
    COOLANT_MALFUNCTION,
    /* DC-DC/AC-DC temperature goes over limit and */
    COOLANT_OVERHEAT_ERROR,
    /* Argumenst are incorrect */
    COOLANT_VALIDATION_ERROR
};

typedef struct {
    /* If DC-DC/AC-DC temperature goes over limit and we couldn't stop it.
    The only thing we can do at this point is to go full power, send error and pray (x_x).
    Basically in this mode we're waiting for system shutdown command, ignition switch off
    or untill temperature stabilizes.
    We aren't able to control DC/DC and DC/AC and there's no point to simply shutdown
    the coolant as it will lead to overheat grow until it damages system.*/
    uint8_t overheat : 1;
    uint8_t pump_malfunction : 1;
    uint8_t fan_malfunction : 1;
    uint8_t ignition_switch_malfunction : 1;
    uint8_t temp_sensor_malfunction : 1;
} error_field_t;

typedef struct coolant_s {
    enum coolant_state_e state;
    uint8_t pump_power;
    uint8_t fan_power;
    int8_t ignition_swith_state;
    uint8_t temperature_setpoint;
    error_field_t err_bits;
#if CAN_OPEN
    CO_t* CO = NULL; 
#endif
} coolant_t;

#endif
