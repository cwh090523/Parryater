#include "TitleScene.h"
#include"SettingScene.h"
#include "InGameScene.h"
#include "ShopScene.h"
#include "GameOverScene.h"
#include "enums.h"
#include "Console.h"
#include "GameState.h"
#include "SettingStorage.h"
#include "SoundManager.h"

int main()
{
	GameState state;
	srand((unsigned int)time(nullptr));

	state = GameState{};

	SetConsoleSize(WIDTH, HEIGHT);
	SetConsoleMouseInputDisabled();
	SetConsoleWindowStyle(true);
	SetcursorVisble(false);


	LoadSettings(state.settingData);

	SOUND->Init();
	SOUND->SetBGMVolume(state.settingData.bgmVolume);
	SOUND->SetSFXVolume(state.settingData.sfxVolume);

	state.curScene = Scene::TITLE;
	state.prevScene = Scene::NONE;
	while (state.isRunning)
	{

		FrameSync(100);
		state.curTime = GetTickCount64();
		UpdateInput();
		SOUND->Update();
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
		case Scene::SETTING:
			SettingUpdate(state);
			SettingRender(state);
			break;
		case Scene::INGAME:
			InGameUpdate(state);
			InGameRender(state);

			InGameAfterUpdate(state);
			break;
		case Scene::SHOP:
			ShopUpdate(state);
			ShopRender(state);
			break;
		case Scene::GAMEOVER:
			GameOverUpdate(state);
			GameOverRender(state);
			break;

		}

	}
}