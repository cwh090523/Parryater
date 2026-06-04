#pragma once
#pragma once
#include "Enums.h"
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include "MainGameData.h"

constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

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

struct TitleData
{
	Menu curMenu = Menu::START;

};
struct SettingData
{


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