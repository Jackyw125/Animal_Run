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

void check_animal_death(Model *model, bool *endGame);
void animal_input(Animal *chicken, char key);
bool check_collision_coin(Animal *chicken, Coin *coin, int index);
bool check_collision_monster(Animal *chicken, Monster *monster);
bool check_ground_collision(Animal *chicken, Ground* ground);
void animal_vertical_movement(Animal *chicken);
void animal_jump(Animal *chicken);
void animal_fly(Animal *chicken);
void update_score(Model *model);
bool respawn_event(Model *model);
void process_synchronous_events(Model *model, bool *endGame);
void process_asynchronous_events(Model *model, char *pressedKey);

#endif
