/*
Author: Jacky & Ochihai
Date: Dec 09, 2024

Purpose:
    - VBL DRIVER
*/
#ifndef VBL_H
#define VBL_H

#include "GLOBAL.H"
#include "EVENTS.H"
#include "MODEL.H"
#include <osbind.h>

void do_vbl_isr();
void main_vbl_isr();

#endif
