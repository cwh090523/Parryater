#include "MainGameData.h"
#include <cmath>
#include "GameState.h"
#include "Console.h"
Bullet::~Bullet() {}

void Bullet::ProjectileUpdate(GameState& state) {
    if (state.curTime > spawnTime + lifeTime) {
        isActive = false;
        return;
    }
    if (pos.x < 0 || pos.x >= WIDTH || pos.y >= HEIGHT || pos.y < 0) {
        isActive = false;
        return;
    }
    if (state.curTime < lastMoveTime + (ULONGLONG)MoveSpeed) {
        return;
    }
    if (moveDir.x == 0 && moveDir.y == 0) {
        return;
    }

    prevPos = pos;
    pos.x += moveDir.x * 2;
    pos.y += moveDir.y;

    if (pos.x < 0 || pos.x >= WIDTH || pos.y >= HEIGHT || pos.y < 0) {
        GotoXY(prevPos.x, prevPos.y);
        cout << " ";
        isActive = false;
        return;
    }

    lastMoveTime = state.curTime;
}