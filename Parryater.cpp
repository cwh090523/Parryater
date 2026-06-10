#include "TitleScene.h"
#include"SettingScene.h"
#include "InGameScene.h"
#include "ShopScene.h"
#include "EndingScene.h"	
#include "enums.h"
#include "Console.h"
#include "GameState.h"
#include "Game.h"
int main()
{
	GameState state;
	Init(state);
	while (state.isRunning)
	{
		FrameSync(60);
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
				EndingInit(state);
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
			break;
		case Scene::SHOP: // 완벽 미구현
			ShopUpdate(state);
			ShopRender(state);
			break;
		case Scene::GAMEOVER:// 완벽 미구현
			EndingUpdate(state);
			EndingRender(state);
			break;

		}

	}
}