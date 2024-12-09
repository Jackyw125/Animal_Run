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
#include "VBL.H"
#include "GLOBAL.H"
#include "VEC_IN.H"
#include <osbind.h>
#include <stdio.h>

UINT8 double_buffer[35840] = {0};
Model model = {0};
bool endGame = false;
UINT32 get_time();
void main_game_loop();
void input(Model *model, char *pressedKey);
void set_buffers(UINT32** back_buffer, UINT32** front_buffer, UINT8 back_buffer_array[]);
void switch_buffers(UINT32** current_buffer, UINT32* front_buffer, UINT32 * back_buffer);

int main() {
    UINT8 *current_buffer = (UINT8 *)get_video_base();
    char pressed_key;
    bool quit = false;
    Model model;

    clear_screen((UINT8 *)current_buffer);

    render_main_menu((UINT32 *)current_buffer);

    while(quit == false) {
        if (pressed_key == ' ') {
            main_game_loop();
            render_main_menu((UINT32 *)current_buffer);
        } else if (pressed_key == 'q') { 
            quit = true;
            }
        input(&model, &pressed_key); 
    }

    return 0;
}

/***********************************************************************
* Name: main_game_loop
*
* Purpose:
*     Runs the main game loop, managing game updates and rendering.
*
* Details:
*     - Initializes game model and sets up buffers for double buffering.
*     - Handles user input and asynchronous events.
*     - Renders the game state and switches between buffers for smooth 
*       frame transitions.
*     - Ends the game loop when 'q' is pressed or when the `endGame` 
*       flag is set.
*
* Parameters:
*     - None
***********************************************************************/
void main_game_loop()
{   
    UINT32 *back_buffer, *front_buffer, *current_buffer;

    char pressedKey = 0;
    Vector orig_vbl_vector;
    endGame = false;

    initialize_model(&model);
    render(&model, current_buffer);

    /* prepering models for main game loop*/

    set_buffers(&back_buffer, &front_buffer, double_buffer);
    clear_screen((UINT8 *)front_buffer);
    clear_screen((UINT8 *)back_buffer);

    current_buffer = back_buffer;
    orig_vbl_vector = install_vector(VBL_VECTOR_NUM, main_vbl_isr);

    while (pressedKey != 'q' && !endGame) { /* Main game loop */
            input(&model, &pressedKey);
            if(pressedKey == ' ' || 'w' || 'W')
            {
                process_asynchronous_events(&model,&pressedKey);
            }

            if (render_request == 1) {
                render(&model, current_buffer);
                set_video_base(current_buffer);
                
                switch_buffers(&current_buffer, front_buffer, back_buffer);
                render_request = 0;
            }
    }
    install_vector(VBL_VECTOR_NUM, orig_vbl_vector);
    set_video_base(front_buffer);
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
        if (key == 'w' || key == 'q' || key == 'W' || key == ' ') {
            *pressedKey = key;
        }
    }
    else {
        *pressedKey = 0; 
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
    *front_buffer =  get_video_base();
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