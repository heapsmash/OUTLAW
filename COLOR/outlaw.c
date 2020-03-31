#include <stdio.h>
#include <osbind.h>
#include <unistd.h>

#include <OUTLAW.H>
#include <RASTER.H>
#include <TYPES.H>
#include <PALLETE.H>
#include <COWBOY.H>

int main(int argc, char *argv[])
{
    int height, x_pos, y_pos, read_char, original_colors[16];
    uint16_t *base = (uint16_t *)GetVideoBase();

    GetColorPallete(original_colors);
    ClearScreen(base);

    height = sizeof cowboy / sizeof cowboy[0];
    read_char = -1;
    x_pos = y_pos = 0;

    ClearScreen(base);
    Vsync();
    PlotBitMap(base, cowboy, x_pos, y_pos, height);
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
                ClearScreen(base);
                Vsync();
                PlotBitMap(base, cowboy, x_pos, y_pos, height);
                break;
            case 115: /* s down */
                y_pos += 64;
                Vsync();
                ClearScreen(base);
                Vsync();
                PlotBitMap(base, cowboy, x_pos, y_pos, height);
                break;
            case 97: /* a left */
                x_pos -= 64;
                Vsync();
                ClearScreen(base);
                Vsync();
                PlotBitMap(base, cowboy, x_pos, y_pos, height);
                break;
            case 100: /* d right */
                x_pos += 64;
                Vsync();
                ClearScreen(base);
                Vsync();
                PlotBitMap(base, cowboy, x_pos, y_pos, height);
                break;
            default:
                break;
            }
        }
    }

    LoadColorPallete(original_colors);
    return 0;
}
