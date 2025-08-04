/***********************************************************************
* Filename: drv_can_open.c
* File description: 
* Project: EAE_Firmware
* Author: Kateryna Oliinyk
* Created Date: 03 08 2025
***********************************************************************/

/* TODO: Later these files will be included on compilation whenever we need them and
* ifs will be removed.
*/
#if CAN_OPEN

/*This include is only example how it could interact with CANopenNode lib */
#include "301/CO_driver.h"

void CO_CANmodule_disable(CO_CANmodule_t* CANmodule) {
    if (CANmodule != NULL) {
        /* turn off the module */
    }
}

CO_ReturnError_t CO_CANrxBufferInit(CO_CANmodule_t* CANmodule, uint16_t index, uint16_t ident, uint16_t mask, bool_t rtr,
    void* object, void (*CANrx_callback)(void* object, void* message)) {

    }

#endif