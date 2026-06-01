
#pragma once
#include "enums.h"
struct FloatPosition {
	float x; float y;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};
struct Position {
	int x; int y;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};

struct GameState
{
	Scene currentScene;
	bool isRunning;
	bool isGameOver;
	bool isPaused;
	int score;
};

struct Player {

	int maxHp = 3;
	int hp = 3;
	int attackPower = 1;
	int attackSpeed = 200;
	float MoveSpeed = 1; // 1 = 1초마다 1칸 이동
	int DashVelocity = 1;
	int DashCooldown = 2000;
	Position pos = { 0,0 };
	Position lastMoveDir = { 0,0 };
	FloatPosition floatPos = { 0,0 };
	


	void PlayerUpdate();
};