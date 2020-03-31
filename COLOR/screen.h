#ifndef SCREEN_H
#define SCREEN_H

#include <TYPES.H>

#define SCREEN_SIZE 32000
#define NUM_FRAME_BUFFERS 2
#define FRAMEBUFFER_PADDING_LEN 0x100

typedef struct _Screen
{
	int current_fb_index;

	void *next_buffer;
	void *framebuffs[NUM_FRAME_BUFFERS];
	void *orig_framebuffer;
} Screen;

void ScrCleanup(Screen *screen);
void ScrSetScreenBuffer(uint8_t *scrbuf);
uint8_t *ScrGetScreenBuffer(void);
void ScrFlipBuffers(Screen *screen);
void ScrInit(Screen *screen);

#endif /* SCREEN_H */