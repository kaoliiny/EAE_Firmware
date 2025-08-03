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
/* Shouldn't be at this level. Needed to predict temperature reaction to cooling */
#include "drivers.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Static dummy data to emulate temperature sensor measurments in Celsius
*       20–32C warm-up (each value repeated twice)
*    21, 21, 22, 22, 23, 23, 24, 24, 25
*    25, 26, 26, 27, 27, 28, 28, 29, 29,
*    30, 30, 31, 31, 32, 32,
*       33–50C Normal work state
*    33, 34, 35, 36, 37, 38, 39, 40, 41,
*    42, 43, 44, 45, 46, 47, 48, 49, 50
*/

/* This algorithm can be divided into two part: static and dynamic temperature measurments.
* Static - first stage. Simply returns data from predefined array to simulate system startup
* and preheat without reacting to coolant changes.
* Dynamic - Second stage. Imitates simple reaction to cooling.
 */
int16_t drv_temperature_sensor_get_temperature(void) {
    static int8_t i;
    static int16_t fake_temperature_measurment = ROOM_TEMPERATURE;
    int8_t heat_power_degrees = 2;
    int8_t cooling_power;
    int8_t rand_offset;

    if (i < TEMPERATURE_ARRAY_SIZE) {
        /* Static stage. Here we just iterate through predefined array */
        if (!(i % 2) && fake_temperature_measurment <= TEMPERATURE_LOW_POINT) {
            fake_temperature_measurment++;
        } else if (fake_temperature_measurment > TEMPERATURE_LOW_POINT && fake_temperature_measurment < TEMPERATURE_MAX_PREHEAT) {
            fake_temperature_measurment++;
        }
        i++;
    } else {
        /* Dynamic stage.
        * At this point we assume that the temperature naturally grows 2 degrees per main cycle takt
        * (per CYCLE_TAKT_NS).
        * formula to calculate cooling are:
        * ` cooling_power = (fan_power + pump_power)`
        * ` output_temp = current_temp + heat_power_degrees - cooling_power + rand_offset `
        */
        srand(time(NULL));
        rand_offset = (rand() % 4) - 1;
        cooling_power = (drv_fan_get_speed() + drv_pump_get_speed());
        fake_temperature_measurment = fake_temperature_measurment + heat_power_degrees - cooling_power + rand_offset;
    }

    return fake_temperature_measurment;
}

void drv_temperature_sensor_init(void) {
    /* Some driver's init logic */
}
