#pragma once
#pragma once
//#include "Enums.h"
#define NOMINMAX
#include <Windows.h>
#include <vector>

constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;
//
//struct GameState
//{
//	Scene prevScene = Scene::NONE;
//	Scene curScene = Scene::INGAME;
//	Menu curMenu = Menu::START;
//	bool isRunning = true;
//	Block map[MAP_HEIGHT][MAP_WIDTH] = {};
//	Player player;
//	ULONGLONG curTime;
//	std::vector<Bomb> vecBomb;
//	std::vector<Flame> vecFlame;
//	std::vector<DashTrail> vecTrail;
//};