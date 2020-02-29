/*
 * Michael S. Walker <mwalk762@mtroyal.ca>
 *	    _    _
 *       | |  | |	OUTLAW. 
 *      -| |  | |- 
 *  _    | |- | |
 *-| |   | |  | |- 	
 * |.|  -| ||/  |
 * | |-  |  ___/ 
 *-|.|   | | |
 * |  \_|| |
 *  \____  |
 *   |   | |- 
 *       | |
 *      -| |
 *       |_| Copyleft !(c) 2020 All Rights Unreserved in all Federations, including Alpha Centauris.
 */

#include <OUTLAW.H>
#include <INPUT.H>
#include <MODEL.H>
#include <EVENTS.H>
#include <RENDERER.H>
#include <SYSCALLS.H>
#include <SCREEN.H>
#include <UTIL.H>
#include <PSG.H>
#include <MUSIC.H>
#include <INIT.H>
#include <RASTER.H>
#include <ISR.H>
#include <VBL.H>
#include <BITMAP/SPL_SCRN.C>
#include <BITMAP/MENU.C>

#include <stdio.h>
#include <osbind.h>

const uint8_t mouse[] = {
	0xaa,
	0x55,
	0xaa,
	0x55,
	0xaa,
	0x55,
	0xaa,
	0x55,
};

int main(int argc, char *argv[])
{
	Game game;
	SCANCODE tmp;

	int i, n, read_char, flag_music_on, player_mode_flag;
	uint32_t time_then, time_now, time_elapsed, music_time_then, music_time_now, music_time_elapsed;

	long old_ssp = MySuper(0);								 /* enter privileged mode */
	Vector vbl_orig_vector = InstallVector(VBL_ISR, Vbl);	/* install VBL vector */
	Vector ikbd_orig_vector = InstallVector(IKBD_ISR, Ikbd); /* install IKBD vector */
	void *fb = Physbase();

	game.mouse.sprite.bitmap.current_image = mouse;
	game.mouse.sprite.bitmap.height = (sizeof(mouse) / sizeof mouse[0]);
	game.mouse.sprite.bitmap.raster.Draw = Rast8Draw;
	game.mouse.sprite.bitmap.raster.Clear = Rast8Clear;
	game.mouse.sprite.bitmap.raster.Alpha = Rast8Alpha;

	FifoInit();
	while (1)
		if (CheckInputStatus() < 0)
			printf("0x%x\n", ReadCharNoEcho());

	/* 
	while (1)
	{
		if (g_click == ON)
		{
			g_click = OFF;
		}

		g_delta_x = WrapInteger(g_delta_x, 0, 640);
		g_delta_y = WrapInteger(g_delta_y, 0, 400);

		game.mouse.sprite.x_pos = g_delta_x;
		game.mouse.sprite.y_pos = g_delta_y;

		ClearScreen(fb);
		game.mouse.sprite.bitmap.raster.Draw(fb, &game.mouse.sprite);
	}
	*/

	InstallVector(IKBD_ISR, ikbd_orig_vector); /* install old IKBD vector */
	InstallVector(VBL_ISR, vbl_orig_vector);   /* install old ISR vector */
	MySuper(old_ssp);						   /* exit privileged mode */

	return 0;
}

/*-------------------------------------------- LoadSplash -----
|  Function LoadSplash
|
|  Purpose: Load the intro screen
|
|  Parameters: game
|
|  Returns:
*-------------------------------------------------------------------*/

void LoadSplash(Game *game)
{
	game->splash.sprite.bitmap.current_image = splscrn;
	game->splash.sprite.bitmap.raster.Draw = PrintScreen;
	game->splash.sprite.bitmap.height = (sizeof(splscrn) / (sizeof splscrn[0]));
}

/*-------------------------------------------- LoadMenu -----
|  Function LoadMenu
|
|  Purpose: Load the menu screen
|
|  Parameters: game
|
|  Returns:
*-------------------------------------------------------------------*/

void LoadMenu(Game *game)
{
	game->menu.sprite.bitmap.current_image = menu;
	game->menu.sprite.bitmap.raster.Draw = PrintScreen;
	game->menu.sprite.bitmap.height = (sizeof(menu) / (sizeof menu[0]));
}
