#include "music.h"

#include <stdlib.h>
#include <stdio.h>
#include <osbind.h>



UINT32 game_clock();

/*
 * File: tst_music.c
 * Stage 7
 * Date: November 16, 2024 
 * Authors: Both members 
 * Prof: Paul Pospisil
 * ---------------
 * Tester for the music libary (music.c)
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

	UINT32 current_clock;
	UINT32 old_clock = 0;
	UINT32 time;
	
	int test = 1; /* Number of times ran */
	
	printf("Testing Music\n");

	start_music();
	
	while (test){
	current_clock = game_clock();
	time = current_clock - old_clock;
	 
	if (time > 0){
	
		update_music(time);
	
	}
	
	
	
	if(Cconis())
	{
		test = 0;
	
		Cnecin();
	}
	old_clock = current_clock;
	} 
	
	stop_sound();
	return 0;
 
 }
 
 
 UINT32 game_clock() {

	UINT32 current_clock;
	long old_ssp;
	
	old_ssp = Super(0);
	current_clock = *((UINT32 *)0x462);
	Super(old_ssp);
	
	return current_clock;
	 
 }