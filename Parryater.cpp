#include "TitleScene.h"
#include "GameState.h"
int main()
{
	GameState state;
	TitleData title;
	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleWindowStyle(true);
	SetcursorVisble(false);
	InitTitle(state);
	while (true)
	{
		UpdateTitle(title,state);
		RenderTitle(title);
	}
}