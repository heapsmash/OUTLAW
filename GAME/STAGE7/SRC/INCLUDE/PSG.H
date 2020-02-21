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
                                    /* IOB IOC | C B A | C B A */
#define IO_A_NOISEON_TONEON 0x36    /*   0   0   1 1 0   1 1 0 */ 
#define IO_A_NOISEON_TONEOFF 0x37   /*   0   0   1 1 0   1 1 1 */ 
#define IO_A_NOISEOFF_TONEON 0x3E   /*   0   0   1 1 1   1 1 0 */ 

#define IO_B_NOISEON_TONEON 0x2D    /*   0   0   1 0 1   1 0 1 */ 
#define IO_B_NOISEON_TONEOFF 0x2F   /*   0   0   1 0 1   1 1 1 */ 
#define IO_B_NOISEOFF_TONEON 0x3D   /*   0   0   1 1 1   1 0 1 */ 

#define IO_C_NOISEON_TONEON 0x1B    /*   0   0   0 1 1   0 1 1 */ 
#define IO_C_NOISEON_TONEOFF 0x1F   /*   0   0   0 1 1   1 1 1 */ 
#define IO_C_NOISEOFF_TONEON 0x3B   /*   0   0   1 1 1   0 1 1 */ 

#define IO_OFF 0x3F                 /*   0   0   1 1 1   1 1 1 */ 

void SetEnvelope(int shape, unsigned int sustain);
void SetNoise(int tuning);
void StopSound(void);
void EnableChannel(int channel, int tone_on, int noise_on);
void SetVolume(int channel, int volume);
void SetTone(int channel, int tuning);
uint8_t ReadPsg(int reg);
void WritePsg(int reg, uint8_t val);


#endif /* PSG_H */ 
