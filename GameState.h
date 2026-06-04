#pragma once
#pragma once
#include "Enums.h"
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include "MainGameData.h"
#include "enums.h"
constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

struct TitleData
{
	Menu curMenu = Menu::START;

};

struct SettingData
{
	SettingsMenu curMenu = SettingsMenu::VOLUME;
	bool isSelected = false;
	int selectIndex = 0;
	float bgmVolume = 0.5f;
	float sfxVolume = 0.5f;
	MovementSettingData movementSettingData;
	void MovecurMenu(int direction) {
		selectIndex = 0;
		curMenu = static_cast<SettingsMenu>(selectIndex);
	}
	void SelectMenu() {

		if (curMenu == SettingsMenu::RESET) {
			ResetSettings();
			return;
		}
		isSelected = true;
		if (isSelected) {
			isSelected = false;
		}
	}
	
	void ResetSettings() {
		bgmVolume = 0.5f;
		sfxVolume = 0.5f;
		movementSettingData.moveUpKey = 'W';
		movementSettingData.moveDownKey = 'S';
		movementSettingData.moveLeftKey = 'A';
		movementSettingData.moveRightKey = 'D';
		movementSettingData.BombKey = 'E';
		movementSettingData.SelectKey = VK_RETURN;
		movementSettingData.dashKey = VK_SPACE;
	}

};
struct MovementSettingData
{
	char moveUpKey = 'W';
	char moveDownKey = 'S';
	char moveLeftKey = 'A';
	char moveRightKey = 'D';
	char moveUpArrowKey = VK_UP;
	char moveDownArrowKey = VK_DOWN;
	char moveLeftArrowKey = VK_LEFT;
	char moveRightArrowKey = VK_RIGHT;
	char SelectKey = VK_RETURN;
	char BombKey = 'E';
	char dashKey = VK_SPACE;
};
struct InGameData
{
	bool isPaused;
	bool isGameOver;
	int score;
	Player player;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
};
struct ShopData {

};
struct StageData {

};
struct GameState
{
	Scene prevScene = Scene::NONE;
	Scene curScene = Scene::INGAME;
	bool isRunning = true;
	TitleData titleData;
	SettingData settingData;
	InGameData inGameData;
	ShopData shopData;
	ULONGLONG curTime;
};