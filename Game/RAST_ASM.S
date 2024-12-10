;clears the screen	
;Author : Marc Schroeder	

	    xdef		_clear_screen
		xdef		_set_video_base
		xdef		_get_video_base
		xdef		_super_mode
		xdef		_user_mode

base		equ		64		; offset from SP, not A6

_clear_screen:	movem.l		d0-7/a0-6,-(sp)
		lea		zeros,a0
		movem.l		(a0)+,d1-7/a1-6
		movea.l		base(sp),a0
		adda.l		#32000,a0
		move.w		#614,d0
fill_loop:	movem.l		d1-7/a1-6,-(a0)
		dbra		d0,fill_loop
		movem.l		d1-5,-(a0)
		movem.l		(sp)+,d0-7/a0-6
		rts

video_address  equ		$FFFF8201
GEMDOS			   equ		1

;----------------- SUBROUTINE: UINT32 *get_video_base(); ----------------
; PURPOSE:  Returns the address stored at the video base register

_get_video_base:
		link	a6,#0               ; Set up a stack frame
		movem.l	d3/a0,-(sp)         ; Save registers d3 and a0 on the stack
		
		bsr _super_mode           	

		clr.l 	d3                	; Clear d3 to prepare for data retrieval
		move.l  #video_address,a0 	; Load the address of the video register into a0
		movep.w (a0),d3           	; Read a 16-bit value from the video register into d3
		lsl.l   #8,d3             	; Shift left by 8 bits to align it into a 32-bit value

		bsr _user_mode            
		
		move.l d3,d0              	; Move the retrieved value into d0 (return register)
		
		movem.l	(sp)+,d3/a0        	; Restore registers d3 and a0 from the stack
		unlk	a6                 	; Restore the stack frame
		rts                       	; Return to the caller

;----------------- SUBROUTINE: void set_video_base(UINT32 *); ----------------
; PURPOSE:  Updates the video base register with the specified address
; CALLER INPUT: Pointer passed in stack frame at offset VB_OFFSET

VB_OFFSET 	equ     	8

_set_video_base:
		link	a6,#0               ; Set up a stack frame
		movem.l	d0/a0,-(sp)         ; Save registers d0 and a0 on the stack

		bsr		_super_mode         ; Enter supervisor mode

		clr.l 	d0                	; Clear d0 to prepare for the new base address
		move.l	VB_OFFSET(a6),d0 	; Load the new address from the stack frame into d0
		lsr.l   #8,d0             	; Shift right by 8 bits for proper alignment
		move.l  #video_address,a0 	; Load the address of the video register into a0
		movep.w d0,(a0)           	; Write the aligned value into the video register
		
		bsr		_user_mode         
		
		movem.l	(sp)+,d0/a0        ; Restore registers d0 and a0 from the stack
		unlk	a6                 ; Restore the stack frame
		rts                        ; Return to the caller

;----------------- SUBROUTINE: void enter_super(); ----------------
; PURPOSE:  Lets user enter supervisor mode
_super_mode:
		movem.l	d0,-(sp)           ; Save register d0 on the stack

		clr.l	-(sp)              ; Push a zero to indicate user stack for GEMDOS
		move.w	#$20,-(sp)         ; Push the GEMDOS trap code for entering supervisor mode
		trap	#GEMDOS            
		addq.l	#6,sp              ; Clean up the stack after the trap
		move.l	d0,old_ssp         ; Save the old system stack pointer in old_ssp
		
		movem.l	(sp)+,d0           ; Restore register d0 from the stack
		rts                        ; Return to the caller

;----------------- SUBROUTINE: void exit_super(); ----------------
; PURPOSE:  Lets user exit supervisor mode

_user_mode:
		movem.l	d0,-(sp)           ; Save register d0 on the stack

		move.l	old_ssp(pc),-(sp)  ; Push the old system stack pointer onto the stack
		move.w	#$20,-(sp)         ; Push the GEMDOS trap code for exiting supervisor mode
		trap	#GEMDOS            
		addq.l	#6,sp              ; Clean up the stack after the trap
		
		movem.l	(sp)+,d0           ; Restore register d0 from the stack
		rts                       ; Return to the caller

;----------------- Data Section ----------------
old_ssp:	ds.l	    1		; Reserve space for the saved system stack pointer (SSP)
zeros:		ds.l		13      ; Reserve 13 longwords (52 bytes) for potential scratchpad use
