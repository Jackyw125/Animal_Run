#include "model.h"
#include <stdlib.h>  

/***********************************************************************
 * Name: initialize_model
 *
 * Purpose:
 *   Initializes all components of the game model, setting up the initial 
 *   state for the game.
 *
 * Details:
 *   This function initializes various elements of the game model, 
 *   including the player character (e.g., chicken), monsters, coins, 
 *   score, and ground.
 *
 * Parameters:
 *   - model: Pointer to the game model structure to be initialized.
 ***********************************************************************/
void initialize_model(Model *model)
{
    initialize_animal(&(model->chicken));
    initialize_monster((model->monster), (model->coins));
    initialize_coins((model->coins), (model->monster));
    initialize_score(&(model->score));
    initialize_ground(&(model->ground), GROUND_Y); 
}

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
void initialize_animal(Animal *chicken)
{
    chicken->x = 10;
    chicken->y = (GROUND_Y) - 62;
    chicken->prev_x = -1;
    chicken->prev_y = -1;
    chicken->velocity = ANIMAL_HORIZONTAL_MOVEMENT;
    chicken->isFalling = false;
    chicken->velocity_y = 0;
    chicken->dead = false;
}

/***********************************************************************
* Name: initialize_monster
*
* Purpose: Initializes the monster model with default values.
*
* Details: Initializes the monsters.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
***********************************************************************/
void initialize_monster(Monster *monster, Coin *coins) {
    int i, j;
    bool isColliding;

    for (i = 0; i < MAX_MONSTER; i++) {
        do {
            /*Randomly place the monster within the valid horizontal and vertical bounds*/
            monster[i].x = rand();
            monster[i].y = rand();
            monster[i].off_screen = false;

             isColliding = false;

            /*Check collision with coins*/
        for (j = 0; j < MAX_COINS; j++) {
            if (check_object_collision(monster[i].x, monster[i].y, MONSTER_WIDTH, MONSTER_HEIGHT,
                                       coins[j].x, coins[j].y, COIN_WIDTH, COIN_HEIGHT)) {
                isColliding = true;
                break;
            }
        }

        /*Check collision with other monsters*/
        for (j = 0; j < i; j++) {
            if (check_object_collision(monster[i].x, monster[i].y, MONSTER_WIDTH, MONSTER_HEIGHT,
                                       monster[j].x, monster[j].y, MONSTER_WIDTH, MONSTER_HEIGHT)) {
                isColliding = true;
                break;
            }
        }

        /*Ensure the monster stays within screen boundaries*/
        if (monster[i].y + MONSTER_HEIGHT > GROUND_Y || monster[i].y < 0) {
            isColliding = true;
        }

        } while (isColliding);
    }
}

/***********************************************************************
* Name: initialize_score
*
* Purpose: Initializes the coin model with default values.
*
* Details: Initializes the coins.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
***********************************************************************/

void initialize_coins(Coin *coins, Monster *monster) {
    int j, k;
    bool isColliding;

    for (j = 0; j < MAX_COINS; j++) {
        do {
            /*Randomly place the coin within valid horizontal and vertical bounds*/
            coins[j].x = rand() % SCREEN_WIDTH;
            coins[j].y = rand() % (GROUND_Y - COIN_HEIGHT);
            coins[j].active = true;

            isColliding = false;

            /*Check collision with monsters*/
            for (k = 0; k < MAX_MONSTER; k++) {
                if (check_object_collision(coins[j].x, coins[j].y, COIN_WIDTH, COIN_HEIGHT,
                                           monster[k].x, monster[k].y, MONSTER_WIDTH, MONSTER_HEIGHT)) {
                    isColliding = true;
                    break;
                }
            }
            /*Ensure the coin stays within screen boundaries*/
            if (coins[j].y + COIN_HEIGHT > GROUND_Y || coins[j].y < 0) {
                isColliding = true;
            }

        } while (isColliding);
    }
}

/***********************************************************************
* Name: initialize_score
*
* Purpose: Initializes the score model with default values.
*
* Details: Initializes the score.
*
* Parameters:
*     - score: Pointer to the score to be initialized.
***********************************************************************/
void initialize_score(Score *score)
{
    score->digits = 0;
    score->total = 0;
    score->prev_total = 0;
}

/***********************************************************************
* Name: initialize_ground
*
* Purpose: Initializes the ground model with default values.
*
* Details: Initializes the ground.
*
* Parameters:
*     - model: Pointer to the game model to be initialized.
***********************************************************************/
void initialize_ground(Ground *ground, int y) 
{
	ground->y = y;
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
    chicken->y += displacement_y;
}

/***********************************************************************
* Name: animal_horizontal_movement
*
* Purpose: Handles horizontal movement of the animal.
*
* Details: Handles animal's horizontal movement, including falling,
*          jumping, and collision detection with coins.
*
* Parameters:
*     - model: Pointer to the game model.
***********************************************************************/
void animal_horizontal_movement(Model *model)
{
    model->chicken.prev_x = model->chicken.x;
    move_animal(&(model->chicken), ANIMAL_HORIZONTAL_MOVEMENT, 0);
    if (model->chicken.x > 640) {
        model->chicken.x = 0;
    }
}

/***********************************************************************
* Name: has_animal_moved
*
* Purpose: Checks if the animal has moved.
*
* Details: Compares the current animal position
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


/***********************************************************************
 * Name: check_object_collision
 *
 * Purpose:
 *   Checks for a collision between two rectangular objects.
 *
 * Details:
 *   Determines whether two rectangles overlap based on their 
 *   coordinates and dimensions. 
 *
 * Parameters:
 *   - x, y: Coordinates of the top-left corner of the first rectangle.
 *   - width, height: Dimensions of the first rectangle.
 *   - x2, y2: Coordinates of the top-left corner of the second rectangle.
 *   - width2, height2: Dimensions of the second rectangle.
 *
 * Return Value:
 *   - `true` if the rectangles overlap (collision detected).
 *   - `false` otherwise (no collision).
 ***********************************************************************/
bool check_object_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2) {
    return (x < x2 + width2) && (x + width > x2) &&
           (y < y2 + height2) && (y + height > y2);
}
