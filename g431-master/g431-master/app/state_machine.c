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
	static MPU6050_t MPU6050_Data;
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
			//initialisation de l'accéléromètre
			if (MPU6050_Init(&MPU6050_Data, GPIOA, GPIO_PIN_1, MPU6050_Device_0, MPU6050_Accelerometer_8G, MPU6050_Gyroscope_2000s) != MPU6050_Result_Ok) {
				// Affiche error avec l'UART
				printf("MPU6050 Error\n");
				// Boucle infinie
				while (1);
			}
			printf("Init\n");
			state = WAITING_STATE;
			break;
		case WAITING_STATE:
			if(get_button_center_value()){
				if(beer_fill_level <= MAX_BEER_FILL_VALUE){
					state = FILLING_STATE;
				} else {
					state = DRAINING_STATE;
				}
			}
			break;
		case FILLING_STATE:
			fill_beer();
			HAL_Delay(20);
			//HAL_Delay(40);
			state = WAITING_STATE;
			break;
		case DRAINING_STATE:
			reset_beer();
			printf("Draining\n");
			HAL_Delay(4000);
			state = WAITING_STATE;
			break;
        default:
        	break;
	}
}

