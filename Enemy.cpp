#include "MainGameData.h"
#include "GameState.h"
#include <algorithm>
using namespace std;




EnemyRusher::EnemyRusher(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemyRusher::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;
    pos.y += 1;
    lastMoveTime = state.curTime;
    if (pos.y >= HEIGHT) isAlive = false;
}

EnemyShooter::EnemyShooter(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemyShooter::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;
    pos.y += 1;
    lastMoveTime = state.curTime;
    if (pos.y >= HEIGHT) { isAlive = false; return; }

    if (state.curTime >= lastAttackTime + (ULONGLONG)stats.attackSpeed) {
        Bullet bullet(pos, Position{ 0, 1 }, stats.attackPower, 20.0f, 5000, ProjectileType::Enemy);
        bullet.spawnTime = state.curTime;
        state.inGameData.bullets.push_back(bullet);
        lastAttackTime = state.curTime;
    }
}

EnemyZigzag::EnemyZigzag(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemyZigzag::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;
    pos.y += 1;
    pos.x += zigDir * 2;
    zigCount++;
    if (zigCount >= 5) {
        zigDir *= -1;
        zigCount = 0;
    }
    pos.x = std::max(0, std::min(pos.x, GAME_WIDTH - 1));
    lastMoveTime = state.curTime;
    if (pos.y >= HEIGHT) isAlive = false;
}