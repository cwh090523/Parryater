#include "Game.h"
#include "Console.h"
#include "TitleScene.h"
#include "SettingScene.h"
//#include "InGameScene.h"
void Init(GameState& state)
{
	srand((unsigned int)time(nullptr));
	SetConsoleSize(WIDTH, HEIGHT);
	SetcursorVisble(false);
	SetConsoleWindowStyle(true);
	state = GameState{};
}

void Update(GameState& state)
{
	bool sceneChanged =
		state.curScene != state.prevScene;
	state.prevScene = state.curScene;
	UpdateInput();

	//if (GetKeyDown('1'))
	//	SetConsoleFont(L"MS Gothic", { 10,20 }, FW_BOLD);
	//if (GetKeyDown('2'))
	//	SetConsoleFont(L"NSimSun", { 10,20 });
	//if (GetKeyDown('3'))
	//	SetConsoleFont(L"¸¼Àº °íµñ", { 10,20 });
	//if (GetKeyDown('4'))
	//	SetConsoleFont(L"SimSun-ExtB", { 7,14 });
	//if (GetKeyDown('5'))
	//	SetConsoleFont(L"±¼¸²Ã¼", { 8,16 });
	if (GetKeyDown(VK_ESCAPE))
	{
		state.isRunning = false;
	}

	switch (state.curScene) {
	case Scene::TITLE:
		if (sceneChanged)
			InitTitle(state);
		//UpdateTitle(state);
		break;
	//case Scene::INGAME:
	//	if (sceneChanged)
	//		InitInGame(state);
	//	UpdateInGame(state);
	//	break;
	case Scene::SETTING:
		SettingUpdate(state);
		break;
	case Scene::GAMEOVER:
		break;
	}
}

void Render(const GameState& state)
{
	if (state.prevScene != state.curScene)
		system("cls");
	GotoXY(0, 0);
	switch (state.curScene) {
	case Scene::TITLE:
		RenderTitle(state);
		break;
	//case Scene::INGAME:
	//	RenderInGame(state);
	//	break;
	case Scene::SETTING:
		SettingRender(state);
	case Scene::GAMEOVER:
		break;
	}
}