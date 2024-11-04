/*
Author: Jacky & Ochihai
Date: Oct 25, 2024

Purpose:
    - Defines functions for initializing the game model, moving game objects, and checking object movements.
 */

#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"
#include <osbind.h>

#define MAX_COINS 5
#define MAX_MONSTER 5
#define MAX_VELOCITY 14
#define ANIMAL_HORIZONTAL_MOVEMENT 16

typedef struct 
{
    int x, y; 
    int prev_x, prev_y;
    int velocity;
    int max_y;
    bool isFalling;
    bool dead;
} Animal;

typedef struct 
{
    int x, y; 
    bool off_screen;
} Monster;

typedef struct
{
    int x, y;        
    bool active;     
    bool collected; 
} Coin;

typedef struct
{
  int total;
  int digits;
  int prev_total;
} Score;

typedef struct 
{
	int y;
} Ground;

typedef struct {
    Animal chicken;
    Monster monster[MAX_MONSTER];
    Score score;
    Coin coins[MAX_COINS];   
    Ground ground;
} Model;

void initialize_animal(Model *model);
void initialize_monster(Model *model);
void initialize_coins(Model *model);
void initialize_ground(Model *model, int y);
void move_animal(Animal *chicken, int displacement_x, int displacement_y);
bool has_animal_moved(Animal *chicken);

#endif
