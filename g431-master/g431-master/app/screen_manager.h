/*
 * screen_manager.h
 *
 *  Created on: Apr 1, 2026
 *      Author: akaal
 */

#ifndef SCREEN_MANAGER_H_
#define SCREEN_MANAGER_H_

#include "tft_ili9341/stm32g4_ili9341.h"
#include <stdbool.h>

#define MAX_BEER_FILL_VALUE 245
#define BOTTOM_BEER_X0 33
#define BOTTOM_BEER_Y 279
#define TOP_BEER_Y 30
#define BOTTOM_BEER_X1 209

extern int beer_fill_level;
extern void reset_beer(void);

void screen_manager_init(void);
void draw_glass(void);
void fill_beer(void);
void drain_beer(void);
void empty_beer(void);

void check_x_values(bool fill);

#endif /* SCREEN_MANAGER_H_ */
