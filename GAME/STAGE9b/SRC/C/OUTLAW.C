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

int main(int argc, char *argv[])
{
	Game game;
	int i, n, read_char, flag_music_on, player_mode_flag;
	uint32_t time_then, time_now, time_elapsed, music_time_then, music_time_now, music_time_elapsed;

	long old_ssp = MySuper(0); /* enter privileged mode */

	Vector vbl_orig_vector = InstallVector(VBL_ISR, Vbl);	/* install VBL vector */
	Vector ikbd_orig_vector = InstallVector(IKBD_ISR, Ikbd); /* install IKBD vector */

	while (BREAK_CODE(g_action) != ESC)
	{
		printf("action -> %x\n", g_action);
		printf("delta_x -> %d\n", g_mouse_delta_x);
		printf("delta_y -> %d\n", g_mouse_delta_y);
	}

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
