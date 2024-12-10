#include "raster.h"

/***********************************************************************
Function Name: plot_bitmap_8

Purpose: Plot an 8-bit per pixel bitmap onto the frame buffer.

Input:
    	- base: Pointer to the start of the frame buffer.
        - x: X-coordinate 
        - y: Y-coordinate
        - bitmap: Pointer to the bitmap data.
        - height: Height of the bitmap.

Output:
        - The bitmap is drawn to the screen
***********************************************************************/
void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;
       
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return; 
    }

    if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}

    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];
        loc += 40;
    }
}

/***********************************************************************
Function Name: plot_bitmap_16

Purpose: Plot an 16-bit per pixel bitmap onto the frame buffer.

Input:
    	- base: Pointer to the start of the frame buffer.
        - x: X-coordinate to plot.
        - y: Y-coordinate to plot.
        - bitmap: Pointer to the bitmap data.
        - height: Height of the bitmap.

Output:
        - The bitmap is drawn to the screen
***********************************************************************/
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;    

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return; 
    }

    if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}

    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];     
        loc += 40;
    }
}

/***********************************************************************
Function Name: plot_bitmap_32

Purpose: Plot an 32-bit per pixel bitmap onto the frame buffer.

Input:
    	- base: Pointer to the start of the frame buffer.
        - x: X-coordinate to plot.
        - y: Y-coordinate to plot.
        - bitmap: Pointer to the bitmap data.
        - height: Height of the bitmap.

Output:
        - The bitmap is drawn to the screen
***********************************************************************/
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height)
{
	int rows;
	int cols;

	UINT32 *loc = base + (y * 20) + (x>>5);

    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
        return;
    }

    if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}

	for (rows = 0; rows < height; rows++) {
		for(cols = 0; cols < 2; cols++) {
			*loc = *loc | *(bitmap)++;
			*loc = ~(*loc ^ 0xFFFFFFFF); /*32 bits in hexadecimal*/
			loc++;
		}
		loc += 18;
	}
}

/***********************************************************************
Function Name: plot_horizontal_line

Purpose:
    Draw a horizontal line at the specified y-coordinate.

Details:
    - Fills a row of the screen buffer with the specified pattern.
    - Operates across the entire width of the buffer row.

Input:
    - base: Pointer to the start of the frame buffer.
    - y: Y-coordinate of the line to draw.

Output:
    - A horizontal line is drawn on the screen buffer.
***********************************************************************/
void plot_horizontal_line(UINT8 *base, int y) {
	int row= 0;

	UINT8 *drawLine = base + (y*80);

	while(row++ < 80){
		*(drawLine++) = 0xFF;
	} 
}

/***********************************************************************
Function Name: clear_horizontal_line_8

Purpose: Clear a horizontal line on the screen.

Input:
         - base: Pointer to the start of the frame buffer.
         - x: X-coordinate to clear.
         - y: Y-coordinate to clear.
         - length: Length of the line to clear.
Output:
        - All memory locations in a row of the frame buffer are set to 0, creating a clear line on the screen

***********************************************************************/

void clear_horizontal_line_8(UINT8* base, int x, int y, int length) {
	int row;
	int counter = length >> 3;

	UINT8 *clearLine = base + (y * 80) + (x >> 3);

	for (row = 0; row < counter; row++){

		*(clearLine++) &= 0x00;
	}
}

/***********************************************************************
Function Name: clear_bitmap_8

Purpose: Clear specific areas on the screen based on a provided bitmap.

Input:
    - base: Pointer to the start of the frame buffer.
    - x: X-coordinate to start clearing.
    - y: Y-coordinate to start clearing.
    - bitmap: Pointer to the bitmap array used for clearing specific bits.
    - height: Height of the bitmap.

Output:
    - Selected areas in a column of the frame buffer are masked with the
      bitmap, effectively clearing specific regions on the screen.

***********************************************************************/
void clear_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;
       
	if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}
	
    for (row = 0; row < height; row++)
    {
        *loc &= bitmap[row];
        loc += 40;
    }
}

/***********************************************************************
Function Name: clear_bitmap_32

Purpose: Clear specific areas on the screen based on a provided bitmap.

Input:
    - base: Pointer to the start of the frame buffer.
    - x: X-coordinate to start clearing.
    - y: Y-coordinate to start clearing.
    - bitmap: Pointer to the bitmap array used for clearing specific bits.
    - height: Height of the bitmap.

Output:
    - Selected areas in a column of the frame buffer are masked with the
      bitmap, effectively clearing specific regions on the screen.

***********************************************************************/
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height)
{
	int rows;
	int cols;

	UINT32 *loc = base + (y * 20) + (x>>5);

	if(y >= SCREEN_HEIGHT)
		return;

	if(y+height > SCREEN_HEIGHT)
	{
		height = SCREEN_HEIGHT-y-1;
	}
	
	for (rows = 0; rows < height; rows++) {
		for(cols = 0; cols < 2; cols++) {
			*loc |= *(bitmap)++;
			*loc ^= 0xFFFFFFFF; /*32 bits in hex*/
			loc++;
		}
		loc += 18;
	}
}

/***********************************************************************
Function Name: plot_bitmap_screen

Purpose:
    Render a full-screen bitmap onto the frame buffer.

Details:
    - Plots the bitmap data across the entire screen buffer.
    - Operates with a 32-bit per pixel depth.
    - Iterates over all pixels to render the bitmap.

Input:
    - base: Pointer to the start of the frame buffer.
    - bitmap: Pointer to the bitmap data.

Output:
    - The specified bitmap is rendered across the screen buffer.
***********************************************************************/
void plot_bitmap_screen(UINT32 *base, UINT32* bitmap)
{
	int row;
	int counter = 8000;

	UINT32 *loc = base + (0 >> 5);

	for (row = 0; row < counter; row++)
	{
		*loc |= *(bitmap++);
		*(loc++) ^= 0xFFFFFFFF; /*32 bits in hex*/
	}
}
