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
#define MAX_MONSTER 2
#define MAX_VERT_VELOCITY 24
#define ANIMAL_HORIZONTAL_MOVEMENT 16
#define ANIMAL_STATE_MOVING_UP 1
#define ANIMAL_STATE_MOVING_DOWN 2
#define ANIMAL_STATE_ON_GROUND 3

typedef struct 
{
    int x, y; 
    int prev_x, prev_y;
    int velocity;
    int max_y;
    int state;
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

void initialize_model(Model *model);
void initialize_animal(Animal *chicken);
void initialize_score (Score *score);
void initialize_monster(Monster *monster, Coin *coins);
void initialize_coins(Coin *coins, Monster *monster);
void initialize_ground(Ground *ground, int y);
void animal_horizontal_movement(Model *model);
void move_animal(Animal *chicken, int displacement_x, int displacement_y);
bool has_animal_moved(Animal *chicken);
bool check_object_collision(int x, int y, int width, int height, int x2, int y2, int width2, int height2);

#endif
