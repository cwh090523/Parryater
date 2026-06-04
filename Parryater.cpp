#include "TitleScene.h"
#include "GameState.h"
int main()
{
	GameState state;
	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleWindowStyle(true);
	SetcursorVisble(false);
	InitTitle(state);
	while (true)
	{
		UpdateTitle(state);
		RenderTitle(state);
	}
}