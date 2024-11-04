#include "model.h"
#include <stdlib.h>  

/***********************************************************************
* Name: initialize_animal
*
* Purpose: Initializes the game model with default values.
*
* Details: Initializes the animal character.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
***********************************************************************/
void initialize_animal(Model *model)
{

    /* Initialize animal character at the bottom-left */
    model->chicken.x = 0;  
    model->chicken.y = SCREEN_HEIGHT - 64; 

    model->chicken.prev_x = -1;  
    model->chicken.prev_y = -1;
    
    model->chicken.velocity = 0;
    model->chicken.isFalling = true;
    model->chicken.max_y = model->chicken.y;
    model->chicken.dead = false;
}

/***********************************************************************
* Name: initialize_monster
*
* Purpose: Initializes the game model with default values.
*
* Details: Initializes the monsters.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
***********************************************************************/
void initialize_monster(Model *model)
{
    int i;
    /* Initialize monsters with random positions */
    for (i = 0; i < MAX_MONSTER; i++)
    {
    model->monster[i].x = rand() % SCREEN_WIDTH;   /* Random X position */
    model->monster[i].y = 0;                       /* Start at the top of the screen */
    model->monster[i].off_screen = false;          /* Monster is initially on-screen */
    }
}

/***********************************************************************
* Name: initialize_score
*
* Purpose: Initializes the game model with default values.
*
* Details: Initializes the coins.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
***********************************************************************/
void initialize_coins(Model *model)
{
    int j;
     /* Initialize coins with random positions */
    for (j = 0; j < MAX_COINS; j++)
    {
    model->coins[j].x = rand() % SCREEN_WIDTH;          /* Random X position */
    model->coins[j].y = rand() % (SCREEN_HEIGHT - 64);  /* Random Y position */
    model->coins[j].active = true;                      /* Set the coin as active */
    }
}

/***********************************************************************
* Name: initialize_score
*
* Purpose: Initializes the game model with default values.
*
* Details: Initializes the score.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
***********************************************************************/
void initialize_score(Model *model)
{
    model->score.digits = 1;
    model->score.total = 1;
    model->score.prev_total = 0;
}

void initialize_ground(Model *model, int y) 
{
	model->ground.y = y;
}

/***********************************************************************
* Name: move_animal
*
* Purpose: Moves the animal character.
*
* Details: Moves the animal character horizontally and vertically
*          based on the given displacement. Updates the previous
*          position.
*
* Parameters:
*     - doodle: Pointer to the animal object to be moved.
*     - displacement_x: Horizontal displacement.
*     - displacement_y: Vertical displacement.
***********************************************************************/
void move_animal(Animal *chicken, int displacement_x, int displacement_y)
{
    int screenBorderCheck;
  
    chicken->prev_x = chicken->x;
    chicken->prev_y = chicken->y;

    chicken->x += displacement_x;

    if(chicken->x > SCREEN_WIDTH)
        chicken->x -= SCREEN_WIDTH;
    else 
        if(chicken->x < 0)
            chicken->x += SCREEN_WIDTH;
  
    chicken->y += displacement_y;
}

/***********************************************************************
* Name: has_animal_moved
*
* Purpose: Checks if the animal has moved.
*
* Details: Compares the current animal position and facing direction
*          with the previous state to determine if there's movement.
*
* Parameters:
*     - animal: Pointer to the animal object.
* Returns:
*     - bool: True if the animal has moved, false otherwise.
***********************************************************************/
bool has_animal_moved(Animal *chicken)
{
    if(chicken->prev_x != chicken->x || chicken->prev_y != chicken->y)
        return true;

    return false;
}
