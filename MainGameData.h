#pragma once
#include "enums.h"
#include <Windows.h>
#include <vector>
struct GameState;
class Enemy;
class Bullet;
using namespace std;

struct Position {
	int x; int y;

	bool operator==(const Position& other) const {
		return x == other.x && y == other.y;
	}
};

struct FloatPosition {
	float x; float y;

	bool operator==(const FloatPosition& other) const {
		return (abs(x - other.x) < 0.001f) && (abs(y - other.y) < 0.001f);
	}
};


struct Stats
{
public:
	int maxHp = 3;
	int hp = 3;
	int attackPower = 1;
	int attackSpeed = 50; // 0.2초마다
	float MoveSpeed = 1; // 1초마다 N칸 이동(플레이어는 int로 취급함);

	//여기부턴 플레이어 고유 능력치
	int DashVelocity = 7;
	int DashCooldown = 1500;
};
class Player {

public:
	int remingDashTime = 0;
	int remingDashCooldown = 0;
	int remingInvisibleTime = 0;
	
	Stats stats;
	Position prevPos = { 0,0 };
	Position pos = { 0,0 };
	Position moveDir = { 0,0 };
	Position lastMoveDir = { 0,0 };
    FloatPosition floatPos = { 0,0 };
    ULONGLONG lastAttackTime;
    ULONGLONG lastMoveTime;
	void PlayerUpdate();
};

class Enemy {
	public:
		
		Stats stats;
		Enemy(Stats astat, Position apos) {
			stats = astat;
			pos = apos;
			floatPos = { static_cast<float>(apos.x), static_cast<float>(apos.y) };
		}
		~Enemy();
		int hp = 10;
		float MoveSpeed;
		Position prevPos = { 0,0 };
		Position pos = { 0,0 };
		Position moveDir = { 0,0 };
		FloatPosition floatPos = { 0,0 };

		bool isAlive = true;
		virtual void EnemyUpdate() = 0;

};
class Enmey1 : public Enemy
{
public:
	Enmey1(Stats astat, Position apos);
	~Enmey1();

	void EnemyUpdate(GameState& state);
};

class Bullet {
	public:
		Bullet(Position apos, Position adir, int adamage,float amoveSpeed, int alifeTime, ProjectileType atype) {
			pos = apos;
			moveDir = adir;
			damage = adamage;
			type = atype;
			lifeTime = alifeTime;
			MoveSpeed = amoveSpeed;
			lastMoveTime = GetTickCount64();
			lifeTime = lastMoveTime + alifeTime;
			//floatPos = { static_cast<float>(apos.x), static_cast<float>(apos.y) };
	}
public:
	~Bullet();
	Position pos;
	Position moveDir;
	Position prevPos;
	//FloatPosition floatPos;
	bool isActive = true;
	int damage = 0;
	float MoveSpeed = 0;
	ProjectileType type;
	ULONGLONG lifeTime;
	ULONGLONG lastMoveTime;
	void ProjectileUpdate(GameState& state);
};