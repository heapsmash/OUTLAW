#include <RENDERER.H>
#include <TYPES.H>
#include <RASTER.H>

void RenderGunSlinger(GunSlinger *gs, void *base)
{
	gs->sprite.bitmap.current_image = gs->sprite.bitmap.stored_images[gs->player_state];
	gs->sprite.bitmap.raster.Alpha(base, &gs->sprite);
	gs->sprite.render_flag = OFF;
}

void RenderBullet(Bullet *bullet, void *base)
{
	bullet->sprite.bitmap.raster.Draw(base, &bullet->sprite);
}

void RenderScore(Score *score, void *base)
{
}

void RenderBackground(BackGround *bg, void *base)
{
	bg->sprite.bitmap.raster.Draw(base, &bg->sprite);
	bg->sprite.render_flag = OFF;
}

void Render(Game *game, void *base)
{
	int i;

	/* render background */

	if (game->background.sprite.render_flag == ON)
		RenderBackground(&game->background, base);

	/* render player one state */

	if (game->gun_slinger[PLAYER_ONE].sprite.render_flag == ON)
		RenderGunSlinger(&game->gun_slinger[PLAYER_ONE], base);

	/* render player two state */

	if (game->gun_slinger[PLAYER_TWO].sprite.render_flag == ON)
		RenderGunSlinger(&game->gun_slinger[PLAYER_TWO], base);

	/* render player one score */

	if (game->gun_slinger[PLAYER_ONE].score.sprite.render_flag == ON)
		RenderScore(&game->gun_slinger[PLAYER_ONE].score, base);

	/* render player two score */

	if (game->gun_slinger[PLAYER_TWO].score.sprite.render_flag == ON)
		RenderScore(&game->gun_slinger[PLAYER_TWO].score, base);

	/* render player one bullets */

	for (i = 0; i < NUM_ROUNDS; i++)
		if (game->gun_slinger[PLAYER_ONE].bullet[i].sprite.render_flag == ON)
			RenderBullet(&game->gun_slinger[PLAYER_ONE].bullet[i], base);

	/* render player two bullets */
	for (i = 0; i < NUM_ROUNDS; i++)
		if (game->gun_slinger[PLAYER_TWO].bullet[i].sprite.render_flag == ON)
			RenderBullet(&game->gun_slinger[PLAYER_TWO].bullet[i], base);
}
