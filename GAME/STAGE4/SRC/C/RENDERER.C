#include <RENDERER.H>
#include <TYPES.H>
#include <RASTER.H>

void RenderGunSlinger(const GunSlinger *gs, void *base)
{
}

void RenderBullet(const Bullet *bullet, void *base)
{
}

void RenderScore(const Score *score, void *base)
{
}

void RenderBackground(const BackGround *bg, void *base)
{
	bg->sprite.bitmap.raster.Draw(base, bg->sprite.bitmap.current_image);
}

void Render(const Game *game, void *base)
{
}
