/*
Author: Jacky & Ochihai
Date: Oct 25, 2024

Purpose: 
		    - Provides various routines to: 
                    - Plot bitmaps of size 8, 16, 32
                    - Plot horizontal lines
                    - Clear horizontal lines & clear screen

*/
#ifndef RASTER_H
#define RASTER_H
#include "types.h"

void plot_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void plot_bitmap_16(UINT16 *base, int x, int y, const UINT16 *bitmap, unsigned int height);
void plot_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
void plot_horizontal_line(UINT8 *base, int y);
void clear_screen(UINT8 *base);
void clear_horizontal_line_8(UINT8* base, int x, int y, int length);
void clear_bitmap_8(UINT16 *base, int x, int y, const UINT8 *bitmap, unsigned int height);
void clear_bitmap_32(UINT32 *base, int x, int y, const UINT32 *bitmap, int height);
UINT8 *get_video_base();
void set_video_base(UINT8 *);
void enter_super();
void exit_super(); 

#endif
