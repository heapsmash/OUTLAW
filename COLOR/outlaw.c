#include <stdio.h>
#include <osbind.h>
#include <unistd.h>

#include <OUTLAW.H>
#include <RASTER.H>
#include <TYPES.H>
#include <PALLETE.H>
#include <SCREEN.H>
#include <COWBOY.H>

int main(int argc, char *argv[])
{
    Screen screen;
    int height, x_pos, y_pos, read_char, original_colors[16];

    GetColorPallete(original_colors);
    ScrInit(&screen);

    height = sizeof cowboy / sizeof cowboy[0];
    read_char = -1;
    x_pos = y_pos = 0;

    Vsync();
    PlotBitMap(screen.next_buffer, cowboy, x_pos, y_pos, height);
    ScrFlipBuffers(&screen);

    while (read_char != 27)
    {
        if (Cconis() < 0)
        {
            read_char = Cnecin();
            switch (read_char)
            {
            case 119: /* w up */
                y_pos -= 64;
                Vsync();
                ClearScreen(screen.next_buffer);
                Vsync();
                PlotBitMap(screen.next_buffer, cowboy, x_pos, y_pos, height);
                ScrFlipBuffers(&screen);
                break;
            case 115: /* s down */
                y_pos += 64;
                Vsync();
                ClearScreen(screen.next_buffer);
                Vsync();
                PlotBitMap(screen.next_buffer, cowboy, x_pos, y_pos, height);
                ScrFlipBuffers(&screen);
                break;
            case 97: /* a left */
                x_pos -= 64;
                Vsync();
                ClearScreen(screen.next_buffer);
                Vsync();
                PlotBitMap(screen.next_buffer, cowboy, x_pos, y_pos, height);
                ScrFlipBuffers(&screen);
                break;
            case 100: /* d right */
                x_pos += 64;
                Vsync();
                ClearScreen(screen.next_buffer);
                Vsync();
                PlotBitMap(screen.next_buffer, cowboy, x_pos, y_pos, height);
                ScrFlipBuffers(&screen);
                break;
            default:
                break;
            }
        }
    }

    ScrCleanup(&screen); /* resotre operating system */
    LoadColorPallete(original_colors);

    return 0;
}
