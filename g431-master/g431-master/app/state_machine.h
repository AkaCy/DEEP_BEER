/*
 * state_machine.h
 *
 *  Created on: Apr 22, 2026
 *      Author: akaal
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdbool.h>
#include "screen_manager.h"
#include "MPU6050/stm32g4_mpu6050.h"
#include "button_handler.h"

typedef enum
	{
		INIT,
		WAITING_STATE,
		FILLING_STATE,
		DRAINING_STATE,
	} state_e;

void state_machine(void);
#endif /* STATE_MACHINE_H_ */
