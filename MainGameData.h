#pragma once
#include "enums.h"
#include <Windows.h>
#include <vector>
#include <algorithm>
#include <memory>
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

struct Stats {
    int maxHp = 3;
    int hp = 3;
    int attackPower = 1;
    int attackSpeed = 1500;
    float MoveInterval = 300;
    int DashVelocity = 7;
    int DashCooldown = 1500;
};

class Player {
public:
    ULONGLONG dashStartTime = 0;
    ULONGLONG dashEndTime = 0;
    ULONGLONG dashCooldownEndTime = 0;
    ULONGLONG invisibleEndTime = 0;
    Stats stats;
    Position prevPos = { 0,0 };
    Position pos = { 0,0 };
    Position moveDir = { 0,0 };
    Position lastMoveDir = { 0,0 };
    FloatPosition floatPos = { 0,0 };
    ULONGLONG lastAttackTime = 0;
    ULONGLONG lastMoveTime = 0;
    void PlayerUpdate();

    bool IsDashing(ULONGLONG curTime) const {
        return curTime >= dashStartTime && curTime < dashEndTime;
    }
    bool CanDash(ULONGLONG curTime) const {
        return curTime >= dashCooldownEndTime;
    }
};

class Enemy {
public:
    Stats stats;
    Enemy(Stats astat, Position apos) {
        stats = astat;
        hp = astat.maxHp;
        pos = apos;
        prevPos = apos;
        floatPos = { static_cast<float>(apos.x), static_cast<float>(apos.y) };
    }
    virtual ~Enemy() {}
    int hp = 10;
    ULONGLONG lastMoveTime = 0;
    Position prevPos = { 0,0 };
    Position pos = { 0,0 };
    Position moveDir = { 0,0 };
    FloatPosition floatPos = { 0,0 };
    bool isAlive = true;
    virtual void EnemyUpdate(GameState& state) = 0;
};

class EnemyRusher : public Enemy {
public:
    EnemyRusher(Stats astat, Position apos);
    ~EnemyRusher() {}
    void EnemyUpdate(GameState& state) override;
};

class EnemyShooter : public Enemy {
public:
    EnemyShooter(Stats astat, Position apos);
    ~EnemyShooter() {}
    ULONGLONG lastAttackTime = 0;
    void EnemyUpdate(GameState& state) override;
};

class EnemyZigzag : public Enemy {
public:
    EnemyZigzag(Stats astat, Position apos);
    ~EnemyZigzag() {}
    int zigDir = 1;
    int zigCount = 0;
    void EnemyUpdate(GameState& state) override;
};

class Bullet {
public:
    Bullet(Position apos, Position adir, int adamage, float amoveSpeed, ULONGLONG alifeTime, ProjectileType atype) {
        pos = apos;
        prevPos = apos;
        moveDir = adir;
        damage = adamage;
        type = atype;
        MoveSpeed = amoveSpeed;
        lastMoveTime = GetTickCount64();
        spawnTime = lastMoveTime;
        lifeTime = alifeTime;
        isActive = true;
    }
    ~Bullet();
    Position pos;
    Position moveDir;
    Position prevPos;
    bool isActive = true;
    int damage = 0;
    float MoveSpeed = 0;
    ProjectileType type;
    ULONGLONG lifeTime = 0;
    ULONGLONG spawnTime = 0;
    ULONGLONG lastMoveTime = 0;
    void ProjectileUpdate(GameState& state);
};