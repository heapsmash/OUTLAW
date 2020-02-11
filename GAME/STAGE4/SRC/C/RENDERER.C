#include <RENDERER.H>
#include <TYPES.H>
#include <RASTER.H>

void RenderGunSlinger(GunSlinger *gs, void *base)
{
	gs->sprite.bitmap.current_image = gs->sprite.bitmap.stored_images[gs->player_state];
	gs->sprite.bitmap.raster.Draw(base, &gs->sprite);
}

void RenderBullet(Bullet *bullet, void *base)
{
}

void RenderScore(Score *score, void *base)
{
}

void RenderBackground(BackGround *bg, void *base)
{
	bg->sprite.bitmap.raster.Draw(base, &bg->sprite);
}

void Render(Game *game, void *base)
{
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
}
