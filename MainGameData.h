
#pragma once
#include "enums.h"
#include <Windows.h>
#include <vector>
using namespace std;
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
		
		Stats stats;
		Enemy(Stats astat, Position apos) {
			stats = astat;
			pos = apos;
			floatPos = { static_cast<float>(apos.x), static_cast<float>(apos.y) };
		}
		~Enemy();
		int hp = 10;
		float MoveSpeed;
		Position pos;
		Position moveDir;
		FloatPosition floatPos;
		bool isAlive = true;
		virtual void EnemyUpdate();

};
class Enmey1 : public Enemy
{
public:
	Enmey1(Stats astat, Position apos);
	~Enmey1();

	void EnemyUpdate() {
		
	}
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
			floatPos = { static_cast<float>(apos.x), static_cast<float>(apos.y) };
	}
	~Bullet();
	Position pos;
	Position moveDir;
	FloatPosition floatPos;
	bool isActive = true;
	int damage = 0;
	float MoveSpeed = 0;
	ProjectileType type;
	int lifeTime = 0;
	void ProjectileUpdate() {

	}
};