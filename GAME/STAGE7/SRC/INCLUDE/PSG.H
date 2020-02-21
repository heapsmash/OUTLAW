#ifndef PSG_H
#define PSG_H
#include <TYPES.H> /* for type t */ 

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

#define MAKE_TONE(f,r) (((f) << 4) | (r))
#define ROUGH_MASK(a) ((a) & 0x000F)
#define FINE_MASK(a) (((a) & 0x0FF0) >> 4)

#define R0 0x0
#define R1 0x1
#define R2 0x2
#define R3 0x3
#define R4 0x4
#define R5 0x5
#define R6 0x6
#define R7 0x7
#define R8 0x8
#define R9 0x9
#define RA 0xA
#define RB 0xB
#define RC 0xC
#define RD 0xD
#define RE 0xE
#define RF 0xF

void write_psg(int reg, uint8_t val);
uint8_t read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(int channel, int tone_on, int noise_on);
void stop_sound(void);
void set_noise(int tuning);
void set_envelope(int shape, unsigned int sustain);

#endif /* PSG_H */ 
