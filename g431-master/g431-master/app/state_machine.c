/*
 * state_machine.c
 *
 *  Created on: Apr 22, 2026
 *      Author: akaal
 */


#include "config.h"
#include "state_machine.h"
#include "stm32g4xx.h"
#include "stm32g4_gpio.h"
static int32_t gyro_x = 0;
static int32_t gyro_y = 0;
static int32_t gyro_z = 0;

const int16_t reset_threshold = 1000;
const int8_t delay_beer = 20; //40


void state_machine(void)
{
	static state_e state = INIT;
	static state_e previous_state = INIT;
	static MPU6050_t MPU6050_Data;
	bool entry = (state!=previous_state)?true:false;	//ce booléen sera vrai seulement 1 fois après chaque changement d'état.
	previous_state = state;
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
			MPU6050_ReadAll(&MPU6050_Data);
			gyro_z +=MPU6050_Data.Gyroscope_Z;
			if(get_button_center_value()){
				if(beer_fill_level < MAX_BEER_FILL_VALUE){
					state = FILLING_STATE;
				}
			} else if( gyro_z > reset_threshold) {
				state = DRAINING_STATE;
			}
			break;
		case FILLING_STATE:
			fill_beer();
			HAL_Delay(delay_beer);
			//HAL_Delay(40);
			state = WAITING_STATE;
			break;
		case DRAINING_STATE:
		{
			if(entry){
				printf("Draining\n");
			}
			do{
				MPU6050_ReadAll(&MPU6050_Data);
				gyro_z +=MPU6050_Data.Gyroscope_Z;
				drain_beer();
				HAL_Delay(delay_beer);
			} while(abs(gyro_z) > reset_threshold && beer_fill_level>9);
			printf("End Draining\n");
			state = WAITING_STATE;

			/* Affiche avec l'UART
			 printf("GX%4d\tGY%4d\tGZ%4d\tgx%4ld\tgy%4ld\tgz%4ld\t\n",
							(int16_t)MPU6050_Data.Gyroscope_X,
							(int16_t)MPU6050_Data.Gyroscope_Y,
							(int16_t)MPU6050_Data.Gyroscope_Z,
							(int32_t)gyro_x/16400,						//environ en °
							(int32_t)gyro_y/16400,						//environ en °
							(int32_t)gyro_z/16400);					//environ en °
			 HAL_Delay(120);

			 if (abs_gz >= tilt_drain_threshold && abs_gz < reset_threshold){
			 	drain_amount = (int)((abs_gz - tilt_drain_threshold) / drain_step_divisor) + 1;
			 	set_beer_fill_level(beer_fill_level - drain_amount);
			 }

			 if (abs_gz >= reset_threshold){
				 state = WAITING_STATE;
			 	 reset_beer();
			 }*/

			break;
		}
        default:
        	break;
	}
}

