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
#include <osbind.h>
#include <stdio.h>

UINT8 double_buffer[448][80] = {0};

UINT32 get_time();
void input(Model *model, char *pressedKey);
void syncModel(Model *modelSrc, Model *modelDst);
void process_synchronous_events(Model *model, bool *endGame, UINT32 *base);
void process_asynchronous_events(Model *model, char *pressedKey);

int main() {
    UINT8 *page1 = get_video_base();
    UINT8 *page2 = &double_buffer[0][0];
    UINT8 confirmedInput;

    bool useDoubleBuffer = true;
    bool endGame = false;

    UINT32 time_then, time_now, time_elapsed;

    Model modelOne, modelTwo, modelThree;
    Model *modelPtr = &modelOne;
    Model *modelSnapshotOne = &modelTwo;
    Model *modelSnapshotTwo = &modelThree;
    char pressedKey = 0;
    bool respawned = false;

    initialize_model(modelPtr);
    initialize_model(modelSnapshotOne);
    initialize_model(modelSnapshotTwo);

    page2 = (UINT8*)((size_t)page2 | 0xff ) + 1; /* finding page aligned address for second page*/

    /* prepering models for main game loop*/
    syncModel(modelPtr, modelSnapshotOne);
    syncModel(modelPtr, modelSnapshotTwo);
    clear_screen(page1);
    clear_screen(page2);
    render(modelPtr, (UINT32*)page1);
    render(modelPtr, (UINT32*)page2);
    time_then = get_time();

    while (pressedKey != 'q' && !endGame) { /* Main game loop */
    Vsync();
        if (useDoubleBuffer) {
            input(modelPtr, &pressedKey);
            if(pressedKey == ' ' || 'w' || 'W')
            {
                process_asynchronous_events(modelPtr,&pressedKey);
            }
            time_now = get_time();
	        time_elapsed = time_now - time_then;
            if (time_elapsed > 0) {
                process_synchronous_events(modelPtr,&endGame,(UINT32*)page1);
                syncModel(modelPtr, modelSnapshotOne);
                double_buffer_render(modelSnapshotTwo, (UINT32*)page1);
                set_video_base(page1);
            }

            useDoubleBuffer = false;
        } else {
            input(modelPtr, &pressedKey);
            if(pressedKey == ' ' || 'w' || 'W')
            {
                process_asynchronous_events(modelPtr, &pressedKey);
            }
            time_now = get_time();
	        time_elapsed = time_now - time_then;            
            if (time_elapsed > 0) {
                process_synchronous_events(modelPtr,&endGame,(UINT32*)page2); 
                syncModel(modelPtr, modelSnapshotTwo);
                double_buffer_render(modelSnapshotOne, (UINT32*)page2); 
                set_video_base(page2);
            }   

            useDoubleBuffer = true;
        }
        Vsync();
        time_then = time_now; 
    }
    set_video_base(page1);
    clear_screen(page1);
    return 0;
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
* Name: syncModel
*
* Purpose: Synchronizes the content of two game models.
*
* Details: Copies data from the source model to the destination model,
*          ensuring consistency between the two models.
*
* Parameters:
*     - modelSrc: Pointer to the source game model.
*     - modelDst: Pointer to the destination game model.
***********************************************************************/
void syncModel(Model *modelSrc, Model *modelDst)
{
    UINT8 i;
    UINT8 j;
    Coin *srcCoin, *dstCoin;

    modelDst->chicken.x = modelSrc->chicken.x;
    modelDst->chicken.y = modelSrc->chicken.y;

    modelDst->chicken.velocity = modelSrc->chicken.velocity;
    modelDst->chicken.isFalling = modelSrc->chicken.isFalling;
    modelDst->chicken.velocity_y = modelSrc->chicken.velocity_y;
    modelDst->chicken.dead = modelSrc->chicken.dead;


    modelDst->score.total = modelSrc->score.total;
    modelDst->score.prev_total = modelSrc->score.prev_total;
    modelDst->score.digits = modelSrc->score.digits;
   

    srcCoin = (modelSrc->coins);
    dstCoin = (modelDst->coins);

    for(i=0; i < MAX_COINS;i++)
    {
        dstCoin->x = srcCoin->x;
        dstCoin->y = srcCoin->y;
        srcCoin++;
        dstCoin++;    
    }
}

/***********************************************************************
* Name: process_synchronous_events
*
* Purpose: Processes synchronous events for the game.
*
* Details: Calls functions to handle animal movement,and animal death checking.
*
* Parameters:
*     - model: Pointer to the game model.
*     - endGame: Pointer to a boolean indicating game end.
*     - seed: Random seed for event generation.
***********************************************************************/
void process_synchronous_events(Model *model, bool *endGame, UINT32 *base)
{
    check_animal_death(model, endGame);
    animal_horizontal_movement(&(model->chicken));
    animal_vertical_movement(&(model->chicken));
    respawn_render(model, base);
}

void process_asynchronous_events(Model *model, char *pressedKey)
{
    animal_input(&(model->chicken), *pressedKey);
    update_score(model);    
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