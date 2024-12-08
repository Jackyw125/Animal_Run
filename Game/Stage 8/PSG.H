#ifndef PSG_H
#define PSG_H

#include "TYPES.h"

/* ***************** Header File for the psg library ***************** */
/*
 * File: psg.h
 * Stage 7
 * Date: November 16, 2024
 * Author: Both members
 * Prof: Paul Pospisil
 * 
 *  --------------
 * Contains prototypes for all the psg based functions of the game 
 * 
 * Team Members:
 * - Ochihai Omuha
 * - Jacky On
 * 
 */



/* Page 7 of the YM2149 Documentation */

/* fine tune registers */
#define CH_A_FINE_TONE 0x0          /* R0 */
#define CH_B_FINE_TONE 0x2          /* R2 */
#define CH_C_FINE_TONE 0x4          /* R4 */

/* coarse tune registers */
#define CH_A_ROUGH_TONE 0x1         /* R1 */
#define CH_B_ROUGH_TONE 0x3         /* R3 */
#define CH_C_ROUGH_TONE 0x5         /* R5 */

/* volume registers */
#define CH_A_VOLUME 0x8             /* R8 */ 
#define CH_B_VOLUME 0x9             /* R9 */
#define CH_C_VOLUME 0xA             /* RA */


/* mixer and noise */
#define MIXER_REGISTER 0x7          /* R7 */
#define NOISE_PERIOD_REGISTER 0x6   /* R6 */

/* Page 20 of the YM2149 Documentation 

| B7 | B6 | B5 | B4 | B3 | B2 | B1 | B0 |
-----------------------------------------
| B  | A  | C  | B  | A  | C  | B  | A  |
 

 * B0 - B2 = tone
 * B3 - B5 = noise
 * B6 - B7 =  I/O (if both bits are = 0 then Input is selected)

 * When both the noise bit and tone bit are 0, the mixer combines the output.
 * If the noise bit is 0 and the tone bit is 1, the output is a noise signal.
 * If the noise bit is 1 and the tone bit is 0, the output is a tone signal.
 * When both the noise bit and tone bit are 1, there is no output.
*/

#define MIXER_NOTHING 0x3F               /* binary number : 0 0 111 111  */

#define IO_PORT_A_NOISEON_TONEON 0x36    /* binary number : 0 0 110 110  */
#define IO_PORT_A_NOISEON_TONEOFF 0x37   /* binary number : 0 0 110 111  */
#define IO_PORT_A_NOISEOFF_TONEON 0x3E   /* binary number : 0 0 111 110  */

#define IO_PORT_B_NOISEON_TONEON 0x2D   /*  binary number : 0 0 101 101  */
#define IO_PORT_B_NOISEON_TONEOFF 0x2F  /*  binary number : 0 0 101 111  */
#define IO_PORT_B_NOISEOFF_TONEON 0x3D  /*  binary number : 0 0 111 101  */

#define IO_PORT_C_NOISEON_TONEON 0x1B   /*  binary number : 0 0 011 011  */
#define IO_PORT_C_NOISEON_TONEOFF 0x1F  /*  binary number : 0 0 011 111  */
#define IO_PORT_C_NOISEOFF_TONEON 0x3B  /*  binary number : 0 0 111 011  */


/* Page 34 of the YM2149 Documentation */
/* Envelopes may not neccessarily be required */

#define ENVELOPE_FINE_REGISTER 0xB
#define ENVELOPE_ROUGH_REGISTER 0xC
#define ENVELOPE_SHAPE_CONTROL_REGISTER 0xD


/* Envelope shape bit patterns  */

#define SAW_REGULAR 0x8
#define TRIANGLE_PERIOD_INVERSE 0x00
#define TRIANGLE_INVERSE  0xA
#define SAW_PERIOD_INVERSE 0xB
#define SAW_INVERSE 0xC
#define TRIANGLE_PERIOD_REGULAR 0xD
#define TRIANGLE_REGULAR 0xE
#define SAW_PERIOD_REGULAR 0xF


extern volatile char *PSG_reg_select = 0xFF8800;
extern volatile char *PSG_reg_write = 0xFF8802;


typedef enum{
    ch_a,
    ch_b,
    ch_c
} channel;

void write_psg(int reg, UINT8 val);
UINT8 read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, bool tone_on, bool noise_on);
void stop_sound();

void set_noise(int tuning);
void set_envelope(int Env_shape, UINT16 sustain);

#endif