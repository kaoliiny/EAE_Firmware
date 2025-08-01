/***********************************************************************
* Filename: drv_temperature_sensor.h
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 30 07 2025
***********************************************************************/

#ifndef _DRV_TEMPERATURE_SENSOR_H_
#define _DRV_TEMPERATURE_SENSOR_H_

#define TEMPERATURE_ARRAY_SIZE 67

#define DRV_TEMPERATURE_SENSOR_ERROR -1

int8_t drv_temperature_sensor_get_temperature(void);

#endif
