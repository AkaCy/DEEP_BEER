/*
 * screen_manager.c
 *
 *  Created on: Apr 1, 2026
 *      Author: akaal
 */

#include "screen_manager.h"

void screen_manager_init(){
	ILI9341_Init();
}

void draw_glass(){
	// draw glass
	ILI9341_DrawLine(25,30,31,280,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(26,30,32,280,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(215,30,208,280,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(214,30,207,280,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(32,280,208,280,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(32,281,208,281,ILI9341_COLOR_GLASS);
}

