#include "TitleScene.h"
#include"SettingScene.h"
#include "InGameScene.h"
#include "ShopScene.h"
#include "GameOverScene.h"
#include "enums.h"
#include "Console.h"
#include "GameState.h"
int main()
{
	GameState state;
	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleWindowStyle(true);
	SetcursorVisble(false);
	srand(time(nullptr));
	while (state.isRunning)
	{

		FrameSync(100);
		state.curTime = GetTickCount64();
		UpdateInput();
		if (state.prevScene != state.curScene) {
			switch (state.curScene)
			{
			case Scene::TITLE:
				InitTitle(state);
				break;
			case Scene::SETTING:
				SettingInit(state);
				break;
			case Scene::INGAME:
				InGameInit(state);
				break;
			case Scene::SHOP:
				ShopInit(state);
				break;
			case Scene::GAMEOVER:
				GameOverInit(state);
				break;
			}
			state.prevScene = state.curScene;
		}
		switch (state.curScene)
		{
		case Scene::TITLE:
			UpdateTitle(state);
			RenderTitle(state);
			break;
		case Scene::SETTING: // 완벽 미구현
			SettingUpdate(state);
			SettingRender(state);
			break;
		case Scene::INGAME:
			InGameUpdate(state);
			InGameRender(state);

			InGameAfterUpdate(state);
			break;
		case Scene::SHOP: // 완벽 미구현
			ShopUpdate(state);
			ShopRender(state);
			break;
		case Scene::GAMEOVER:// 완벽 미구현
			GameOverUpdate(state);
			GameOverRender(state);
			break;

		}

	}
}