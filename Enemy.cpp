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
        Bullet bullet(pos, Position{ 0, 1 }, stats.attackPower, 25.0f, 5000, ProjectileType::Enemy);
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
EnemyWaver::EnemyWaver(Stats astat, Position apos) : Enemy(astat, apos) {}


void EnemyWaver::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;

    if (isAwakend) {
        lastMoveTime = state.curTime;
        pos.x += moveXdir;
        if (pos.x <= 0 || pos.x >= GAME_WIDTH - 1) {
            moveXdir *= -1;
        }

        if (state.curTime >= lastAttackTime + (ULONGLONG)stats.attackSpeed) {
            Bullet bullet(pos, Position{ 0, 1 }, stats.attackPower, 23.0f, 5000, ProjectileType::Enemy);
            bullet.spawnTime = state.curTime;
            state.inGameData.bullets.push_back(bullet);
            lastAttackTime = state.curTime;
        }
        return;
    }

    if (pos.y < 10) {
        pos.y += 1;
    }
    else {
        if (moveXdir == 0) {
            moveXdir = 1;
        }
        pos.x += moveXdir;

        if (pos.x <= 0 || pos.x >= GAME_WIDTH - 1) {
            moveXdir *= -1;
            isAwakend = true;
        }
    }

    lastMoveTime = state.curTime;
    if (pos.y >= HEIGHT) isAlive = false;
}
EnemySideShooter::EnemySideShooter(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemySideShooter::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;

    pos.y += 1;
    lastMoveTime = state.curTime;

    if (pos.y >= HEIGHT) { isAlive = false; return; }

    if (state.curTime >= lastAttackTime + (ULONGLONG)stats.attackSpeed) {
        Position dir = shootLeft ? Position{ -1,0 } : Position{ 1,0 };
        Bullet bullet(pos, dir, stats.attackPower, 20.0f, 5000, ProjectileType::Enemy);
        bullet.spawnTime = state.curTime;
        state.inGameData.bullets.push_back(bullet);

        shootLeft = !shootLeft;
        lastAttackTime = state.curTime;
    }
}

EnemyCrossShooter::EnemyCrossShooter(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemyCrossShooter::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;

    pos.y += 1;
    pos.x += moveDirX * 2;

    if (pos.x <= 0 || pos.x >= GAME_WIDTH - 1) moveDirX *= -1;

    lastMoveTime = state.curTime;

    if (pos.y >= HEIGHT) { isAlive = false; return; }

    if (state.curTime >= lastAttackTime + (ULONGLONG)stats.attackSpeed) {
        Position dirs[4] = {
            {1,1},{-1,1},{1,-1},{-1,-1}
        };

        for (auto& d : dirs) {
            Bullet bullet(pos, d, stats.attackPower, 40.0f, 5000, ProjectileType::Enemy);
            bullet.spawnTime = state.curTime;
            state.inGameData.bullets.push_back(bullet);
        }

        lastAttackTime = state.curTime;
    }
}

EnemyRadialShooter::EnemyRadialShooter(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemyRadialShooter::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;

    pos.y += 1;
    lastMoveTime = state.curTime;

    if (pos.y >= HEIGHT) { isAlive = false; return; }

    if (state.curTime >= lastAttackTime + (ULONGLONG)stats.attackSpeed) {
        Position dirs[8] = {
            {1,0},{-1,0},{0,1},{0,-1},
            {1,1},{-1,1},{1,-1},{-1,-1}
        };

        for (auto& d : dirs) {
            Bullet bullet(pos, d, stats.attackPower, 50.0f, 5000, ProjectileType::Enemy);
            bullet.spawnTime = state.curTime;
            state.inGameData.bullets.push_back(bullet);
        }

        lastAttackTime = state.curTime;
    }
}

EnemyTrackerX::EnemyTrackerX(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemyTrackerX::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;

    Player& player = state.inGameData.player;

    if (player.pos.x < pos.x) pos.x -= 2;
    else if (player.pos.x > pos.x) pos.x += 2;

    pos.y += 1;

    lastMoveTime = state.curTime;

    if (pos.y >= HEIGHT) isAlive = false;
}

EnemyChaser::EnemyChaser(Stats astat, Position apos) : Enemy(astat, apos) {}

void EnemyChaser::EnemyUpdate(GameState& state) {
    if (state.curTime < lastMoveTime + (ULONGLONG)stats.MoveSpeed) return;
    prevPos = pos;

    Player& player = state.inGameData.player;

    int dx = player.pos.x - pos.x;
    int dy = player.pos.y - pos.y;

    if (dx != 0) pos.x += (dx > 0 ? 1 : -1);
    if (dy != 0) pos.y += (dy > 0 ? 1 : -1);

    lastMoveTime = state.curTime;

    if (pos.y >= HEIGHT) isAlive = false;
}