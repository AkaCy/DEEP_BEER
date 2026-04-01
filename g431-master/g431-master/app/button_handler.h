/*
 * button_handler.h
 *
 *  Created on: Apr 1, 2026
 *      Author: akaal
 */

#ifndef BUTTON_HANDLER_H_
#define BUTTON_HANDLER_H_

#include <stdbool.h>
#include "stm32g4_gpio.h"
#include "stm32g4_systick.h"

void button_handler_init(void);
void process_button(void);
bool get_button_center_value(void);
void set_button_center_value(bool new_value);


#endif /* BUTTON_HANDLER_H_ */
