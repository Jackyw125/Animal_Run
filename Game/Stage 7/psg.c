#include "psg.h"

#include <osbind.h>
#include <stdio.h>


/*
 * File: psg.c
 * Stage 7
 * Date: November 16, 2024
 * Author: Both members
 * Prof: Paul Pospisil
 * --------------
 * The purpose of this file is to write values to the register, adjusting both the tone and volume of the channel. 
 * Additionally, it enables the specific channel for music playback. Enabling the channel also facilitates concurrent 
 * playback of noise and tone if required, or vice versa.
 *
 * Team Members:
 * - Ochihai Omuha
 * - Jacky On
 * 
 */


/*
 * Function Name: write_psg
 * -------------------------
 * Purpose: Write a value to a specified register of the Programmable Sound Generator (PSG) chip.
 *
 * Input Parameters:
 *   int reg - The register address to write to on the PSG chip. Should be in the range 0 to 15.
 *   UINT8 val - The value to write to the specified register. Should be in the range 0 to 255.
 *
 * Output Parameters:
 *   The function modifies the PSG chip by writing the specified value to the specified register.
 *   There are no explicit output parameters.
 *
 * Return Value: The function has no return value.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function expects valid register addresses and values provided by the caller.
 *   - The function utilizes supervisor mode (or equivalent privileged mode) to access hardware registers.
 */ 

void write_psg(int reg, UINT8 val)
{	
		long old_ssp = Super(0);
           
		if (reg >= 0 && reg <= 15 && val >= 0 && val <= 255)
	{
		        *PSG_reg_select = reg;
                        *PSG_reg_write = val;				
        }
		        Super(old_ssp);
}

/*
 * Function Name: read_psg
 *
 * Purpose: Read the value from a specified register of the Programmable Sound Generator (PSG) chip.
 *
 * Input Parameters:
 *   int reg - The register address to read from on the PSG chip. Should be in the range 0 to 15.
 *
 * Output Parameters:
 *   There are no explicit output parameters.
 *
 * Return Value: 
 *   int - The value read from the specified register. Returns -1 if the register address is invalid.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function expects a valid register address provided by the caller.
 *   - The function utilizes supervisor mode (or equivalent privileged mode) to access hardware registers.
 */

UINT8 read_psg(int reg)
{
	   long old_ssp;
	   UINT8 val = -1;

        if (reg >= 0 && reg <= 15){	
			
                old_ssp = Super(0);
                
                *PSG_reg_select = reg;
                val = *PSG_reg_select;
                        
                Super(old_ssp);
        }
        return val;
}

/*
 * Function Name: set_tone
 *
 * Purpose: Set the tone for a specified channel on the Programmable Sound Generator (PSG) chip.
 *
 * Input Parameters:
 *   int channel - The channel for which the tone needs to be set (ch_a, ch_b, or ch_c).
 *   int tuning - The tuning value to set the tone for the specified channel.
 *
 * Output Parameters:
 *   The function modifies the PSG chip by setting the tone for the specified channel.
 *   There are no explicit output parameters.
 *
 * Return Value: The function has no return value.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function expects valid channel identifiers and tuning values provided by the caller.
 *   - The function utilizes another function `write_psg` to write values to the PSG chip registers.
 */


void set_tone(int channel, int tuning)
{
        /* Split 12-bit tuning into 8-bit and 4-bit components */
        int fine_tune = tuning & 0x00FF;             /* LSB */
        int coarse_tune = (tuning & 0x0FF0) >> 8;   /* MSB */
        switch (channel)
        {
        case ch_a:
                write_psg(CH_A_FINE_TONE, fine_tune);
                write_psg(CH_A_ROUGH_TONE, coarse_tune);
                break;
        case ch_b:
                write_psg(CH_B_FINE_TONE, fine_tune);
                write_psg(CH_B_ROUGH_TONE, coarse_tune);
                break;
        case ch_c:
                write_psg(CH_C_FINE_TONE, fine_tune);
                write_psg(CH_C_ROUGH_TONE, coarse_tune);
                break;
        
        default:
          break;
        
        }
}

/*
 * Function Name: set_volume
 *
 * Purpose: Set the volume for a specified channel on the Programmable Sound Generator (PSG) chip.
 *
 * Input Parameters:
 *   int channel - The channel for which the volume needs to be set (ch_a, ch_b, or ch_c).
 *   int volume - The volume level to set for the specified channel.
 *
 * Output Parameters:
 *   The function modifies the PSG chip by setting the volume for the specified channel.
 *   There are no explicit output parameters.
 *
 * Return Value: The function has no return value.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function expects valid channel identifiers and volume levels provided by the caller.
 *   - The function utilizes another function `write_psg` to write values to the PSG chip registers.
 */ 

void set_volume(int channel, int volume)
{
		/* only need the first 5 bits */
		UINT8 vol = volume & 0x001F; 
	
        switch (channel)
        {
        case ch_a:
                write_psg(CH_A_VOLUME, vol);
                break;
        case ch_b:
                write_psg(CH_B_VOLUME, vol);
                break;
        case ch_c:
                write_psg(CH_C_VOLUME, vol);
                break;
        }
}

/*
 * Function Name: enable_channel
 *
 * Purpose: Enable or disable a channel on the Programmable Sound Generator (PSG) chip, controlling tone and noise.
 *
 * Input Parameters:
 *   int channel - The channel to enable or disable (ch_a, ch_b, or ch_c).
 *   int tone_on - Flag indicating whether tone should be enabled (true) or disabled (false).
 *   int noise_on - Flag indicating whether noise should be enabled (true) or disabled (false).
 *
 * Output Parameters:
 *   The function modifies the PSG chip by enabling or disabling the specified channel and controlling tone and noise.
 *   There are no explicit output parameters.
 *
 * Return Value: The function has no return value.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function expects valid channel identifiers provided by the caller.
 *   - The function utilizes another function `write_psg` to write values to the PSG chip registers.
 *   - The function also utilizes another function `read_psg` to read values from the PSG chip registers.
 */ 


void enable_channel(int channel, bool noise_on, bool tone_on)
{       
       /* Retain the existing value in the mixer by default */
        UINT16 mixerControl;
        
        switch (channel)
        {
                case ch_a:
                        if (tone_on == 1 && noise_on == 0)
                        {
                                mixerControl = IO_PORT_A_NOISEON_TONEOFF;
                        }
                        else if (noise_on == 1 && tone_on == 0)
                        {
                               mixerControl = IO_PORT_A_NOISEOFF_TONEON;
                        }
                        else if (tone_on == 1 && noise_on == 1)
                        {
                                mixerControl = (IO_PORT_A_NOISEOFF_TONEON && IO_PORT_A_NOISEON_TONEOFF);
                        }
                        break;
                
                case ch_b:
                        if (tone_on == 1 && noise_on == 0)
                        {
                                mixerControl = IO_PORT_B_NOISEON_TONEOFF;
                        }
                        else if (noise_on == 1 && tone_on == 0)
                        {
                                mixerControl = IO_PORT_B_NOISEOFF_TONEON;
                        }
                        else if (tone_on == 1 && noise_on == 1)
                        {
                                mixerControl = (IO_PORT_B_NOISEOFF_TONEON && IO_PORT_B_NOISEON_TONEOFF);
                        }
                        break;
                
                case ch_c:
                        if (tone_on == 1 && noise_on == 0)
                        {
                                mixerControl = IO_PORT_C_NOISEON_TONEOFF;
                        }
                        if (noise_on == 1 && tone_on == 0)
                        {
                                mixerControl = IO_PORT_C_NOISEOFF_TONEON;
                        }
                        if (tone_on == 1 && noise_on == 1)
                        {
                                mixerControl = (IO_PORT_C_NOISEOFF_TONEON && IO_PORT_C_NOISEON_TONEOFF);
                        }
                        break;
                
        }
		write_psg(MIXER_REGISTER, mixerControl);
		
		
}

/*
 * Function Name: stop_sound
 *
 * Purpose: Stop all sounds by setting the volume of all channels to 0.
 *
 * Input Parameters: None
 *
 * Output Parameters:
 *   The function modifies the PSG chip by setting the volume of all channels to 0.
 *   There are no explicit output parameters.
 *
 * Return Value: The function has no return value.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function utilizes another function `write_psg` to write values to the PSG chip registers.
 */ 

void stop_sound()
{
	
	/* turn all channels off in the mixer*/
	write_psg(MIXER_REGISTER, MIXER_NOTHING);
	
	/*disable noise bits */
	write_psg(NOISE_PERIOD_REGISTER, 0x00);
	
	/*disable envelope bits */
	write_psg(ENVELOPE_FINE_REGISTER, 0x00);
	write_psg(ENVELOPE_ROUGH_REGISTER, 0x00);
	write_psg(ENVELOPE_SHAPE_CONTROL_REGISTER, 0x00);
	
	/*disable the volume in all channels*/
	write_psg(CH_A_VOLUME,0);
	write_psg(CH_B_VOLUME,0);
	write_psg(CH_C_VOLUME,0);


}


/*
 * Function Name: set_noise
 *
 * Purpose: Set the noise period for the noise generator on the Programmable Sound Generator (PSG) chip.
 *
 * Input Parameters:
 *   int tuning - The tuning value to set for the noise period.
 *
 * Output Parameters:
 *   The function modifies the PSG chip by setting the noise period.
 *   There are no explicit output parameters.
 *
 * Return Value: The function has no return value.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function expects a valid tuning value provided by the caller.
 *   - The function utilizes another function `write_psg` to write the tuning value to the PSG chip register.
 */ 


void set_noise(int tuning)
{
		/* only need the first 5 bits */
		UINT8 tune = tuning & 0x001F; 
		
        write_psg(NOISE_PERIOD_REGISTER, tune);
}

/*
 * Function Name: set_envelope
 *
 * Purpose: Set the envelope shape and sustain level for the envelope generator on the Programmable Sound Generator (PSG) chip.
 *
 * Input Parameters:
 *   int Env_shape - The shape of the envelope to set (saw, triangle, saw_inv, saw_period, triangle_inv, triangle_period, triangle_inv_period).
 *   UINT16 sustain - The sustain level to set for the envelope generator.
 *
 * Output Parameters:
 *   The function modifies the PSG chip by setting the envelope shape and sustain level.
 *   There are no explicit output parameters.
 *
 * Return Value: The function has no return value.
 *
 * Assumptions/Limitations/Known Bugs:
 *   - The function assumes the availability of a PSG chip.
 *   - It assumes that the PSG chip is accessible via memory-mapped registers.
 *   - The function expects a valid envelope shape and sustain level provided by the caller.
 *   - The function utilizes another function `write_psg` to write values to the PSG chip registers.
 */

void set_envelope(int Env_shape, UINT16 sustain)
{
        int val;
        write_psg(ENVELOPE_FINE_REGISTER, sustain);
        write_psg(ENVELOPE_ROUGH_REGISTER, sustain);

        switch (Env_shape)
        {
        case 0:
                val = SAW_REGULAR;
                break;
        case 1:
                val = TRIANGLE_PERIOD_INVERSE;
                break;
        case 2:
                val = TRIANGLE_INVERSE;
                break;
        case 3:
                val = SAW_PERIOD_INVERSE;
                break;
        case 4:
                val = SAW_INVERSE;
                break;
        case 5:
                val = TRIANGLE_PERIOD_REGULAR;
                break;
        case 6:
                val = TRIANGLE_REGULAR;
                break;
        case 7:
		val = SAW_PERIOD_REGULAR;
		break;
		}
	write_psg(0xD, val);
}






