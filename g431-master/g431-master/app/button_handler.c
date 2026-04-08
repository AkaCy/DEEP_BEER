/*
 * button_handler.c
 *
 *  Created on: Apr 1, 2026
 *      Author: akaal
 */
#include "button_handler.h"

static volatile bool button_event = false;

bool get_button_center_value(void){
	return button_event;
}
void set_button_center_value(bool new_value){
	button_event = new_value;
}

void button_handler_init(void){
	// Bouton en entrée pull-up (PAS en IT ici, on poll via SysTick)
	BSP_GPIO_pin_config(GPIOB, GPIO_PIN_4, GPIO_MODE_INPUT, GPIO_PULLUP, GPIO_SPEED_FREQ_HIGH, GPIO_NO_AF);

	// Enregistrer UNE SEULE FOIS le callback périodique

	BSP_systick_add_callback_function(&process_button);
}

/* Appelée périodiquement par SysTick (ex: toutes les 1 ms) */
void process_button(void)
{
    uint8_t cur_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);

		// Pull-up: appui = 0, repos = 1
		button_event = (cur_state == 0);
}
