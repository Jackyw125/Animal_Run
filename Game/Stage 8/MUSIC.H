#ifndef MUSIC_H
#define MUSIC_H

#include "psg.h"
#include "TYPES.H"




/* ***************** Header File for the music library ***************** */
/*
 * File: music.h
 * Stage 7
 * Date: Novmeber 16, 2024
 * Author: Both members
 * Prof: Paul Pospisil
 * 
 *  --------------
 * Contains prototypes for all the music based functions of the game 
 * 
 * Team Members:
 * - Ochihai Omuha
 * - Jacky On
 * 
 */
 
 /* Define a struct for a note */
 typedef struct {
	int pitch;   	/* Frequency or pitch of the note */  
	int duration;   /* Duration of the note */
 } notes;
 
 
void start_music();
void update_music(UINT32 time_elapsed);
void reset_song()


 #endif