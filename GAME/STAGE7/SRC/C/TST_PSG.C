#include <PSG.H> 
#include <osbind.h> /* For super */ 
#include <stdio.h> 

void TestTone(void); 
void TestVolume(void); 

int main(int argc, char *argv[])
{
	long old_ssp = Super(0);

	TestTone(); 
	TestVolume(); 
	Super(old_ssp);

	return 0;
}

void TestTone(void) 
{
	int fine_tone = 0x11;
	int rough_tone = 0x02;
	int tone = MAKE_TONE(fine_tone, rough_tone);
	SetTone(CHANNEL_A, tone); 

	fine_tone = 0x33;
	rough_tone = 0x04;
	tone = MAKE_TONE(fine_tone, rough_tone);
	SetTone(CHANNEL_B, tone); 

	fine_tone = 0x55;
	rough_tone = 0x06; 
	tone = MAKE_TONE(fine_tone, rough_tone);
	SetTone(CHANNEL_C, tone); 

	printf("FINE TONE RO: 0x%x\n", ReadPsg(R0)); 
	printf("ROUGH TONE R1: 0x%x\n", ReadPsg(R1)); 

	printf("FINE TONE R2: 0x%x\n", ReadPsg(R2)); 
	printf("ROUGH TONE R3: 0x%x\n", ReadPsg(R3)); 

	printf("FINE TONE R4: 0x%x\n", ReadPsg(R4)); 
	printf("ROUGH TONE R5: 0x%x\n", ReadPsg(R5)); 
}

void TestVolume(void) 
{

	SetVolume(CHANNEL_A, 0xF); 
	printf("VOLMUE OF R8: 0x%x\n", ReadPsg(R8));

	SetVolume(CHANNEL_B, 0xE); 
	printf("VOLMUE OF R8: 0x%x\n", ReadPsg(R9));
	
	SetVolume(CHANNEL_C, 0xD); 
	printf("VOLMUE OF R8: 0x%x\n", ReadPsg(RA));

}