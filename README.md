## EAE_Firmware
This project is my implementation for EAE Combined Challenge.
It emulates behaviour of coolant system for DC/AC and DC/DC.

System has 4 main components: temperature sensor, ignition switch, pump and fan.
The coolant receives input from the temperature sensor and ignition switch to control the pump and fan.
It also simulates CANbus communication EMCY messages reporting.

I highly recommend visiting `srcs/drivers/drv_temperature_sensor.c` and `coolant_controller.c` files to understand the way fake memperatures
are generated and PID controller logic BEFORE launching application.

## Prerequisites

Assumes Linux environment.

### Tools
    - gcc
    - cmake

## Build instructions
Build all:
`./build.sh all` or `./build.sh`

Build app:
`./build.sh app`

Build tests:
`./build.sh tests`

## Run instructions
Run app:
`./run.sh app TEMP_SETPOINT` or `./build/srcs/EAE_Firmware TEMP_SETPOINT`

TEMPERATURE_SETPOINT is a reference temperature value in 20-92 Celsius degree range.

Run tests:
`./run.sh tests`
