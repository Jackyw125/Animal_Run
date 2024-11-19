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
#include <osbind.h>

void input(Model *model, char *pressedKey);
void process_synchronous_events(Model *model, bool *endGame, int seed);
UINT32 get_time();

int main() {
    UINT8 *page1 = Physbase();
    int seed;

    bool endGame = false;

    UINT32 timeThen, timeNow, timeElapsed;

    Model modelOne;
    Model *modelPtr = &modelOne;
    

    char pressedKey = 0;

    seed = Random();

    initialize_model(modelPtr);

    clear_screen(page1);
    render(modelPtr, (UINT32*)page1);

    /* preparing models for main game loop */
    timeThen = get_time();

    while (pressedKey != 'q' && !endGame) {
    timeNow = get_time();
    timeElapsed = timeNow - timeThen;

    if (timeElapsed > 0) {
        Vsync();

        input(modelPtr, &pressedKey);
        animal_vertical_movement(modelPtr);

        process_synchronous_events(modelPtr, &endGame, seed);

        render(modelPtr, (UINT32 *)page1);
        update_score(modelPtr);
        seed = seed * 3;
        Vsync();
    }

    timeThen = get_time();
}
    clear_screen(page1);
    Vsync();
    return 0;
}

/***********************************************************************
* Name: input
*
* Purpose: Handles user input for the game.
*
* Details: Checks if keyboard input is available and reads the key.
*          If the pressed key is ' ' or 'q', it updates the
*          pressedKey variable accordingly.
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
        if (key == ' ' || key == 'q') {
            *pressedKey = key;
        }
    } 
    else {
        *pressedKey = 0; /* Reset pressedKey if no key is pressed */
    }

    animal_input(&(model->chicken), *pressedKey);
}

/***********************************************************************
* Name: process_synchronous_events
*
* Purpose: Processes synchronous events for the game.
*
* Details: Calls functions to handle animal movement, and animal death checking.
*
* Parameters:
*     - model: Pointer to the game model.
*     - endGame: Pointer to a boolean indicating game end.
*     - seed: Random seed for event generation.
***********************************************************************/
void process_synchronous_events(Model *model, bool *endGame, int seed)
{
    animal_horizontal_movement((model));
    check_animal_death(model, endGame);
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
