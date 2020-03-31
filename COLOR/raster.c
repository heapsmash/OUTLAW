#include <TYPES.H>
#include <RASTER.H>
#include <osbind.h> /* for Super() */

uint32_t *GetVideoBase(void)
{
	long old_ssp = Super(0);
	uint8_t frameHi, frameMi;
	uint32_t frameBuffer = 0x0L;
	uint8_t *frame = (uint8_t *)0xFFFF8201;

	frameHi = *frame;

	frame = (uint8_t *)0xFFFF8203;

	frameMi = *frame;

	frameBuffer = ((uint32_t)frameHi << 16);
	frameBuffer |= ((uint32_t)frameMi << 8);

	Super(old_ssp);
	return (uint32_t *)frameBuffer;
}

void SetVideoBase(uint32_t *frameBuffer)
{
	uint8_t frameMi;
	uint8_t frameHi;
	uint8_t *p_frameMi;
	uint8_t *p_frameHi;

	long old_ssp = Super(0);

	frameMi = (uint8_t)((uint32_t)frameBuffer >> 8);
	frameHi = (uint8_t)((uint32_t)frameBuffer >> 16);

	p_frameHi = (uint8_t *)0xFF8201;
	p_frameMi = (uint8_t *)0xFF8203;
	*p_frameHi = frameHi;
	*p_frameMi = frameMi;

	Super(old_ssp);
}

void ClearScreen(uint16_t *base)
{
	int index;

	uint16_t map[] = {0xffff, 0xffff, 0xffff, 0xffff};

	for (index = 0; index < 16000; index++)
	{
		*base = map[index % 4];
		base++;
	}
}

void PlotBitMap(uint16_t *base, uint16_t map[], int x, int y, int height)
{
	int i, y_offset, x_diff, y_diff;
	int offset;
	uint16_t *fb = base;

	y_offset = 320 >> 4;

	x_diff = (x & 0x20);
	x += (x_diff > 32) ? x_diff : -x_diff;

	for (i = 0; i < height; i += 4)
	{
		fb[((i + y) * y_offset) + (x >> 4)] = map[i];
		fb[((i + y) * y_offset) + ((x + 16) >> 4)] = map[i + 1];
		fb[((i + y) * y_offset) + ((x + 32) >> 4)] = map[i + 2];
		fb[((i + y) * y_offset) + ((x + 48) >> 4)] = map[i + 3];
	}
}
