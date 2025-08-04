/***********************************************************************
* Filename: can_proceed.c
* File description: highlevel wrappers over CAN specific protocol.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 03 08 2025
***********************************************************************/

#include "../main.h"

void can_over_temperature_error_report(coolant_t *coolant __attribute__((unused)),
     int16_t temp __attribute__((unused)), uint8_t is_error_active __attribute__((unused))) {
#if CAN_OPEN
    uint32_t over_temperature_error = 0x3210;

    if (is_error_active) {
        CO_errorReport(coolant->CO->em, CO_EMC_TEMPERATURE, over_temperature_error, temp);
    } else {
        CO_errorReset(coolant->CO->em, CO_EMC_TEMPERATURE, over_temperature_error, temp);
    }
#else
    (void)coolant;
#endif
}

void can_malfunction_error_report(coolant_t *coolant __attribute__((unused)),
     uint8_t is_error_active __attribute__((unused))) {
#if CAN_OPEN
    uint32_t malfunction_error = 0x3110;
    uint32_t additional_data = 0;
    
    if (is_error_active) {
        if (coolant->err_bits.fan_malfunction) {
            additional_data = 1;
        } else if (coolant->err_bits.pump_malfunction) {
            additional_data = 2;
        } else if (coolant->err_bits.ignition_switch_malfunction) {
            additional_data = 3;
        }

        CO_errorReport(coolant->CO->em, CO_EMC_GENERIC, malfunction_error, additional_data);
    } else {
        CO_errorReset(coolant->CO->em, CO_EMC_GENERIC, malfunction_error, additional_data);
    }
#else
    (void)coolant;
#endif
}

void can_proceed(coolant_t *coolant __attribute__((unused))) {
#if CAN_OPEN
    /* Process EMCY (Emergency messages ), NMT, HeartBeat etc. */
    CO_process(coolant->CO, false, CYCLE_TAKT_NS / 1000, NULL);
    /* Receive Process Data Object */
    CO_process_RPDO(coolant->CO, false, CYCLE_TAKT_NS / 1000, NULL);
    /* Transmit Process Data Object */
    CO_process_TPDO(coolant->CO, false, CYCLE_TAKT_NS / 1000, NULL);
#endif
}
