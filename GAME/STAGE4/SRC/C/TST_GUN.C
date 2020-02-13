#include <MODEL.H>
#include <EVENTS.H>
#include <RASTER.H>
#include <osbind.h>

int main(int argc, char *argv[])
{
	Game game;
	int read_char = -1;
	void *base = Physbase();
	MDLInitGameStates(&game);
	ClearScreen(base);

	while (read_char != 27)
	{
		/* EventMoveBullets(&game.gun_slinger[PLAYER_ONE], &game.gun_slinger[PLAYER_TWO]); */
		if (Cconis() < 0) /* check ikbd codes */
		{
			read_char = Cnecin();
			switch (read_char)
			{
			case 119: /* w up */
				game.gun_slinger[PLAYER_ONE].sprite.bitmap.raster.Alpha(base, &game.gun_slinger[PLAYER_ONE].sprite);
				EventWalk(UP, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 115: /* s down */
				game.gun_slinger[PLAYER_ONE].sprite.bitmap.raster.Alpha(base, &game.gun_slinger[PLAYER_ONE].sprite);
				EventWalk(DOWN, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 97: /* a left */
				game.gun_slinger[PLAYER_ONE].sprite.bitmap.raster.Alpha(base, &game.gun_slinger[PLAYER_ONE].sprite);
				EventWalk(BACK, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 100: /* d right */
				game.gun_slinger[PLAYER_ONE].sprite.bitmap.raster.Alpha(base, &game.gun_slinger[PLAYER_ONE].sprite);
				EventWalk(FORWARD, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 54: /* NUMPAD 6 shoot forward */
				game.gun_slinger[PLAYER_ONE].cylinder.sprite.bitmap.raster.Clear(base, &game.gun_slinger[PLAYER_ONE].cylinder.sprite);
				game.gun_slinger[PLAYER_ONE].sprite.bitmap.raster.Alpha(base, &game.gun_slinger[PLAYER_ONE].sprite);
				EventShoot(STRAIGHT, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 50: /* NUMPAD 2 shoot down */
				game.gun_slinger[PLAYER_ONE].cylinder.sprite.bitmap.raster.Clear(base, &game.gun_slinger[PLAYER_ONE].cylinder.sprite);
				game.gun_slinger[PLAYER_ONE].sprite.bitmap.raster.Alpha(base, &game.gun_slinger[PLAYER_ONE].sprite);
				EventShoot(DOWN, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 56: /* NUMPAD 8 shoot up */
				game.gun_slinger[PLAYER_ONE].cylinder.sprite.bitmap.raster.Clear(base, &game.gun_slinger[PLAYER_ONE].cylinder.sprite);
				game.gun_slinger[PLAYER_ONE].sprite.bitmap.raster.Alpha(base, &game.gun_slinger[PLAYER_ONE].sprite);
				EventShoot(UP, &game.gun_slinger[PLAYER_ONE]);
				break;
			case 114: /* r RELOAD */
				game.gun_slinger[PLAYER_ONE].cylinder.sprite.bitmap.raster.Clear(base, &game.gun_slinger[PLAYER_ONE].cylinder.sprite);
				EventShoot(RELOAD, &game.gun_slinger[PLAYER_ONE]);
				break;
			default:
				break;
			}
		}

		EventMoveBullets(&game.gun_slinger[PLAYER_ONE], &game.gun_slinger[PLAYER_TWO]);
		Render(&game, base);
	}
	return 0;
}