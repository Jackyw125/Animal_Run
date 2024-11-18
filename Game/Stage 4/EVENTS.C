#include "events.h"

/***********************************************************************
* Name: check_animal_death
*
* Purpose: Checks if the animal has died.
*
* Details: Checks if the animal has fallen below the screen height
*          or collided with the monster. Updates the endGame flag
*          accordingly if the animal is dead.
*
* Parameters:
*     - model: Pointer to the game model.
*     - endGame: Pointer to a boolean indicating game end.
***********************************************************************/

void check_animal_death(Model *model, bool *endGame)
{
    if(model->chicken.y > SCREEN_HEIGHT)
        *endGame = true;
    
    if(check_collision_monster(&(model->chicken), &(model->monster)))
        model->chicken.dead = true;
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
*     - character: Pointer to the animal object.
*     - key: Character representing the pressed key.
***********************************************************************/

void animal_input(Animal *character, char key)
{
    if(character->dead)
        return;

    switch(key)
    {
        case ' ':  
            if (!character->isFalling) { 
                character->velocity = MAX_VELOCITY;  
                character->isFalling = true;  
                move_animal(character, 0, -(character->velocity)); 
            }
            break;
        default:
            break;
    }
}

/***********************************************************************
* Name: check_collision_animal_coin
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

bool check_collision_animal_coin(Animal *chicken, Coin *coin)
{
    UINT8 i;
    int heightDifference;

    for (i = 0; i < MAX_COINS; i++) {
        if (coin[i].active && chicken->x + CHICKEN_WIDTH > coin[i].x && chicken->x < coin[i].x + COIN_WIDTH) {
            heightDifference = coin[i].y - (chicken->y + CHICKEN_HEIGHT);
            if (heightDifference < MAX_VELOCITY + 10 && heightDifference > -MAX_VELOCITY) {
                return i;  /*Return the index of the collided coin*/
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
    if (chicken->y+CHICKEN_HEIGHT > monster->y && 
        chicken->y < monster->y +MONSTER_HEIGHT &&
        chicken->x + CHICKEN_WIDTH > monster->x &&
        chicken->x < monster->x + MONSTER_WIDTH)   
    {
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
    if (chicken->y >=  ground->y) 
    {
        return true;
    }
    return false;
}

/***********************************************************************
* Name: animal_vertical_movement
*
* Purpose: Handles vertical movement of the animal.
*
* Details: Handles animal's vertical movement, including falling,
*          jumping, and collision detection with coins.
*
* Parameters:
*     - model: Pointer to the game model.
***********************************************************************/

void animal_vertical_movement(Model *model)
{
    Animal *chicken = &(model->chicken);
    if(chicken->max_y != 0)
        chicken->max_y = MAX_VELOCITY;

    if (chicken->y <= 0) {
        chicken->y = 0;           
        chicken->velocity = 0;     
        chicken->isFalling = false; 
        return;                   
    }

    if (chicken->y + CHICKEN_HEIGHT >= SCREEN_HEIGHT) {
        chicken->y = SCREEN_HEIGHT - CHICKEN_HEIGHT; 
        chicken->velocity = 0;    
        chicken->isFalling = false; 
        return;
    }
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
    move_animal(&model->chicken);
    if (model->chicken.x > 640) {
        model->chicken.x = 0;
    }
}

void update_score(Model *model)
{
    int collidedCoinIndex = check_collision_animal_coin(&(model->chicken), model->coins);

    if (collidedCoinIndex != -1) 
    { 
        model->coins[collidedCoinIndex].active = false; 
        model->score.total++; 
    }
}
