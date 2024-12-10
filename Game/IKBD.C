/*
Author: Jacky & Ochihai
Date: Dec 09, 2024

Purpose:
    - IKBD ISR
*/

#include <osbind.h>

#include "IKBD.H"
#include "VEC_IN.H"

Vector IKBD_orig_vector;

UINT8 head = 0;
UINT8 tail = 0;

UINT8 IKBD_buffer[256];

unsigned char mouse_button = 0xF8;
unsigned char mouse_x = 0x00;
unsigned char mouse_y = 0x00;

int mouse_state = 0;

volatile   		unsigned char *const CTRL       = 0xFFFC00;
volatile const 	unsigned char *const STATUS		= 0xFFFC00;
volatile const  unsigned char  *const IKBD_RDR   = 0xFFFFFC02;
volatile		unsigned char *const MFP 		= 0xFFFA11; 
volatile		unsigned char *const INT_EN	    = 0xFFFA09; 

void do_IKBD_ISR(){
    unsigned char code = *(IKBD_RDR); 
	
	if(!mouse_state) {
		if((code & 0x80 ) != 0x80){ 
			IKBD_buffer[tail++] = code;
		}
		else if (code >= 0xF8){
			mouse_button = code;
			mouse_state--;
		}
	}
	else {
		if(mouse_state < 0) {
			mouse_x = code;
			mouse_state = 1;
		}
		else {
			mouse_y = code;
			mouse_state--;
		}
	}
		
  *MFP &= 0xBF;
}

