#include <MUSIC.H> 

/*
 * Begins the playing of the song by loading the data for the first note into the PSG.
 */

void start_music(void)
{

}

/* 
 * Advances to the next note of the song if necessary, as determined by the amount of time elapsed
 * since the previous call. The time elapsed is determined by the caller. It is intended that this value
 * is equal to the current value of the vertical blank clock, minus its value when the function was last
 * called.
 */ 

void update_music(uint32_t time_elapsed)
{

}
