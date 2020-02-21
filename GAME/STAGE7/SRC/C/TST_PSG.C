#include <PSG.H> 
#include <osbind.h> /* For super */ 
#include <stdio.h> 
int main(int argc, char *argv[])
{
	int fine_tone = 0xAA;
	int rough_tone = 0x0F; 
	int tone = MAKE_TONE(fine_tone, rough_tone);
	long old_ssp = Super(0);

	set_tone(CHANNEL_A, tone); 

	printf("FINE TONE RO: %x\n", read_psg(R0)); 
	printf("ROUGH TONE R1: %x\n", read_psg(R1)); 

	Super(old_ssp);

	return 0;
}
