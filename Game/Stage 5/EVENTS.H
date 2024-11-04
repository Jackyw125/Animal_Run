/*
Author: Jacky & Ochihai
Date: Oct 25, 2024

Purpose:
    - Defines functions related to game events, such as animal movement, collision detection, and game state updates.
*/

#ifndef EVENTS_H
#define EVENTS_H

#include "MODEL.H"
#include "TYPES.H"

void animal_input(Animal *character, char key);
bool check_collision_animal_coin(Animal *chicken, Coin *coin);
bool check_collision_monster(Animal *chicken, Monster *monster);
bool check_ground_collision(Animal chicken, Ground* ground);
void animal_vertical_movement(Model *model);
void check_animal_death(Model *model, bool *endGame);

#endif
