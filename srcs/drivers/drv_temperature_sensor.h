/***********************************************************************
* Filename: drv_temperature_sensor.h
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _DRV_TEMPERATURE_SENSOR_H_
#define _DRV_TEMPERATURE_SENSOR_H_

#define TEMPERATURE_ARRAY_SIZE 43

/* Start point */
#define ROOM_TEMPERATURE 20

#define TEMPERATURE_LOW_POINT 32
#define TEMPERATURE_MAX_PREHEAT 50

#define DRV_TEMPERATURE_SENSOR_ERROR -255

int16_t drv_temperature_sensor_get_temperature(void);

/* Nothing to init yet */
void drv_temperature_sensor_init(void);

#endif
