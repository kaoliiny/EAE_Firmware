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
#include <time.h>
#include <unistd.h>

#include "drivers/drivers.h"
#include "main.h"
#include "CAN/can_proceed.h"
#include "coolant_controller.h"

static enum coolant_error_status_e args_validation(int argc, char **argv) {
    int8_t temperature_sp;

    if (argc == 2) {
        temperature_sp = atoi(argv[1]);
        if (temperature_sp >= TEMPERATURE_LOW_SETPOINT && temperature_sp <= TEMPERATURE_HIGH_SETPOINT) {
            return 0;
        }
    }

    /* + 1 needed to trim the last '/' from stringd to get file name from full path name. */
    printf("Usage: %s TEMPERATURE_SETPOINT\n", strrchr(argv[0], '/') + 1);
    printf("TEMPERATURE_SETPOINT is a reference temperature value in %d-%d Celsius degree range.\n",
        TEMPERATURE_LOW_SETPOINT, TEMPERATURE_HIGH_SETPOINT);

    return COOLANT_VALIDATION_ERROR;
}

static enum coolant_error_status_e main_loop(coolant_t *coolant, void *temperature_sp) {
    struct timespec request = {0, CYCLE_TAKT_NS};

    while (true) {
        switch(coolant->state) {
            case STARTUP:
                if (sys_init(coolant, temperature_sp) == COOLANT_OFF) {
                    coolant->state = IDLE;
                } else {
                    coolant->state = MALFUNCTION_ERROR_SHUTDOWN;
                }
                break;
            case IDLE:
                /* Sleep until ignition_switch turned ON */
                if (get_ignition_switch_state() == COOLANT_ON_OK) {
                    coolant->state = ACTIVE;
                } else if (get_ignition_switch_state() == COOLANT_MALFUNCTION) {
                    coolant->err_bits.ignition_switch_malfunction = true;
                    coolant->state = MALFUNCTION_ERROR_SHUTDOWN;
                }
                break;
            case ACTIVE:
                if (get_ignition_switch_state() == COOLANT_OFF) {
                    /* Turn off pump and fan and go sleep if ignition_switch turned OFF */
                    turn_off_components();
                    coolant->state = IDLE;
                } else if (get_ignition_switch_state() == COOLANT_MALFUNCTION) {
                    coolant->state = MALFUNCTION_ERROR_SHUTDOWN;
                } else {
                    coolant_logic_proceed(coolant);
                    can_proceed(coolant);
                }
                break;
            case MALFUNCTION_ERROR_SHUTDOWN:
                /* Turn off pump and fan and go sleep if any of the components is malfanctioned */
                can_malfunction_error_report(coolant, true);
                /* proceed malfunction report before shutdown */
                can_proceed(coolant);
                printf("MALFUNCTION_ERROR_SHUTDOWN\n");
                sys_shutdown();
                return COOLANT_MALFUNCTION;
            default:
                break;
        }
        /* 0.5s delay */
        nanosleep(&request, NULL);
    }
}

int main(int argc, char **argv) {
    coolant_t coolant = {0};
    int err_no = COOLANT_OFF;

    err_no = args_validation(argc, argv);
    if (err_no == 0) {
        err_no = main_loop(&coolant, argv[1]);
    }

    return err_no;
}
