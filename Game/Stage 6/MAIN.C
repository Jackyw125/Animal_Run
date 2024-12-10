/*
Author: Jacky & Ochihai
Date: Nov 18, 2024

Purpose:
    - Implements a double-buffered game engine.
    - Handles game model initialization, user input processing, model synchronization, event processing, and rendering.
    - Ensures smooth gameplay through efficient time and buffer management.
*/
#include "MODEL.H"
#include "RENDER.H"
#include "EVENTS.H"
#include "RASTER.H"
#include "INPUT.H"
#include <osbind.h>
#include <stdio.h>

UINT8 double_buffer[35840] = {0};

UINT32 get_time();
void main_game_loop();
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
void swap_buffer(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer);

int main() {
    UINT8 *page1 = Physbase();

    main_game_loop();

    return 0;
}

void main_game_loop()
{
    UINT32 *back_buffer, *front_buffer, *current_buffer;

    bool endGame = false;

    UINT32 time_then, time_now, time_elapsed;

    Model model;
    char pressedKey = 0;

    initialize_model(&model);
    render(&model, (UINT32*)current_buffer);

    /* prepering models for main game loop*/

    time_then = get_time();
    set_buffers(&back_buffer, &front_buffer, double_buffer);
    clear_screen((UINT8 *)front_buffer);
    clear_screen((UINT8 *)back_buffer);

    current_buffer = back_buffer;
    while (pressedKey != 'q' && !endGame) { /* Main game loop */
            input(&model, &pressedKey);
            if(pressedKey == ' ' || 'w' || 'W')
            {
                process_asynchronous_events(&model,&pressedKey);
            }
            time_now = get_time();
	        time_elapsed = time_now - time_then;

            if (time_elapsed > 0) {
                process_synchronous_events(&model,&endGame);
                render(&model, current_buffer);
                Setscreen(-1, current_buffer, -1);
                Vsync();
                swap_buffer(&current_buffer, front_buffer, back_buffer);
            }
    }
    Setscreen(-1, front_buffer, -1);
    clear_screen((UINT8 *)front_buffer);
}

/***********************************************************************
* Function: set_buffers
*
* Purpose:
*     Configures the back and front buffers for double buffering.
*
* Description:
*     - Aligns the back buffer's starting address to the next 256-byte 
*       boundary for compatibility.
*     - Assigns the front buffer to the current video base address.
*
* Parameters:
*     - back_buffer: Pointer to store the aligned back buffer address.
*     - front_buffer: Pointer to store the front buffer address.
*     - back_buffer_array: Preallocated memory array for the back buffer.
***********************************************************************/
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]) {

    UINT8 *temp = back_buffer_array;

    while( ((UINT32) temp) & 0xFF) {
        temp++;
    }

    *back_buffer =	(UINT32*) temp;
    *front_buffer =  Physbase();
}

/***********************************************************************
* Function: swap_buffer
*
* Purpose:
*     Switches between front and back buffers for smooth double buffering.
*
* Description:
*     - Updates the current buffer pointer to alternate between the 
*       back and front buffers, ensuring smooth visual updates.
*
* Parameters:
*     - current_buffer: Pointer to the current buffer in use.
*     - front_buffer: Pointer to the front buffer.
*     - back_buffer: Pointer to the back buffer.
***********************************************************************/
void swap_buffer(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer) {

    if(*current_buffer == front_buffer) {
        *current_buffer = back_buffer;
    } else {
        *current_buffer = front_buffer;
    }
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