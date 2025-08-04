/***********************************************************************
* Filename: sys_init.c
* File description: This file is corresponding for all system's componnents
* initialization and deinitialization.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include <stdlib.h>
#include <stdbool.h>

#include "drivers/drivers.h"
#include "sys_init.h"

/* Example CAN init function */
static void can_init(void) {
#if CAN_OPEN
    int8_t err;

    coolant->CO = CO_new(NULL, NULL);
    err = CO_CANopenInit(coolant->CO,          /* CANopen object */
                         NULL,                 /* alternate NMT */
                         NULL,                 /* alternate em */
                         OD,                   /* Object dictionary */
                         OD_STATUS_BITS,       /* Optional OD_statusBits */
                         NMT_CONTROL,          /* CO_NMT_control_t */
                         FIRST_HB_TIME,        /* firstHBTime_ms */
                         SDO_SRV_TIMEOUT_TIME, /* SDOserverTimeoutTime_ms */
                         SDO_CLI_TIMEOUT_TIME, /* SDOclientTimeoutTime_ms */
                         SDO_CLI_BLOCK,        /* SDOclientBlockTransfer */
                         activeNodeId, 0);
    if (!err) {
        CO_CANopenInitPDO(coolant->CO, Ccoolant->CO->em, OD, activeNodeId, 0);
    }
#endif
}

static void setpoints_init(coolant_t *coolant, void *temperature_sp) {
    coolant->temperature_setpoint = atoi(temperature_sp);
}

void turn_off_components(void) {
    drv_fan_turn_off();
    drv_pump_turn_off();
}

void sys_deinit(void) {
    /* drivers deinit. Currently no drivers so nothing to deitit. All dummy */
    /* CAN bus deinit */
}

void sys_shutdown(void) {
    turn_off_components();
    sys_deinit();
}

enum coolant_error_status_e sys_init(coolant_t *coolant, void *temperature_sp) {
    /* drivers init. Currently no drivers no init. All dummy */
    if (drv_pump_init() == PUMP_MALFUNCTION) {
        coolant->err_bits.pump_malfunction = true;
        return COOLANT_MALFUNCTION;
    }
    if (drv_fan_init() == FAN_MALFUNCTION) {
        coolant->err_bits.fan_malfunction = true;
        return COOLANT_MALFUNCTION;
    }
    /* setpoints_init */
    setpoints_init(coolant, temperature_sp);
    /* CAN bus init */
    can_init();

    return COOLANT_OFF;
}
