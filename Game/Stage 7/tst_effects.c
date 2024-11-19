#include "effects.h"

#include <stdio.h>
#include <osbind.h>

/*
 * File: tst_effects.c
 * Stage 7
 * Date: November 16, 2024 
 * Authors: Both members 
 * Prof: Paul Pospisil
 * ---------------
 * Tester for the effects libary (effects.c)
 *
 *
 *  Team Members:
 * - Ochihai Omuha
 * - Jacky On 
 *
 *
 */
 
 int main ()
 {
	
	/* Testing Sound Effects*/

    printf("BEGIN SOUND EFFECTS TEST\n");
    printf("PLAYING COIN COLLECTED\n");
	coin_collected();
	printf("Press Key to End Sound Effect\n");

	while (!Cconis())		/* tone now playing, await key*/
		;
	Cnecin(); 
	
	stop_sound();


	printf("PLAYING COLLISON \n");
    collison_effect();
    printf("Press Key to End Sound Effect\n");

    while (!Cconis())        /* tone now playing, await key */
        ;
    while (Cconis())         /* Clear any remaining key press in the buffer */
        Cconin();

    stop_sound();


	printf("PLAYING SPAWNING\n");
    spawn_effect();
    printf("Press Key to End Sound Effect\n");
    printf("END SOUNDS EFFECTS\n");

    while (!Cconis())        /* tone now playing, await key */
        ;
    while (Cconis())         /* Clear any remaining key press in the buffer */
        Cconin();




	 return 0;
 }