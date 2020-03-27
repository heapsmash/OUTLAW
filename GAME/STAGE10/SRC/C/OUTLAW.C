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

int main(int argc, char *argv[])
{
	Game game;
	SCANCODE read_char;

	int i, n, player_mode_flag;
	uint32_t time_then, time_now, time_elapsed, music_time_then, music_time_now, music_time_elapsed;

	long old_ssp = MySuper(0);								 /* enter privileged mode */
	Vector vbl_orig_vector = InstallVector(VBL_ISR, Vbl);	 /* install VBL vector */
	Vector ikbd_orig_vector = InstallVector(IKBD_ISR, Ikbd); /* install IKBD vector */

	FlushIKBD();		   /* flush the keyboard */
	FifoInit();			   /* init circular keyboard buffer */
	ResetVblankFlag();	   /* reset VBL flag for MyVsync() */
	ScrInit(&game.screen); /* initialize frame buffers */
	ResetTicks();		   /* reset vblank timer */
	ResetSeconds();		   /* reset seconds timer */
	LoadMenu(&game);	   /* load game menu */
	LoadSplash(&game);	   /* load game splash screen */
	InitMouse(&game);	   /* init mouse */

	RenderSplash(&game, game.screen.next_buffer);
	MySleep(4);

	game.num_players = -1;
	RenderMenu(&game, game.screen.next_buffer);

	while (game.num_players == -1) /* menu loop */
	{
		EventUpdateMouse(&game.mouse);
		EventMenuClick(&game);
		RenderMenu(&game, game.screen.next_buffer);
	}

	MouseOff();		 /* disable the mouse */
	InitGame(&game); /* initialize main game loop */
	Render(&game, game.screen.next_buffer);

	/* initialize timers */
	music_time_now = time_now = GetTime();
	time_then = time_now;
	music_time_then = music_time_now;

	StartMusic();

	read_char = -1;
	while (read_char != ALPHA_Q) /* main game loop */
	{
		/* update timers */
		music_time_now = time_now = GetTime();
		time_elapsed = time_now - time_then;
		music_time_elapsed = music_time_now - music_time_then;

		UpdateMusic(music_time_elapsed);

		/* reset music timer */
		if (music_time_elapsed >= 15)
			music_time_then = music_time_now;

		/* Player 1 wins */
		if (EventWin(game.gun_slinger[PLAYER_ONE]))
		{
			RenderWin(&game.screen, game.screen.next_buffer, 1);
			MySleep(5);
			InitGame(&game);
			Render(&game, game.screen.next_buffer);
		}

		/* Player 2 wins */
		if (EventWin(game.gun_slinger[PLAYER_TWO]))
		{
			RenderWin(&game.screen, game.screen.next_buffer, 2);
			MySleep(5);
			InitGame(&game);
			Render(&game, game.screen.next_buffer);
		}

		/* player movement */
		if (CheckInputStatus() < 0)
		{
			read_char = ReadCharNoEcho();
			EventMovePlayer(&game.gun_slinger[PLAYER_ONE], read_char);
		}

		/* computer player movement */
		EventMoveComputerPlayer(&game.gun_slinger[PLAYER_TWO]);

		/* update all bullets */
		if (time_elapsed > 3)
		{
			EventMoveBullets(&game.gun_slinger[PLAYER_ONE], &game.gun_slinger[PLAYER_TWO]);
			EventMoveBullets(&game.gun_slinger[PLAYER_TWO], &game.gun_slinger[PLAYER_ONE]);
		}

		/* check if player 2 is dead and update score */
		if (EventPlayerDead(&game.gun_slinger[PLAYER_TWO]))
			EventUpdateScore(&game.gun_slinger[PLAYER_ONE]);

		/* check if player 1 is dead and update score */
		if (EventPlayerDead(&game.gun_slinger[PLAYER_ONE]))
			EventUpdateScore(&game.gun_slinger[PLAYER_TWO]);

		/* render the frame */
		Render(&game, game.screen.next_buffer);
		time_then = time_now;
	}

	StopSound();							   /* stop all game sound */
	ScrCleanup(&game.screen);				   /* restore original frame buffer */
	FlushIKBD();							   /* flush the keyboard */
	MouseOn();								   /* re enable the mouse */
	InstallVector(IKBD_ISR, ikbd_orig_vector); /* install old IKBD vector */
	InstallVector(VBL_ISR, vbl_orig_vector);   /* install old ISR vector */

	MySuper(old_ssp); /* exit privileged mode */

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
