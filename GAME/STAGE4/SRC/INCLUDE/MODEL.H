#ifndef MODEL_H
#define MODEL_H

#define NUM_ROUNDS 6
#define MAX_ROUNDS (NUM_ROUNDS - 1)
#define MAX_SCORE 10

#define NUM_PLAYERS 2
#define NUM_SPRITE_STATES 10

/* Player index */

#define PLAYER_ONE 0
#define PLAYER_TWO 1

#define BULLET_SPEED 16
#define PLAYER_SPEED 32

/* Player forward direction */

#define STANDARD 1
#define INVERTED -1

#define ON 1
#define OFF 0

/* Is the player Dead or alive ? */

#define ALIVE 1
#define DEAD 0

/* 16 for border (Boundary's) */

#define SCREEN_TOP_EDGE 16
#define SCREEN_LEFT_EDGE 16
#define SCREEN_RIGHT_EDGE (640 - 16)
#define SCREEN_BOTTOM_EDGE (400 - 16)

/* Player States */

#define STATE_DEAD 0
#define STATE_NORM 1
#define STATE_SHOOT 2
#define STATE_SHOOT_UP 3
#define STATE_SHOOT_DOWN 4
#define STATE_WALK 5

struct _Bitmap;
struct _Sprite;

typedef struct _RasterFunctions
{
	void (*Draw)(const void *, struct _Sprite *);
	void (*Alpha)(const void *, struct _Sprite *);
	void (*Clear)(const void *, struct _Sprite *);
} RasterFunctions;

typedef struct _Bitmap
{
	int height; /* height of current image */
	void *stored_images[NUM_SPRITE_STATES];
	void *current_image;
	RasterFunctions raster;
} Bitmap;

typedef struct _Sprite
{
	int x_vel, y_vel; /* horiz. & vert. displacement per clock tick */
	int x_pos, y_pos; /* position coordinates */
	Bitmap bitmap;
} Sprite;

typedef struct _Bullet
{
	Sprite sprite;
	int flag;
} Bullet;

typedef struct _BackGround
{
	Sprite sprite;
} BackGround;

typedef struct _Score
{
	int current_score;
	Sprite sprite;
} Score;

typedef struct _GunSlinger
{
	int num_bullets, current_bullet, flag_alive, orientation;
	Sprite sprite;
	Bullet bullet[NUM_ROUNDS];
	Score score;
} GunSlinger;

typedef struct _Game
{
	GunSlinger gun_slinger[NUM_PLAYERS];
	BackGround background;
} Game;

void MDLEnvGunSlingerCollision(GunSlinger *gs);
void MDLMoveGunSlinger(GunSlinger *gs);
void MDLInitGunSlinger(Game *game);

int MDLMoveBullet(Bullet *bullet, GunSlinger *shooter, GunSlinger *target);
void MDLEnvBulletCollision(Bullet *bullet);
void MDLBulletReload(GunSlinger *gs);
void MDLFireBullet(GunSlinger *gs);

void MDLPlayerBulletCollision(Bullet *bullet, GunSlinger *shooter, GunSlinger *target);
void MDLTurnOffBullet(Bullet *Bullet);
void MDLIncScore(GunSlinger *gs);
int MDLGetScore(GunSlinger gs);

void MDLInitGameStates(Game *game);

#endif /* MODEL_H */
