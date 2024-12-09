#include "psg.h"
#include <stdio.h>
#include <osbind.h>
#include <unistd.h> /* used for pauses*/

/*
 * File: tst_psg.c
 * Stage 7
 * Date: November 15, 2024 
 * Authors: Both members 
 * Prof: Marc Schroeder
 * ---------------
 * Tester for the psg libary (psg.c)
 *
 *
 *  Team Members:
 * - Ochihai Omuha
 * - Jacky On
 *
 *
 */
 
 #define pause 2


 int main ()
 {
	
	printf("Starting PSG Tests\n");
	/*** TESTING Channel A ***/
	printf("Enabling channel A with Tone(0) and Noise(1)\n");
	enable_channel(ch_a,1,0);

	printf("BEGIN Channel A Volume Tests\n");
    printf("Setting channel A volume to 15(MAX)\n");
    set_volume(ch_a, 15);
    sleep(pause);

	printf("Setting channel A tone to 0x0AA\n");
    set_tone(ch_a, 170);
    sleep(pause);

    printf("Setting channel A volume to 4\n");
    sleep(pause);
    set_volume(ch_a, 4);
    sleep(pause);
    
    printf("Setting channel A volume to 7\n");
    sleep(pause);
    set_volume(ch_a, 7);
    sleep(pause);
    
    printf("STOPPING SOUND\n");
    sleep(pause);
    stop_sound();



	/*** TESTING CHANNEL B ***/
    printf("Enabling channel B with Tone(0) and Noise(1)\n");
    enable_channel(ch_b, 1, 0);
    
    printf("BEGIN Channel B Volume Tests\n");
    printf("Setting channel B volume to 15(MAX)\n");
    set_volume(ch_b, 15);
    sleep(pause);
    
    printf("Setting channel B tone to 0x3EF\n");
    set_tone(ch_b, 300);
    sleep(pause);
    
    printf("Setting channel B volume to 4\n");
    sleep(pause);
    set_volume(ch_b, 4);
    sleep(pause);
    
    printf("Setting channel B volume to 7\n");
    sleep(pause);
    set_volume(ch_b, 7);
    sleep(pause);
    
    printf("STOPPING SOUND\n");
    sleep(pause);
    stop_sound();


	/***TESTING CHANNEL C***/
    printf("Channel C Tests with Tone 0x123\n");
    printf("Enabling channel C with Tone(0) and Noise(1)\n");
    enable_channel(ch_c, 1, 0);
    
    printf("BEGIN Channel C Volume Tests\n");
    printf("Setting channel C volume to 15(MAX)\n");
    set_volume(ch_c, 15);
    sleep(pause);
    
    printf("Setting channel C tone to 123\n");
    set_tone(ch_c, 123);
    sleep(pause);
    
    printf("Setting channel C volume to 4\n");
    sleep(pause);
    set_volume(ch_c, 4);
    sleep(pause);
    
    printf("Setting channel C volume to 7\n");
    sleep(pause);
    set_volume(ch_c, 7);
    sleep(pause);
    
    printf("STOPPING SOUND\n");
    sleep(pause);
    stop_sound();


	/*TESTING ALL CHANNEL TOGETHER*/
    printf("TEST ALL CHANNELS WITH TONE AT ONCE\n");
    printf("ENABLING ALL CHANNELS WITH TONE\n");
    enable_channel(ch_a, 1, 0);
    enable_channel(ch_b, 1, 0);
    enable_channel(ch_c, 1, 0);

    printf("Setting all channel volumes to 15(MAX)\n");
    set_volume(ch_a, 15);
    set_volume(ch_b, 15);
    set_volume(ch_c, 15);

    printf("Setting channel A tone to 0x0AA\n");
    set_tone(ch_a, 170);
    printf("Setting channel B tone to 0x3EF\n");
    set_tone(ch_b, 300);
    printf("Setting channel C tone to 123\n");
    set_tone(ch_c, 123);
    sleep(pause);
    sleep(pause);
    sleep(pause);
    sleep(pause);

    printf("STOPPING SOUND\n");
    sleep(pause);
    stop_sound();
    sleep(pause);
	 
	return 0;
 }