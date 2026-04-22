/*
 * state_machine.c
 *
 *  Created on: Apr 22, 2026
 *      Author: akaal
 */


#include "state_machine.h"

void state_machine(void)
{

	static state_e state = INIT;
	static state_e previous_state = INIT;
	bool entry = (state!=previous_state)?true:false;	//ce booléen sera vrai seulement 1 fois après chaque changement d'état.
	previous_state = state;
	// Récupération des évènements
	//button_event_t button_event = BUTTON_state_machine();
	//printf("state: %d \n",  state);
	switch(state)
	{
		case INIT:
			button_handler_init();
			screen_manager_init();

			draw_glass();
			MPU6050_t MPU6050_Data;
			if (MPU6050_Init(&MPU6050_Data, GPIOA, GPIO_PIN_0, MPU6050_Device_0, MPU6050_Accelerometer_8G, MPU6050_Gyroscope_2000s) != MPU6050_Result_Ok) {
				// Affiche error avec l'UART
						printf("MPU6050 Error\n");
						// Boucle infinie
						while (1);
			}
			printf("Init\n");
			state = WAITING_STATE;
			break;
		case WAITING_STATE:
			break;
		case FILLING_STATE:
					break;
		case DRAINING_STATE:
					break;
        default:
        	break;
	}
}

