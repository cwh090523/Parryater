#include "SettingScene.h"
#include "TitleScene.h"
#include "GameState.h"
#include "AsciiArt.h"

static AsciiObjs objs;
void SettingInit(GameState& state) {
	system("cls");
}

void SettingUpdate(GameState& state) {
	if (GetKeyDown(VK_ESCAPE)) {
		state.curScene = Scene::TITLE;
	}
	AsciiUpdate(objs);
	if (GetKeyDown(VK_UP))
	{
		state.settingData.curMenu = (SettingsMenu)std::max((int)SettingsMenu::VOLUME, (int)state.settingData.curMenu - 1);
	}
	if (GetKeyDown(VK_DOWN))
	{
		state.settingData.curMenu = (SettingsMenu)std::min((int)SettingsMenu::BACK, (int)state.settingData.curMenu + 1);
	}

	if (GetKeyDown(VK_SPACE) || GetKeyDown(VK_RETURN))
	{
		switch (state.settingData.curMenu)
		{
		case SettingsMenu::VOLUME:
			state.settingData.curMenu = SettingsMenu::VOLUME;
			state.settingData.SelectMenu();
			break;
		case SettingsMenu::CONTROLS:
			state.settingData.curMenu = SettingsMenu::CONTROLS;
			state.settingData.SelectMenu();
			break;
		case SettingsMenu::RESET:
			state.settingData.curMenu = SettingsMenu::RESET;
			state.settingData.SelectMenu();
			break;
		case SettingsMenu::BACK: 
			state.curScene = Scene::TITLE;
			break;
		}
	}
}

void SettingRender(const GameState& state) {

	// 화면 중앙에 출력
	COORD res = GetConsoleResolution();
	int cx = res.X / 2 - 4;
	int cy = res.Y / 3 * 2;

	const string labels[] = { "사운드", "조작", "초기화", "돌아가기"};
	for (int i = 0;i < 4; ++i) {
		GotoXY(cx - 2, cy + i);
		cout << (i == (int)state.settingData.curMenu ? ">" : " ") << " " << labels[i];
	}

	//const string infoLabels[] =
	//{
	//	"[ 조작 방법 ]",
	//	"WASD/방향키 : 이동",
	//	"SPACE	    : 대쉬",
	//	"E			: 공격",
	//	"Enter		: 선택",
	//	"ESC 로 돌아가기"
	//};
	//for (int i = 0; i < 5; ++i)
	//{
	//	GotoXY(cx - 6, cy + i);
	//	if (i == 0)
	//		SetColor(Color::LIGHT_YELLOW);
	//	else if (i == 4)
	//		SetColor(Color::LIGHT_GRAY);
	//	else
	//		SetColor();
	//	cout << infoLabels[i];
	//}
}


