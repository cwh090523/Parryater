#include "MainGameData.h"

Enemy::~Enemy() {}

void Enemy::EnemyUpdate() {
}



Enmey1::Enmey1(Stats astat, Position apos) : Enemy(astat, apos) {}

void Enmey1::EnemyUpdate(GameState& state) {
}
Enmey1::~Enmey1() {}