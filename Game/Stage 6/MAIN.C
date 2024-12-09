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
#include <osbind.h>
#include <stdio.h>

UINT8 double_buffer[35840] = {0};

UINT32 get_time();
void input(Model *model, char *pressedKey);
void main_game_loop();
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer);

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
                switch_buffers(&current_buffer, front_buffer, back_buffer);
            }
    }
    Setscreen(-1, front_buffer, -1);
    clear_screen((UINT8 *)front_buffer);
}

/***********************************************************************
* Name: input
*
* Purpose: Handles user input for the game.
*
* Details: 
*   - Captures input using `Cconis` and `Cnecin`.
*   - Updates the `pressedKey` if ' ', 'q', or other specified keys are pressed.
*   - Integrates user input into game mechanics via `animal_input`.

*
* Parameters:
*     - model: Pointer to the game model.
*     - pressedKey: Pointer to the variable storing the pressed key.
***********************************************************************/
void input(Model *model, char *pressedKey)
{
    if (Cconis()) /* Check if keyboard input is available */
    {
        char key = (char)Cnecin(); /* Read keyboard input */
        if (key == ' ' || key == 'q' || key == 'W' || key == 'w') {
            *pressedKey = key;
        }
    }
    else {
        *pressedKey = 0; /* Reset pressedKey if no key is pressed */
    }
}

/***********************************************************************
* Name: set_buffers
*
* Purpose:
*     Sets up the back and front buffers for double buffering.
*
* Details:
*     - Aligns the back buffer's starting address to the next 256-byte 
*       boundary.
*     - Assigns the front buffer to the current video base.

* Parameters:
*     - back_buffer: Double pointer to the back buffer.
*     - front_buffer: Double pointer to the front buffer.
*     - back_buffer_array: Array used to allocate memory for the back buffer.
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
* Name: switch_buffers
*
* Purpose:
*     Toggles between the front and back buffers for double buffering.
*
* Details:
*     - Sets the current buffer to the back buffer if it's currently the 
*       front buffer, and vice versa.
*
* Parameters:
*     - current_buffer: Double pointer to the current buffer.
*     - front_buffer: Pointer to the front buffer.
*     - back_buffer: Pointer to the back buffer.
***********************************************************************/
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer) {

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