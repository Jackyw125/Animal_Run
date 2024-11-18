#include "events.h"

/***********************************************************************
* Name: check_animal_death
*
* Purpose: Checks if the animal has died.
*
* Details: Checks if the animal has collided with the monster.
*
* Parameters:
*     - model: Pointer to the game model.
*     - endGame: Pointer to a boolean indicating game end.
***********************************************************************/
void check_animal_death(Model *model, bool *endGame)
{
    int i; 
    for (i = 0; i < MAX_MONSTER; i++) {
        if (check_collision_monster(&(model->chicken), &(model->monster[i]))) {
            model->chicken.dead = true;
            *endGame = true;
        }
    }
    return;
}

/***********************************************************************
* Name: animal_input
*
* Purpose: Handles user input for animal movement.
*
* Details: If the spacebar is pressed, moves the animal vertically.
*          If the animal is dead, no movement is allowed.
*
* Parameters:
*     - chicken: Pointer to the animal object.
*     - key: chicken representing the pressed key.
***********************************************************************/
void animal_input(Animal *chicken, char key)
{
    if(chicken->dead)
        return;

    if(key == ' '){
        animal_jump(chicken);
    }

}

/***********************************************************************
* Name: check_collision_coin
*
* Purpose: Checks collision between animal and coins.
*
* Details: Checks if the animal collides with any of the coins.
*
* Parameters:
*     - animal: Pointer to the animal object.
*     - coin: Pointer to the array of coin objects.
* Returns:
*     - bool: True if collision occurs, false otherwise.
***********************************************************************/
bool check_collision_coin(Animal *chicken, Coin *coins) {
    int i;
    for (i = 0; i < MAX_COINS; i++) {
        if (coins[i].active) {
            bool horizontal_overlap = (chicken->x + CHICKEN_WIDTH > coins[i].x) &&
                                      (chicken->x < coins[i].x + COIN_WIDTH);

            bool vertical_overlap = (chicken->y + CHICKEN_HEIGHT > coins[i].y) &&
                                    (chicken->y < coins[i].y + COIN_HEIGHT);

            if (horizontal_overlap && vertical_overlap) {
                return true; 
            }
        }
    }
    return false; 
}

/***********************************************************************
* Name: check_collision_monster
*
* Purpose: Checks collision between animal and monster.
*
* Details: Checks if the animal collides with the monster.
*
* Parameters:
*     - animal: Pointer to the animal object.
*     - monster: Pointer to the monster object.
* Returns:
*     - bool: True if collision occurs, false otherwise.
***********************************************************************/

bool check_collision_monster(Animal *chicken, Monster *monster)
{
    int i; 
    for (i = 0; i < MAX_MONSTER; i++) {
        bool horizontal_overlap = (chicken->x + CHICKEN_WIDTH > monster[i].x) &&
                                  (chicken->x < monster[i].x + MONSTER_WIDTH);

        bool vertical_overlap = (chicken->y + CHICKEN_HEIGHT > monster[i].y) &&
                                (chicken->y < monster[i].y + MONSTER_HEIGHT);

        if (horizontal_overlap && vertical_overlap) {
            return true; 
        }
    }
    return false;
}

/***********************************************************************
* Name: check_ground_collision
*
* Purpose: Checks collision between animal and ground.
*
* Details: Checks if the animal collides with the ground.
*
* Parameters:
*     - animal: Pointer to the animal object.
*     - ground: Pointer to the ground object.
* Returns:
*     - bool: True if collision occurs, false otherwise.
***********************************************************************/
bool check_ground_collision(Animal *chicken, Ground* ground) {
    if (chicken->y ==  ground->y) 
    {
        return true;
    }
    return false;
}

void animal_vertical_movement(Model *model)
{
    Animal *chicken = &(model->chicken);

    switch (chicken->state) {
        case ANIMAL_STATE_MOVING_UP:
            chicken->max_y = -MAX_VERT_VELOCITY;

            chicken->y -= chicken->max_y;
            if (chicken->max_y <= 0) {
                chicken->state = ANIMAL_STATE_MOVING_DOWN;
            }
            break;

        case ANIMAL_STATE_MOVING_DOWN:
      
            chicken->y += chicken->velocity;

            chicken->max_y += MAX_VERT_VELOCITY;

            if (chicken->y + CHICKEN_HEIGHT >= GROUND_Y) {
                chicken->y = GROUND_Y - CHICKEN_HEIGHT;
                chicken->max_y = 0;
                chicken->state = ANIMAL_STATE_ON_GROUND;
            }
            break;

        case ANIMAL_STATE_ON_GROUND:
            chicken->max_y= 0;
            break;

        default:
            break;
    }
    if (chicken->y < 0) {
        chicken->y = 0;
        chicken->max_y = 0;
        chicken->state = ANIMAL_STATE_MOVING_DOWN;
    }
}

void animal_jump(Animal *chicken)
{
    if (chicken->state == ANIMAL_STATE_ON_GROUND) {
        chicken->max_y = MAX_VERT_VELOCITY; 
        chicken->state = ANIMAL_STATE_MOVING_UP;
    }
}

/***********************************************************************
 * Function Name: update_score
 *
 * Purpose:
 *   Updates the score in the game model when a collision is detected 
 *   between the player's character (e.g., chicken) and a coin.
 *
 * Parameters:
 *   - model: Pointer to the game model structure containing the 
 *            player character, coins, and score data.
 *
 * Details:
 *   This function is responsible for handling score increments when
 *   the player collects a coin. It checks for a collision using the 
 *   `check_collision_coin` function. If a collision is detected:
 ***********************************************************************/
void update_score(Model *model)
{
    int i;
    for (i = 0; i < MAX_COINS; i++) {
        if (model->coins[i].active && 
            check_object_collision(model->chicken.x, model->chicken.y, CHICKEN_WIDTH, CHICKEN_HEIGHT,
                                   model->coins[i].x, model->coins[i].y, COIN_WIDTH, COIN_HEIGHT)) {
            model->coins[i].active = false;  
            model->score.total++;  
        }
    }
}
