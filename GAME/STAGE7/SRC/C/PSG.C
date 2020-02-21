#include <PSG.H> 

/* 
 * Writes the given byte value (0-255) to the given PSG register (0-15). This is a helper routine to be
 * used by the other functions in this module.
 */

void write_psg(int reg, uint8_t val)
{

}

/* 
 * useful for testing purposes.
 */

uint8_t read_psg(int reg)
{

}

/* 
 * Loads the tone registers (coarse and fine) for the given channel (0=A, 1=B, 2=C) with the given
 * 12-bit tuning.
 */

void set_tone(int channel, int tuning)
{

}

/* 
 * Loads the volume register for the given channel.
 */

void set_volume(int channel, int volume)
{

}

/* 
 * Turns the given channel’s tone/noise signals on/off (0=off, 1=on).
 */

void enable_channel(int channel, int tone_on, int noise_on)
{

}

/* 
 * Silences all PSG sound production.
 */

void stop_sound(void)
{

}

/*
 * Loads the noise register with the given tuning.
 */

void set_noise(int tuning)
{

}

/* 
 * Loads the PSG envelope control registers with the given envelope shape and
 * 16-bit sustain.
 */

void set_envelope(int shape, unsigned int sustain)
{

}
