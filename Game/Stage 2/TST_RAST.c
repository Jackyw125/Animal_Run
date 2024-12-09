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
void pause();

int main()
{
    UINT32 *base  = Physbase();
	const UINT8* glyph_A = GLYPH_START('A');
	const UINT8* glyph_0 = GLYPH_START('0'); 

    clear_screen((UINT8*)base);

    /*
    Test Case: test_plot_horizontal_line
    Purpose:
        Verifies the functionality of plotting horizontal lines across the screen.
        Uses the plot_horizontal_line function to ensure that lines are drawn at regular intervals.
        After plotting, it clears the screen to test the clear_screen functionality.
	*/
	test_plot_horizontal_line((UINT8*)base);
	pause();

	/*
    Test Case: test_plot_bitmap_8
    Purpose:
        Tests the ability to plot an 8x8 bitmap (glyph_A) in a grid pattern across the screen.
        Ensures consistent plotting of small bitmaps at regular intervals.
	*/
	test_plot_bitmap_8((UINT16*)base, glyph_A, FONT_HEIGHT);
	pause();

	/*
    Test Case: test_plot_bitmap_16
    Purpose:
        Validates the plotting of a 16x16 bitmap (coin_bitmap) in a grid pattern across the screen.
        Ensures correct placement and alignment of medium-sized bitmaps.
	*/
	test_plot_bitmap_16((UINT16 *)base, coin_bitmap, COIN_HEIGHT);
	pause();

	/*
    Test Case: test_plot_bitmap_32
    Purpose:
        Assesses the functionality of plotting a 32x32 bitmap (chicken_bitmap) in a grid pattern.
        Ensures that larger bitmaps are plotted at regular intervals, both horizontally and vertically.
	*/
	test_plot_bitmap_32(base, chicken_bitmap, CHICKEN_HEIGHT);
	pause();

	/*
    Test Case: plot_bitmap_32 at (192, 178)
    Purpose:
        Validates the capability to plot a single 32x32 bitmap (chicken_bitmap) at specific coordinates.
        Ensures precision in bitmap placement for arbitrary screen locations.
	*/
	plot_bitmap_32(base, 192, 178, chicken_bitmap, CHICKEN_HEIGHT);
	pause();

	/*
    Test Case: plot_bitmap_32 at (292, 278)
    Purpose:
        Checks the plotting of a different 32x32 bitmap (monster_bitmap) at specific coordinates.
        Validates that the system can handle varied bitmap data and placement.
	*/
	plot_bitmap_32(base, 292, 278, monster_bitmap, MONSTER_HEIGHT);
	pause();

	/*	
    Test Case: plot_bitmap_16 at (100, 100)
    Purpose:
        Ensures accurate plotting of a single 16x16 bitmap (coin_bitmap) at specified coordinates.
        Verifies placement of medium-sized graphics.
	*/
	plot_bitmap_16((UINT16 *)base, 100, 100, coin_bitmap, COIN_HEIGHT);
	pause();

	/*
    Test Case: plot_bitmap_8 at (15, 12)
    Purpose:
        Validates the plotting of an 8x8 bitmap (glyph_0) at specific coordinates.
        Commonly used for small graphics like glyphs or icons, ensuring precise placement.
	*/
	plot_bitmap_8((UINT16*)base, 15, 12, glyph_0, FONT_HEIGHT);

	return 0;
}

/***********************************************************************
Function Name: pause

Purpose:
    Pause program execution until the user provides input.
***********************************************************************/

void pause() {
    while (!Cconis()) {
    }
     Cnecin(); 

}

/***********************************************************************
Function Name: test_plot_horizontal_line

Purpose:
		- Uses the plot_horizontal_line function from RASTER.C to 
		  fill the screen with horizontal lines, 
		  after all lines are plotted the screen is cleared

Input:
		- A pointer to frame buffer called "base"

Output:
		- Plots 50 lines to the screen, the screen is then cleared
***********************************************************************/
void test_plot_horizontal_line(UINT8 *base)
{
	int i;
	int j;

	for(j = 0; j < SCREEN_HEIGHT; j+=8)
		plot_horizontal_line(base, j);

	pause();
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

	pause();
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

	pause();
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
	pause();
	clear_screen((UINT8*)base);
}
