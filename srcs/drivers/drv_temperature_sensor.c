/***********************************************************************
* Filename: drv_temperature_sensor.c
* File description: this file simulates temperature sensor drivers and
* temperature measurments for DC/AC and DC/DC.
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#include <stdint.h>
#include "drv_temperature_sensor.h"

/* Dummy data to emulate temperature sensor measurments in Celcius */
static uint8_t fake_temperature_measurments[TEMPERATURE_ARRAY_SIZE] = {
    /* 20–35C warm-up (each value repeated twice) */
    20, 20, 21, 21, 22, 22, 23, 23, 24, 24,
    25, 25, 26, 26, 27, 27, 28, 28, 29, 29,
    30, 30, 31, 31, 32, 32, 33, 33, 34, 34,
    35, 35,
    /* 36–59C Normal work state (step 1) */
    36, 37, 38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
    56, 57, 58, 59,
    /* 60–80C Add some heat (step 2) */
    60, 62, 64, 66, 68, 70, 72, 74, 76, 78, 80
};

int8_t drv_temperature_sensor_get_temperature(void) {
    static int8_t i = -1;
    
    i++;
    if (i == TEMPERATURE_ARRAY_SIZE) {
        i = 0;
    }
    return fake_temperature_measurments[i];
}

void drv_temperature_sensor_init(void) {
    /* Some driver's init logic */
}
