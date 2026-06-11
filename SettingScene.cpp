#include "SettingScene.h"
#include "GameState.h"
#include "Console.h"

#include "SettingService.h"
#include "KeyUtil.h"

void SettingInit(GameState& state)
{
	system("cls");
	state.settingData.curMenu = SettingsMenu::VOLUME;
	state.settingData.isSelected = false;
	state.settingData.selectIndex = 0;
}

void SettingUpdate(GameState& state)
{
	SettingData& setting = state.settingData;

	if (GetKeyDown(VK_ESCAPE))
	{
		if (setting.isSelected) {

			system("cls");
			ExitSettingSubMenu(setting);
		}
		else
			state.curScene = Scene::TITLE;

		return;
	}

	if (setting.isSelected)
	{
		if (setting.curMenu == SettingsMenu::VOLUME)
		{
			if (GetKeyDown(VK_UP))
				MoveSettingSelectIndex(setting, -1, 1);

			if (GetKeyDown(VK_DOWN))
				MoveSettingSelectIndex(setting, 1, 1);

			if (GetKeyDown(VK_LEFT))
				ChangeSettingVolume(setting, -1);

			if (GetKeyDown(VK_RIGHT))
				ChangeSettingVolume(setting, 1);
		}

		else if (setting.curMenu == SettingsMenu::CONTROLS)
		{
			if (GetKeyDown(VK_UP))
				MoveSettingSelectIndex(setting, -1, 5);

			if (GetKeyDown(VK_DOWN))
				MoveSettingSelectIndex(setting, 1, 5);

			for (int key = 0; key < 256; ++key)
			{
				if (GetKeyDown(key))
				{
					if (key == VK_UP || key == VK_DOWN || key == VK_ESCAPE)
						break;

					ChangeControlKey(setting, key);
					break;
				}
			}
		}

		return;
	}

	if (GetKeyDown(VK_UP))
		MoveSettingMenu(setting, -1);

	if (GetKeyDown(VK_DOWN))
		MoveSettingMenu(setting, 1);

	if (GetKeyDown(VK_SPACE) || GetKeyDown(VK_RETURN))
	{
		switch (setting.curMenu)
		{
		case SettingsMenu::VOLUME:
			system("cls");
		case SettingsMenu::CONTROLS:
			system("cls");
			EnterSettingSubMenu(setting);
			break;

		case SettingsMenu::RESET:
			ResetSettingData(setting);
			break;

		case SettingsMenu::BACK:
			system("cls");
			state.curScene = Scene::TITLE;
			break;
		}
	}
}

void SettingRender(const GameState& state)
{
	const SettingData& setting = state.settingData;
	const MovementSettingData& move = setting.movementSettingData;

	COORD res = GetConsoleResolution();
	int cx = res.X / 2 - 12;
	int cy = res.Y / 3;

	GotoXY(cx, cy - 2);
	SetColor(Color::LIGHT_YELLOW);
	cout << "[ 설정 ]";
	SetColor();

	if (setting.isSelected && setting.curMenu == SettingsMenu::VOLUME)
	{
		GotoXY(cx, cy);
		cout << (setting.selectIndex == 0 ? "> " : "  ");
		cout << "BGM : " << (int)(setting.bgmVolume * 100) << "%  ";

		GotoXY(cx, cy + 1);
		cout << (setting.selectIndex == 1 ? "> " : "  ");
		cout << "SFX : " << (int)(setting.sfxVolume * 100) << "%   ";

		GotoXY(cx, cy + 4);
		cout << "UP/DOWN    : 선택";
		GotoXY(cx, cy + 5);
		cout << "LEFT/RIGHT : 변경";
		GotoXY(cx, cy + 6);
		cout << "ESC        : 돌아가기";
		return;
	}

	if (setting.isSelected && setting.curMenu == SettingsMenu::CONTROLS)
	{
		const string labels[] =
		{
			"Move Up    : ",
			"Move Down  : ",
			"Move Left  : ",
			"Move Right : ",
			"Attack     : ",
			"Dash       : "
		};

		const string keys[] =
		{
			KeyToString(move.moveUpArrowKey),
			KeyToString(move.moveDownArrowKey),
			KeyToString(move.moveLeftArrowKey),
			KeyToString(move.moveRightArrowKey),
			KeyToString(move.AttackKey),
			KeyToString(move.dashKey)
		};

		for (int i = 0; i < 6; ++i)
		{
			GotoXY(cx, cy + i);
			cout << (setting.selectIndex == i ? "> " : "  ");
			cout << labels[i] << keys[i] << "     ";
		}

		GotoXY(cx, cy + 8);
		cout << "UP/DOWN : 선택";
		GotoXY(cx, cy + 9);
		cout << "키를 눌러 변경하기";
		GotoXY(cx, cy + 10);
		cout << "ESC : 돌아가기";
		return;
	}

	const string labels[] =
	{	
		"소리                ",
		"조작                ",
		"초기화              ",
		"돌아가기            "
	};

	for (int i = 0; i < 4; ++i)
	{
		GotoXY(cx, cy + i);
		cout << (i == (int)setting.curMenu ? "> " : "  ");
		cout << labels[i];
	}

	GotoXY(cx, cy + 6);
	cout << "ENTER / SPACE : 선택";
	GotoXY(cx, cy + 7);
	cout << "ESC : 돌아가기";
}