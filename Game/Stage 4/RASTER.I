# 1 "raster.c" 1
# 1 "./raster.h" 1
# 1 "./types.h" 1
# 16 "./types.h"
typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef unsigned char bool;
# 15 "./raster.h" 2


void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_horizontal_line(UINT8 *base, int y);
void clear_screen(UINT8 *base);
void clear_horizontal_line_8(UINT8* base, int x, int y, int length);
void clear_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
# 1 "raster.c" 2


void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;

	if(y+height > 400 )
	{
		height = 400 -y-1;
	}

    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];
        loc += 40;
    }
}

void clear_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;

	if(y+height > 400 )
	{
		height = 400 -y-1;
	}

    for (row = 0; row < height; row++)
    {
        *loc &= bitmap[row];
        loc += 40;
    }
}

void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height)
{
    UINT16 *loc = base + (y * 40) + (x >> 4);
    int row;

	if(y+height > 400 )
	{
		height = 400 -y-1;
	}

    for (row = 0; row < height; row++)
    {
        *loc |= bitmap[row];
        loc += 40;
    }
}


void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height)
{
	int rows;
	int cols;

	UINT32 *loc = base + (y * 20) + (x>>5);

	if(y >= 400 )
		return;

	if(y+height > 400 )
	{
		height = 400 -y-1;
	}

	for (rows = 0; rows < height; rows++) {
		for(cols = 0; cols < 2; cols++) {
			*loc = *loc | *(bitmap)++;
			*loc = ~(*loc ^ 0xFFFFFFFF);
			loc++;
		}
		loc += 18;
	}
}

void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height)
{
	int rows;
	int cols;

	UINT32 *loc = base + (y * 20) + (x>>5);

	if(y >= 400 )
		return;

	if(y+height > 400 )
	{
		height = 400 -y-1;
	}

	for (rows = 0; rows < height; rows++) {
		for(cols = 0; cols < 2; cols++) {
			*loc |= *(bitmap)++;
			*loc ^= 0xFFFFFFFF;
			loc++;
		}
		loc += 18;
	}
}


void plot_horizontal_line(UINT8 *base, int y) {
	int row= 0;

	UINT8 *drawLine = base + (y*80);

	while(row++ < 80){
		*(drawLine++) = 0xFFFF;
	}
}



void clear_screen(UINT8 *base)
{
	int row;

	for (row = 0; row < 400 ; row++) {
		clear_horizontal_line_8(base, 0, 0, 640 );
		base += 80;
	}
}

void clear_horizontal_line_8(UINT8* base, int x, int y, int length) {
	int row;
	int counter = length >> 3;

	UINT8 *clearLine = base + (y * 80) + (x >> 3);

	for (row = 0; row < counter; row++){

		*(clearLine++) &= 0x00;
	}
}

void plot_bitmap_screen(UINT32 *base, UINT32* bitmap)
{
	int row;
	int counter = 8000;

	UINT32 *loc = base + (0 >> 5);

	for (row = 0; row < counter; row++)
	{
		*loc |= *(bitmap++);
		*(loc++) ^= 0xFFFFFFFF;
	}
}
