#ifndef ISRS_H
#define ISRS_H

#include "TYPES.H"
#include "globals.h"

#define IKBD_ISR 70

typedef void (*Vector)();

extern Vector VBL_orig_vector;
extern Vector IKBD_orig_vector;

extern UINT8 head;
extern UINT8 tail;

extern UINT8 IKBD_buffer[256];


void do_IKBD_ISR();

#endif