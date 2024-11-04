#include <stdio.h>
#include <stdlib.h>
#include <osbind.h>
#include "MODEL.h" 
#include "EVENTS.h"
#include "types.h"

int main() {
    char key;
    int y = 350;
    int i = 1;  
    int j = 1; 
    Model model;
    initialize_animal(&model); 
    initialize_monster(&model); 
    initialize_coins(&model); 
    initialize_ground(&model, y); 

    /* Starting message */

    printf("Game Initialized. Use SPACEBAR to move the animal.");
    printf("Press space to simulate a tick, and 'Q' to quit.\n");

     while ((key = (char)(Cconin() & 0x00FF)) != 'q' && key != 'Q')
    {
        /*handle_keypress(&model, key);
        Cconws("\033E"); /* Clears the console */
        
        /* Prints the current state of the animal and monster objects */
        printf("-------------------------------------------------\n");
        printf("Animal (Chicken) Position: (%d, %d)\n", model.chicken.x, model.chicken.y);
        printf("Animal Velocity: %d, IsFalling: %s\n", model.chicken.velocity, model.chicken.isFalling ? "True" : "False");
        printf("Monster Position: (%d, %d)\n", model.monster[i].x, model.monster[i].y);
        printf("Monster Off-Screen: %s\n", model.monster[i].off_screen ? "True" : "False");
        printf("Coin %d Position: (%d, %d)\n", j, model.coins[j].x, model.coins[j].y);
        printf("Coin %d Collected: %s\n", j, model.coins[j].collected ? "True" : "False");
        printf("Ground Position: (%d)\n", model.ground.y);
        printf("-------------------------------------------------\n");
        
     }

        printf("Exiting...\n");
        return 0;
}
