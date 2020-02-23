#include <TYPES.H>
#include <SCREEN.H>
#include <UTIL.H>
#include <RASTER.H> /* for ClearScreen() GetScreenBuffer() SetScreenBuffer() */

uint8_t g_framebuffers[NUM_FRAME_BUFFERS][SCREEN_SIZE + FRAMEBUFFER_PADDING_LEN];

void ScrInit(Screen *screen)
{
    int i;

    screen->current_fb_index = 0;
    screen->orig_framebuffer = GetVideoBase(); /* save orig screen */

    for (i = 0; i != NUM_FRAME_BUFFERS; i++)
    {
        screen->framebuffs[i] = (uint8_t *)addr_roundup(g_framebuffers[i], 8);
        ClearScreen(screen->framebuffs[i]);
    }

    screen->next_buffer = screen->framebuffs[screen->current_fb_index];
    ScrFlipBuffers(screen);
}

void ScrFlipBuffers(Screen *screen)
{
    SetVideoBase(screen->next_buffer);
    screen->current_fb_index ^= (screen->current_fb_index + 1) % NUM_FRAME_BUFFERS;
    screen->next_buffer = screen->framebuffs[screen->current_fb_index];
}

void ScrCleanup(Screen *screen)
{
    SetVideoBase(screen->orig_framebuffer);
}
