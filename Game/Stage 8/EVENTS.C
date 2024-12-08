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
        if (check_collision_monster(&(model->chicken), &(model->monster))) {
            model->chicken.dead = true;
            *endGame = true;
    }
    return;
}

/***********************************************************************
* Name: animal_input
*
* Purpose: Handles user input for animal movement.
*
* Details: If the spacebar is pressed, the animal jumps vertically.
*          If the W key is held, the animal flies continuously.
*          If no keys are held, the animal falls if in the air.
*          If the animal is dead, no movement is allowed.
*
* Parameters:
*     - chicken: Pointer to the animal object.
*     - key: Represents the pressed key (or '\0' if no key is held).
***********************************************************************/
void animal_input(Animal *chicken, char key)
{
    int i;
    if (chicken->dead)
        return;
    if (key == 'W' || key == 'w') {
        animal_fly(chicken);
        for(i = 0; i < 8875; i++)
            ;
    } else {
        if (chicken->state == ANIMAL_STATE_FLYING) {
            chicken->state = ANIMAL_STATE_FLY_DOWN; 
        }
    }
    if (chicken->state == ANIMAL_STATE_ON_GROUND && key == ' ' && chicken->state != ANIMAL_STATE_JUMP_DOWN) {
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
bool check_collision_coin(Animal *chicken, Coin *coins, int index) {
        int i = index;
        if (coins[i].active) {
            bool horizontal_overlap = (chicken->x + CHICKEN_WIDTH > coins[i].x) &&
                                      (chicken->x < coins[i].x + COIN_WIDTH);

            bool vertical_overlap = (chicken->y + CHICKEN_HEIGHT > coins[i].y) &&
                                    (chicken->y < coins[i].y + COIN_HEIGHT);

            if (horizontal_overlap && vertical_overlap) {
                coins[i].active = false;
                return true; 
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
        bool horizontal_overlap = (chicken->x + CHICKEN_WIDTH > monster->x) &&
                                  (chicken->x < monster->x + MONSTER_WIDTH);

        bool vertical_overlap = (chicken->y + CHICKEN_HEIGHT > monster->y) &&
                                (chicken->y < monster->y + MONSTER_HEIGHT);

        if (horizontal_overlap && vertical_overlap) {
            return true; 
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

/***********************************************************************
* Name: animal_vertical_movement
*
* Purpose: Handles vertical movement of the animal, including jumping,
*          falling, and flying states.
*
* Parameters:
*     - chicken: Pointer to the animal object.
***********************************************************************/
void animal_vertical_movement(Animal *chicken)
{
    switch (chicken->state) {
        case ANIMAL_STATE_JUMP:
            move_animal(chicken, ANIMAL_HORIZONTAL_JUMP, -MAX_VERT_VELOCITY);
            chicken->velocity_y = MAX_VERT_VELOCITY;
            if(chicken->velocity_y > 0) {
                chicken->state = ANIMAL_STATE_JUMP_DOWN;
            }
            break;
        case ANIMAL_STATE_JUMP_DOWN:
            chicken->y += GRAVITY;  
            if (chicken->y + CHICKEN_HEIGHT >= GROUND_Y) {
                chicken->y = GROUND_Y - CHICKEN_HEIGHT;
                chicken->velocity_y = 0;
                chicken->state = ANIMAL_STATE_ON_GROUND;
            }
            break;
        case ANIMAL_STATE_FLYING:
            chicken->y -= FLYING;
            if (chicken->y < 0) {    
                chicken->y = 0;
            }
            break;
        case ANIMAL_STATE_FLY_DOWN:
            chicken->y += GRAVITY;  
            if (chicken->y + CHICKEN_HEIGHT >= GROUND_Y) {
                chicken->y = GROUND_Y - CHICKEN_HEIGHT;
                chicken->velocity_y = 0;
                chicken->state = ANIMAL_STATE_ON_GROUND;
            }
            break;
        case ANIMAL_STATE_ON_GROUND:
            chicken->velocity_y = 0;
            break;
        default:
            break;
    }
}

void animal_jump(Animal *chicken)
{
    chicken->state = ANIMAL_STATE_JUMP;
}

void animal_fly(Animal *chicken)
{
    chicken->state = ANIMAL_STATE_FLYING;
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
void update_score(Model *model) {
    int i;
    for (i = 0; i < MAX_COINS; i++) {
        if (model->coins[i].active && 
            check_collision_coin(&model->chicken, model->coins, i)) {
            model->coins[i].active = false; 
            model->score.total++;
        }
    }
}

bool respawn_event(Model *model) {
    int i;

    for (i = 0; i < MAX_COINS; i++) {
        if (model->coins[i].active) {
            return false; 
        }
    }
    return true; 
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
void process_synchronous_events(Model *model, bool *endGame)
{
    check_animal_death(model, endGame);
    animal_horizontal_movement(&(model->chicken));
    animal_vertical_movement(&(model->chicken));
    update_score(model);    
}

void process_asynchronous_events(Model *model, char *pressedKey)
{
    animal_input(&(model->chicken), *pressedKey);
}
