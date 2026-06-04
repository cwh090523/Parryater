#pragma once
#pragma once
#include "Enums.h"
#define NOMINMAX
#include <Windows.h>
#include <vector>

constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

struct GameState
{
	Scene prevScene = Scene::NONE;
	Scene curScene = Scene::INGAME;
	Menu curMenu = Menu::START;
	bool isRunning = true;
	//Player player;
	ULONGLONG curTime;
};