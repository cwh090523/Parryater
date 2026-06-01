
#pragma once
#include "enums.h"
#include <Windows.h>
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
	ULONGLONG currentTime;
};
struct Stats
{
	int maxHp = 3;
	int hp = 3;
	int attackPower = 1;
	int attackSpeed = 200; // 0.2초마다
	float MoveSpeed = 5; // 1초마다 1칸 이동

	//여기부턴 플레이어 고유 능력치
	int DashVelocity = 7;
	int DashCooldown = 1500;
};
class Player {

	int remingDashTime = 0;
	int remingDashCooldown = 0;
	int remingInvisibleTime = 0;
	Stats stats;
	Position pos = { 0,0 };
	Position lastMoveDir = { 0,0 };
	FloatPosition floatPos = { 0,0 };
	ULONGLONG lastAttackTime;
	void PlayerUpdate();
};

class Enemy {
	public:
		
		Enemy(Position pos);
		virtual ~Enemy();
		int hp = 10;
		float MoveSpeed;
		Position pos;
		Position moveDir;
		FloatPosition floatPos;
		void EnemyUpdate();

};
class Enmey1 : public Enemy
{
public:
	Enmey1(Position pos);
	~Enmey1();

	void EnemyUpdate() {
		
	}
};