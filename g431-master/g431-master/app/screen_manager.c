/*
 * screen_manager.c
 *
 *  Created on: Apr 1, 2026
 *      Author: akaal
 */

#include "screen_manager.h"

static volatile int beer_fill_level = 0;

static volatile int beer_fill_x0 = BOTTOM_BEER_X0;
static volatile int beer_fill_x1 = BOTTOM_BEER_X1;

void check_x_values(void)
{
	// On transforme les intervalles en "paliers" pour rester compatible avec switch/case en C.
	switch (beer_fill_level)
	{
	case 20:
		beer_fill_x0--;
		break;
	case 25:
		beer_fill_x1++;
		break;
	case 62:
		beer_fill_x0--;
		break;
	case 67:
		beer_fill_x1++;
		break;
	case 104:
		beer_fill_x0--;
		break;
	case 125:
		beer_fill_x1++;
		break;
	case 175:
		beer_fill_x1++;
		break;
	case 180:
		beer_fill_x0--;
		break;
	case 144:
		beer_fill_x0--;
		break;
	case 225:
			beer_fill_x1++;
			break;
	case 228:
		beer_fill_x0--;
		break;
	case MAX_BEER_FILL_VALUE:
		beer_fill_x0 = BOTTOM_BEER_X0;
		beer_fill_x1 = BOTTOM_BEER_X1;
		beer_fill_level = 0;
		empty_beer();
		break;
	default:
		break;
	}
}

void empty_beer(){
	/* Fill with black color */
	ILI9341_Fill(ILI9341_COLOR_BLACK);
	draw_glass();
}

void screen_manager_init(){
	ILI9341_Init();
}

void draw_glass(){
	// draw glass
	ILI9341_DrawLine(25,TOP_BEER_Y,BOTTOM_BEER_X0-2,BOTTOM_BEER_Y+1,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(26,TOP_BEER_Y,BOTTOM_BEER_X0-1,BOTTOM_BEER_Y+1,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(216,TOP_BEER_Y,BOTTOM_BEER_X1+2,BOTTOM_BEER_Y+1,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(215,TOP_BEER_Y,BOTTOM_BEER_X1+1,BOTTOM_BEER_Y+1,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(BOTTOM_BEER_X0,BOTTOM_BEER_Y+1,BOTTOM_BEER_X1+1,BOTTOM_BEER_Y+1,ILI9341_COLOR_GLASS);
	ILI9341_DrawLine(BOTTOM_BEER_X0,BOTTOM_BEER_Y+2,BOTTOM_BEER_X1+1,BOTTOM_BEER_Y+2,ILI9341_COLOR_GLASS);
}

void fill_beer(){
	if (beer_fill_level <= MAX_BEER_FILL_VALUE){
		check_x_values();
		ILI9341_DrawLine(beer_fill_x0,BOTTOM_BEER_Y-beer_fill_level,beer_fill_x1,BOTTOM_BEER_Y-beer_fill_level,ILI9341_COLOR_BEER);
		beer_fill_level ++;
	}
}

