#include <RENDERER.H>
#include <MODEL.H>
#include <osbind.h>

int main(int argc, char *argv[])
{
	Game game;
	void *base = Physbase();
	MDLInitGameStates(&game);
	ClearScreen(base);
	Render(&game, base);
	Cnecin();

	return 0;
}
