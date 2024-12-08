#include "effects.h"

#include <osbind.h>
#include <stdio.h>


/*
 * File: effects.c
 * Stage 7
 * Date: November 16, 2024
 * Author: Both members
 * Prof: Paul Pospisil
 * --------------
 * The purpose of this file is to define the sound effects that will be used in the program.

 *
 * Team Members:
 * - Ochihai Omuha
 * - Jacky On
 * 
 */

/*
 * Function: coin_collected 
 * ------------------------
 * Simulates the sound of an coin collected.
 *
 * Parameters:
 *   None.
 * 
 * Returns:
 *   None.
 *
 *
 * Assumptions/Limitations/Known Bugs:
 *   Assumes that the PSG is properly initialized and ready to play sound effects.
 */


void coin_collected()
{		
	set_noise(0x1F);
	set_tone(ch_c,0);
	set_volume(2,0x10);
	set_envelope(0x00,0x38);

}

/*
 * Function: collision_effect
 * --------------------------
 * Simulates the sound of a collision.
 *
 * Parameters:
 *   None.
 * 
 * Returns:
 *   None.
 *
 *
 * Assumptions/Limitations/Known Bugs:
 *   Assumes that the PSG is properly initialized and ready to play sound effects.
 */

void collison_effect()
{
	set_noise(0x15);
	set_tone(ch_c,350);
	set_volume(2,0x15);
	set_envelope(0x06,0x05);	
	
		
}

/*
 * Function: spawn_effect
 * ------------------------
 * Simulates the sound of a character spawn.
 *
 * Parameters:
 *   None.
 * 
 * Returns:
 *   None.
 *
 *
 * Assumptions/Limitations/Known Bugs:
 *   Assumes that the PSG is properly initialized and ready to play sound effects.
 */

void spawn_effect()
{
	set_noise(0xAA);
	set_tone(ch_c,200);
	set_volume(ch_c,0x15);
	set_envelope(0x04,0x09);
	

}