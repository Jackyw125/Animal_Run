#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>
#include "MODEL.h"
#include "EVENTS.h"
#include "types.h"

void print_model_status(Model *model);
void pause();

int main() {
    char key;
    Model model;
    bool endGame = false;
    int i;

    initialize_model(&model);
    printf("Game Initialized. Press SPACE to jump, W to fly, Q to quit.\n");

    while ((key = (char)(Cconin() & 0x00FF)) != 'q' && key != 'Q') {
    if (key == ' ') {
        process_asynchronous_events(&model, &key);
        printf("\n--- Jump Test ---\n");
        animal_jump(&(model.chicken));
        process_synchronous_events(&model, &endGame);
        print_model_status(&model);
        pause();
        printf("\n--- Falling Test ---\n");
        model.chicken.state = ANIMAL_STATE_JUMP_DOWN; 
        while (model.chicken.y + CHICKEN_HEIGHT < GROUND_Y) {
        process_synchronous_events(&model, &endGame); 
        }
        print_model_status(&model);

    }
    else if (key == 'W' || key == 'w') {
            process_asynchronous_events(&model, &key);
            printf("\n--- Fly Test ---\n");
            animal_fly(&(model.chicken));
            process_synchronous_events(&model, &endGame);
            print_model_status(&model);
        } else if (key == 'r' || key == 'R') {
            printf("\n--- Respawn Coins Test ---\n");
            for(i = 0; i < MAX_COINS; i++)
            {
                model.coins[i].active = false;
            }
            if (respawn_event(&model)) {
                printf("All coins collected. Respawning coins...\n");
                initialize_coins(model.coins, &(model.monster));
            }
            print_model_status(&model);
        } else if (key == 'c' || key == 'C') {
            printf("\n--- Collision Test ---\n");
            check_animal_death(&model, &endGame);
            if (endGame) {
                printf("Animal collided with monster! Game Over.\n");
            } else {
                printf("No collision with monster detected.\n");
            }
            print_model_status(&model);
        }

        process_asynchronous_events(&model, &key);

        if (endGame) {
            printf("\nGame Over! Resetting game...\n");
            initialize_model(&model);
            endGame = false;
        }
    }

    printf("Exiting test driver.\n");
    return 0;
}

void print_model_status(Model *model) {
    int i;
    printf("\nModel Status:\n");
    printf("Chicken - Position: (%d, %d), State: %d, Dead: %d\n",
           model->chicken.x, model->chicken.y, model->chicken.state, model->chicken.dead);
    printf("Monster - Position: (%d, %d)",
           model->monster.x, model->monster.y);
    printf("Coins:\n");
    for (i = 0; i < MAX_COINS; i++) {
        printf("  Coin %d - Position: (%d, %d), Active: %d\n",
               i, model->coins[i].x, model->coins[i].y, model->coins[i].active);
    }
    printf("Score - Total: %d\n", model->score.total);
    printf("Ground - Y Position: %d\n", model->ground.y);
}

/***********************************************************************
Function Name: pause

Purpose:
    Pause program execution until the user provides input.
***********************************************************************/
void pause() {
    while (!Cconis()) {
    }
     Cnecin(); 

}