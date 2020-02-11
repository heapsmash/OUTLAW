#include <RENDERER.H>
#include <MODEL.H>
#include <osbind.h>

int main(int argc, char *argv[])
{
	Game game;
	void *base = Physbase();
	MDLInitGameStates(&game);
	ClearScreen(base);
	RenderBackground(&game.background, base);

	return 0;
}
