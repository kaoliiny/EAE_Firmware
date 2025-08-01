/***********************************************************************
* Filename: main.c
* File description: This file is start point and main loop for coolant project.
* It manages validation and the main FSM.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "sys_init.h"
#include <string.h>
#include "drivers/drivers.h"
#include "main.h"
#include "coolant_controller.h"
#include "unistd.h"

static int args_validation(int argc, void **argv) {
    int8_t temperature_sp;

    if (argc == 2) {
        temperature_sp = atoi(argv[1]);
        if (temperature_sp >= TEMPERATURE_LOW_SETPOINT && temperature_sp < TEMPERATURE_HIGH_SETPOINT) {
            return 0;
        }
    }

    /* + 1 needed to trim the last '/' from stringd to get file name from full path name. */
    printf("Usage: %s TEMPERATURE_SETPOINT\n", strrchr(argv[0], '/') + 1);
    printf("TEMPERATURE_SETPOINT is a reference temperature value in %d-%d Celsius degree range.\n",
        TEMPERATURE_LOW_SETPOINT, TEMPERATURE_HIGH_SETPOINT);

    return COOLANT_VALIDATION_ERROR;
}

__attribute__((noreturn))
static void main_loop(coolant_t *coolant, void *temperature_sp) {
    while (true) {
        switch(coolant->state) {
            case STARTUP:
                if (sys_init(coolant, temperature_sp) == 0) {
                    coolant->state = IDLE;
                } else {
                    coolant->state = MALFUNCTION;
                }
                break;
            case IDLE:
                /* Sleep until ignition_switch turned ON */
                if (get_ignition_switch_state() == COOLANT_OK) {
                    coolant->state = ACTIVE;
                } else if (get_ignition_switch_state() == COOLANT_MALFUNCTION) {
                    coolant->state = MALFUNCTION;
                }
                break;
            case ACTIVE:
                /* Turn off pump and fan and go sleep if ignition_switch didn't return OK */
                if (get_ignition_switch_state() != COOLANT_OK) {
                    turn_off_components();
                    if (get_ignition_switch_state() == COOLANT_OFF) {
                        coolant->state = IDLE;
                    } else if (get_ignition_switch_state() == COOLANT_MALFUNCTION) {
                        coolant->state = MALFUNCTION;
                    }
                } else {
                    coolant_logic_proceed(coolant);
                    // canopen_receive();
                    // canopen_transmit();
                }
                break;
            case MALFUNCTION:
                break;
            case ERROR_SHUTDOWN:
                break;
            default:
                break;
        }
        sleep(1);
    }
}

int main(int argc, void **argv) {
    coolant_t coolant = {0};

    if (args_validation(argc, argv) == 0) {
        main_loop(&coolant, argv[1]);
    }

    return COOLANT_VALIDATION_ERROR;
}
