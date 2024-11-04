/*
Author: Jacky & Ochihai
Date: Oct 25, 2024

Purpose: 
				- Test Driver to displays various bitmaps to the ATARI 68000 screen

Function Details: 
				- Each function will clear the screen after plotting the given bitmap
				- test_plot_bitmap_8 and test_plot_bitmap_16 will plot the given bit map equally across the entire screen
				- test_plot_bitmap_32 will plot the bitmap horizontally across the screen, each plot will be cleared
*/

#include <osbind.h>
#include <stdio.h>
#include "raster.h"
#include "bitmap.h"
#include "font.h"


void test_plot_horizontal_line(UINT8 *base);
void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height);
void test_plot_bitmap_16(UINT16 *base, const UINT16 *bitmap, const unsigned int height);
void test_plot_bitmap_32(UINT32 *base, const UINT32 *bitmap, const unsigned int height);

int main()
{
    UINT32 *base  = Physbase();
	const UINT8* glyph_A = GLYPH_START('A');
	const UINT8* glyph_0 = GLYPH_START('0'); 

    clear_screen((UINT8*)base);

	test_plot_horizontal_line((UINT8*)base);
    test_plot_bitmap_8((UINT16*)base, glyph_A, FONT_HEIGHT);
	test_plot_bitmap_16(base, coin_bitmap, COIN_HEIGHT);
    test_plot_bitmap_32(base, chicken_bitmap, CHICKEN_HEIGHT);
    plot_bitmap_32(base, 192, 178, chicken_bitmap, CHICKEN_HEIGHT);
	plot_bitmap_32(base, 292, 278, monster_bitmap, MONSTER_HEIGHT);
	plot_bitmap_16(base, 100, 100, coin_bitmap, COIN_HEIGHT);
	plot_bitmap_8((UINT16*)base, 15, 12, glyph_0, FONT_HEIGHT);

	return 0;
}


/*
Function Name: test_plot_horizontal_line

Purpose:
		- Uses the plot_horizontal_line function from RASTER.C to fill the screen with horizontal lines,
		  after all lines are plotted the screen is cleared

Input:
		- A pointer to frame buffer called "base"

Output:
		- Plots 50 lines to the screen, the screen is then cleared
*/
void test_plot_horizontal_line(UINT8 *base)
{
	int i;
	int j;

	for(j = 0; j < SCREEN_HEIGHT; j+=8)
		plot_horizontal_line(base, j);

	clear_screen(base);

}

/***********************************************************************
Function Name: test_plot_bitmap_8

Purpose: Test the plotting of a bitmap across the screen by repeatedly
         placing the bitmap in a grid pattern.

Input:
    - base: Pointer to the start of the frame buffer.
    - bitmap: Pointer to the bitmap array to plot.
    - height: Height of the bitmap.

Output:
    - The bitmap is plotted at regular intervals across the screen in a
      8x8 grid pattern, covering the entire screen area.
***********************************************************************/
void test_plot_bitmap_8(UINT16 *base, const UINT8 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=8)
		for(j = 0; j < SCREEN_HEIGHT; j+=8)
			plot_bitmap_8(base, i, j, bitmap, height);

	clear_screen((UINT8*)base);

}

/***********************************************************************
Function Name: test_plot_bitmap_16

Purpose: Test the plotting of a bitmap across the screen by repeatedly
         placing the bitmap in a grid pattern.

Input:
    - base: Pointer to the start of the frame buffer.
    - bitmap: Pointer to the bitmap array to plot.
    - height: Height of the bitmap.

Output:
    - The bitmap is plotted at regular intervals across the screen in a
      16x16 grid pattern, covering the entire screen area.
***********************************************************************/

void test_plot_bitmap_16(UINT16 *base, const UINT16 *bitmap, const unsigned int height)
{
	int i;
	int j;

	for(i = 0; i < SCREEN_WIDTH; i+=16)
		for(j = 0; j < SCREEN_HEIGHT; j+=16)
			plot_bitmap_16(base, i, j, bitmap, height);


	clear_screen((UINT8*)base);
}

/***********************************************************************
Function Name: test_plot_bitmap_32

Purpose: Test the plotting of a bitmap across the screen by repeatedly
         placing the bitmap in a grid pattern.

Input:
    - base: Pointer to the start of the frame buffer.
    - bitmap: Pointer to the bitmap array to plot.
    - height: Height of the bitmap.

Output:
    - The bitmap is plotted at regular intervals across the screen in a
      32x32 grid pattern, covering the entire screen area.
***********************************************************************/
void test_plot_bitmap_32(UINT32 *base, const UINT32 *bitmap, const unsigned int height)
{	
    int i=0;
	int j=0;

	for(i = 0; i < SCREEN_WIDTH; i+=64)
		for(j = 0; j < SCREEN_HEIGHT+64; j+=64)
			plot_bitmap_32(base, i, j, bitmap, height);
	
	clear_screen((UINT8*)base);
}
