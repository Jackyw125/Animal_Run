    	xref _do_vbl_isr
	xdef _main_vbl_isr
 

;----------------- SUBROUTINE: void main_vbl_isr(); ----------------
; PURPOSE:  IS the Vertical Blank ISR. Calls a helper function in C do process
;           all the synchronous events
;-------------------------------------------------------------------------------
_main_vbl_isr:
	movem.l	d0-4/a0-4,-(sp)
	jsr     _do_vbl_isr
	movem.l (sp)+,d0-4/a0-4
	rte
