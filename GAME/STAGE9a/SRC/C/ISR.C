#include <ISR.H>

int g_seconds;
long g_ticks;

/*-------------------------------------------- InstallVector -----
|  Function InstallVector
|
|  Purpose: Install interupt vector
|
|  Parameters: num vector # to install, pointer to vector function to save. 
|
|  Returns:
*-------------------------------------------------------------------*/

Vector InstallVector(int num, Vector vector)
{
	Vector orig;
	Vector *vectp = (Vector *)((long)num << 2);
	/*	long old_ssp = Super(0); */

	orig = *vectp;
	*vectp = vector;

	/*	Super(old_ssp); */
	return orig;
}

void do_VBL_ISR(void)
{
	g_ticks += 1;

	if (g_ticks % 70 == 0)
		g_seconds++;
}

long MyVblank(void)
{
	return g_ticks;
}

int GetSeconds(void)
{
	return g_seconds;
}

void ResetSeconds(void)
{
	g_seconds = 0;
}

void ResetTicks(void)
{
	g_ticks = 0;
}