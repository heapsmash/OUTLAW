
	ResetVblankFlag();	 /* reset VBL flag for MyVsync() */
	ScrInit(&game.screen); /* initialize frame buffers */
	ResetTicks();		   /* reset vblank timer */
	ResetSeconds();		   /* reset seconds timer */
	StopSound();		   /* stop all st sounds */
	LoadMenu(&game);	   /* load game menu */
	LoadSplash(&game);	 /* load game splash screen */

	RenderSplash(&game, game.screen.next_buffer);
	MySleep(4);

	player_mode_flag = -11;
	RenderMenu(&game, game.screen.next_buffer);
	while (read_char < 0) /* menu loop */
	{
		if (CheckInputStatus() < 0) /* check ikbd codes */
		{
			read_char = ReadCharNoEcho();
			switch (read_char)
			{
			case UP: /* (KEY W) Or mouse one player game */
				player_mode_flag = 1;
				break;
			case DOWN: /* (KEY S) Or mouse two player game */
				player_mode_flag = 2;
				break;
			}
		}
		RenderMenu(&game, game.screen.next_buffer);
	}

	InitGame(&game);
	Render(&game, game.screen.next_buffer);

	music_time_now = time_now = GetTime();
	time_then = time_now;

	flag_music_on = 1;
	if (flag_music_on) /* For (POSSIBLE) menu selection in future */
	{
		music_time_then = music_time_now;
		StartMusic();
	}

	read_char = -1;
	while (read_char != 27) /* main game loop */
	{
		music_time_now = time_now = GetTime();
		time_elapsed = time_now - time_then;

		if (flag_music_on)
		{
			music_time_elapsed = music_time_now - music_time_then;

			UpdateMusic(music_time_elapsed);

			if (music_time_elapsed >= 20)
				music_time_then = music_time_now;
		}

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

		if (CheckInputStatus() < 0) /* check ikbd codes */
		{
			read_char = ReadCharNoEcho();
			switch (read_char)
			{
			case 119: /* w up */
				EventWalk(UP, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 115: /* s down */
				EventWalk(DOWN, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 97: /* a BACK */
				EventWalk(BACK, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 100: /* d FORWARD */
				EventWalk(FORWARD, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 54: /* NUMPAD 6 SHOOT STRAIGHT */
				EventShoot(STRAIGHT, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 50: /* NUMPAD 2 SHOOT DOWN */
				EventShoot(DOWN, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 56: /* NUMPAD 8 SHOOT UP */
				EventShoot(UP, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 114: /* r RELOAD */
				EventShoot(RELOAD, &game.gun_slinger[PLAYER_ONE]);
				break;
			default:
				break;
			}
		}

		/* computer player movement */

		switch (MyRand() % 200)
		{
		case 0: /* Case UP */
			EventWalk(UP, &game.gun_slinger[PLAYER_TWO]);
			break;
		case 1: /* Case DOWN */
			EventWalk(DOWN, &game.gun_slinger[PLAYER_TWO]);
			break;
		case 2: /* case BACK */
			EventWalk(BACK, &game.gun_slinger[PLAYER_TWO]);
			break;
		case 3: /* case FORWARD */
			EventWalk(FORWARD, &game.gun_slinger[PLAYER_TWO]);
			break;
		case 4: /* case SHOOT STRAIGHT */
			EventShoot(STRAIGHT, &game.gun_slinger[PLAYER_TWO]);
			break;
		case 5: /* case SHOOT DOWN */
			EventShoot(DOWN, &game.gun_slinger[PLAYER_TWO]);
			break;
		case 6: /* case SHOOT UP */
			EventShoot(UP, &game.gun_slinger[PLAYER_TWO]);
			break;
		case 7: /* case RELOAD */
			EventShoot(RELOAD, &game.gun_slinger[PLAYER_TWO]);
			break;
		default:
			break;
		}

		/* update all bullets */
		if (time_elapsed > 3)
		{
			EventMoveBullets(&game.gun_slinger[PLAYER_ONE], &game.gun_slinger[PLAYER_TWO]);
			EventMoveBullets(&game.gun_slinger[PLAYER_TWO], &game.gun_slinger[PLAYER_ONE]);
		}

		/* check if player 2 is dead and update score */

		if (EventPlayerDead(&game.gun_slinger[PLAYER_TWO]))
		{
			game.gun_slinger[PLAYER_TWO].flag_alive = ALIVE;
			EventUpdateScore(&game.gun_slinger[PLAYER_ONE]);
		}

		/* check if player 1 is dead and update score */

		if (EventPlayerDead(&game.gun_slinger[PLAYER_ONE]))
		{
			game.gun_slinger[PLAYER_ONE].flag_alive = ALIVE;
			EventUpdateScore(&game.gun_slinger[PLAYER_TWO]);
		}

		Render(&game, game.screen.next_buffer); /* render the frame */
		time_then = time_now;
	}

	StopSound();							   /* stop all game sound */
	ScrCleanup(&game.screen);				   /* restore original frame buffer */