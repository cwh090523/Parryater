#include "MainGameData.h"
#include <cmath>
#include "GameState.h"
Bullet::~Bullet() {}

void Bullet::ProjectileUpdate(GameState& state) {

    if (state.curTime > lifeTime) {
        isActive = false;
        return;
    }
	if (pos.x <= 0 || pos.x >= WIDTH || pos.y >= HEIGHT || pos.y <= 0)
	{
		isActive = false;
		return;



	}
    if (state.curTime < lastMoveTime +MoveSpeed) {
        return;
    }


    if (moveDir.x == 0 && moveDir.y == 0) {
        return;
    }


    prevPos = pos;

    pos.x += moveDir.x * 2;
    pos.y += moveDir.y;




    lastMoveTime = state.curTime;
    /*float dt = 0.016f;
    float moveAmount = MoveSpeed * dt;
    if (moveDir.x != 0 && moveDir.y != 0) {
        moveAmount *= (1.0f / std::sqrt(2.0f));
    }

    prevPos = pos;

    floatPos.x += moveDir.x * moveAmount;
    floatPos.y += moveDir.y * moveAmount;
    Position nextPos = { static_cast<int>(floatPos.x), static_cast<int>(floatPos.y) };

    if (nextPos.x != pos.x || nextPos.y != pos.y) {
        pos = nextPos;
    }
	pos.x = static_cast<int>(floatPos.x);
	pos.y = static_cast<int>(floatPos.y);*/
	
}