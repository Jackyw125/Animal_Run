/*
Author: Jacky & Ochihai
Date: Nov 18, 2024

Purpose:
    - Implements a simplified game loop with single-buffered rendering.
    - Manages game model initialization, user input processing, event handling, and rendering.
    - Provides utility functions for timing and input handling.

Description:
    This file contains the main function and essential components of the game engine.
    The game runs in a loop, processing user inputs and synchronous events while updating
    the display with the latest game state.

Error:
    Jumping mechanic does not work.
*/

#include "MODEL.H"
#include "RENDER.H"
#include "EVENTS.H"
#include "RASTER.H"
#include "INPUT.H"
#include <osbind.h>
#include <stdio.h>

UINT32 get_time();

int main() {
    UINT8 *page1 = Physbase();
    bool endGame = false;
    UINT32 time_then, time_now, time_elapsed;
    Model model;
    char pressedKey = 0;

    initialize_model(&model);
    render(&model, (UINT32*)page1);

    clear_screen(page1);

    /* preparing models for main game loop */
    time_then = get_time();
        while (pressedKey != 'q' && !endGame) { /* Main game loop */
        Vsync();
            input(&model, &pressedKey);
            if(pressedKey == ' ' || 'w' || 'W')
            {
                process_asynchronous_events(&model, &pressedKey);
            }
            time_now = get_time();
	        time_elapsed = time_now - time_then;

            if (time_elapsed > 1) {
                process_synchronous_events(&model,&endGame);
                render(&model, (UINT32 *)page1);
            }
        Vsync();
    }
    clear_screen(page1);
    return 0;
}

/***********************************************************************
* Name: get_time
*
* Purpose: Retrieves the current system time in milliseconds.
*
* Details: Gets the system time value stored at memory address 0x462,
*
* Returns:
*     - UINT32: The current system time in milliseconds.
***********************************************************************/
UINT32 get_time() {
    UINT32 time;
    long old_ssp = Super(0); 
    time = *((UINT32 *)0x462);
    Super(old_ssp); 
    return time;
}
