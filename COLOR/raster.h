#ifndef RASTER_H
#define RASTER_H

#include <TYPES.H>

void PlotBitMap(uint16_t *base, uint16_t map[], int x, int y, int height);
void SetVideoBase(uint32_t *frameBuffer);
void ClearScreen(uint16_t *base);
uint32_t *GetVideoBase(void);

#endif /* RASTER_H */
