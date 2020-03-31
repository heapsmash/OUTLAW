#include <PALLETE.H>
#include <osbind.h>

void LoadColorPallete(int colors[16])
{
	long old_sup = Super(0);
	int index;
	int *firstAddress = (0x00FF8240);
	for (index = 0; index < 16; index++)
	{
		*firstAddress = colors[index];
		firstAddress++;
	}
	Super(old_sup);
}

void GetColorPallete(int colors[16])
{
	long old_sup = Super(0);
	int index;
	int *firstAddress = (0x00FF8240);
	for (index = 0; index < 16; index++)
	{
		colors[index] = *firstAddress;
		firstAddress++;
	}
	Super(old_sup);
}
