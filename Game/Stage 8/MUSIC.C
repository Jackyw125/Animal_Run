#include "music.h"
#include <stdio.h>

/*
 * File: music.c
 * Stage 7
 * Date: November 16, 2024
 * Author: Both members
 * Prof: Paul Pospisil
 * --------------
 * The purpose of this file is to implement the music-related functionalities of our game.
 *
 * Team Members:
 * - Ochihai Omuha
 * - Jacky On
 * 
 */
 
 int current_note = 0; 
 int duration;
 
 /* Paul McCartney - Wonderful Christmastime */

const notes wonderful_christmastime[] = {
    /* First phrase: "D G A D" */
    {293, 50},  /* D */
    {392, 50},  /* G */
    {440, 50},  /* A */
    {293, 50},  /* D */

    /* Second phrase: "A G E D" */
    {440, 50},  /* A */
    {392, 50},  /* G */
    {329, 50},  /* E */
    {293, 50},  /* D */

    /* Third phrase: "D G A B" */
    {293, 50},  /* D */
    {392, 50},  /* G */
    {440, 50},  /* A */
    {493, 50},  /* B */

    /* Fourth phrase: "A G F# G" */
    {440, 50},  /* A */
    {392, 50},  /* G */
    {369, 50},  /* F# */
    {392, 50},  /* G */
}; 
 
 /*
 * Function: start_music
 * ---------------------
 * Begins the playing of the song by loading the data for the first note into the PSG.
 *
 * Parameters:
 *   None.
 * 
 * Returns:
 *   None.
 *
 * Side Effects:
 *   Begins the playing of the song. The state of the PSG will be modified.
 *
 * Assumptions/Limitations/Known Bugs:
 *   Assumes that the song data has been properly loaded and is ready to be played.
 *   Assumes that the PSG is properly initialized and ready to play music.
 */
void start_music()
{  
    set_tone(ch_a, wonderful_christmastime[current_note].pitch);
    enable_channel(ch_a, 1, 0);
	set_volume(ch_a,12);
	duration = wonderful_christmastime[current_note].duration;
	current_note++; 
}

/*
 * Function: update_music
 * ---------------------
 * Advances to the next note of the song if necessary, as determined by the amount of time elapsed since the previous call.
 *
 * Parameters:
 *   time_elapsed: The amount of time that has elapsed since the function was last called. This value is determined by the caller and is intended to be equal to the current value of the vertical blank clock, minus its value when the function was last called.
 * 
 * Returns:
 *   None.
 *
 * Side Effects:
 *   May advance to the next note of the song, modifying the state of the PSG.
 *
 * Assumptions/Limitations/Known Bugs:
 *   Assumes that the song data has been properly loaded and is ready to be played.
 *   Assumes that the PSG is properly initialized and ready to play music.
 */

void update_music(UINT32 time_elapsed)
{
	duration--;
	
	if (duration <= 0)
	{
		set_tone(ch_a,wonderful_christmastime[current_note].pitch);
		duration = wonderful_christmastime[current_note].duration;
		current_note++;
		
		if (current_note == 16)
			current_note = 0; /*Loop back to start */
	}
	
}


/*
 * Function: reset_song
 * --------------------
 * Resets the song to the beginning by initializing the current note and setting the tone and duration for the first note.
 *
 * Parameters:
 *   None.
 * 
 * Returns:
 *   None.
 *
 * Side Effects:
 *   Resets the state of the song and modifies the state of the PSG to play the first note.
 *
 * Assumptions/Limitations/Known Bugs:
 *   Assumes that the `wonderful_christmastime` song data is properly loaded and contains valid notes.
 *   Assumes that the PSG is properly initialized and ready to play music.
 */

void reset_song() {
    current_note = 0; 
    duration = wonderful_christmastime[current_note].duration; 
    set_tone(ch_a, wonderful_christmastime[current_note].pitch); 
}

