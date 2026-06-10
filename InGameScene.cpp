#pragma once
#include "Console.h"
#include "MainGameData.h" 
#include "InGameScene.h"
#include "GameState.h"
#include <cmath>
#include <algorithm> 
using namespace std;

void InGameInit(GameState& state) {
    state.inGameData.isPaused = false;
    state.inGameData.isGameOver = false;
    state.inGameData.score = 0;

    state.inGameData.enemies.clear();
    state.inGameData.bullets.clear();

    state.inGameData.player.pos = { 10, 10 };
    state.inGameData.player.floatPos = { 10.0f, 10.0f };
    state.inGameData.player.prevPos = { 10, 10 };
    state.inGameData.player.stats.MoveSpeed = 50;
    state.inGameData.player.lastMoveTime = state.curTime;
    state.inGameData.player.lastAttackTime = state.curTime;
}

void InGameUpdate(GameState& state) {
    if (GetKeyDown(VK_ESCAPE)) {
        state.isRunning = false;
        return;
    }

    if (state.inGameData.isGameOver) {
        state.curScene = Scene::GAMEOVER;
        return;
    }

    Player& player = state.inGameData.player;
    MovementSettingData& msd = state.settingData.movementSettingData;

    player.lastMoveDir = player.moveDir;
    player.moveDir = { 0, 0 };

    if (GetKey(msd.moveUpKey)) player.moveDir.y = -1;
    if (GetKey(msd.moveDownKey)) player.moveDir.y = 1;
    if (GetKey(msd.moveLeftKey)) player.moveDir.x = -1;
    if (GetKey(msd.moveRightKey)) player.moveDir.x = 1;
    if (GetKey(msd.dashKey)) DashPlayer(state);
    PlayerMove(state);
    PlayerAttack(state);

    for (Bullet& bullet : state.inGameData.bullets) {
        if (bullet.isActive) {
            bullet.ProjectileUpdate(state);
        }
    }

    auto iter = state.inGameData.bullets.begin();
    while (iter != state.inGameData.bullets.end()) {
        if (!iter->isActive) {
            GotoXY(iter->pos.x, iter->pos.y);
            cout << " ";
            iter = state.inGameData.bullets.erase(iter);
        }
        else {
            ++iter;
        }
    }
}
void DashPlayer(GameState& state)
{


}
void InGameRender(const GameState& state) {
    const Player& player = state.inGameData.player;

    for (const Bullet& bullet : state.inGameData.bullets) {
        if (bullet.prevPos.x != bullet.pos.x || bullet.prevPos.y != bullet.pos.y) {
            GotoXY(bullet.prevPos.x, bullet.prevPos.y);
            cout << " ";
        }

        if (bullet.isActive) {
            GotoXY(bullet.pos.x, bullet.pos.y);
            SetColor(Color::LIGHT_RED);
            cout << "V";
        }
    }

    if (player.prevPos.x != player.pos.x || player.prevPos.y != player.pos.y) {
        GotoXY(player.prevPos.x, player.prevPos.y);
        cout << " ";
    }

    GotoXY(player.pos.x, player.pos.y);
    if (player.remingDashTime > 0) {
        SetColor(Color::WHITE);
    }
    else {
        SetColor(Color::LIGHT_GREEN);

    }
    cout << "@";

    const_cast<Player&>(player).prevPos = player.pos;
    for (Bullet& bullet : const_cast<std::vector<Bullet>&>(state.inGameData.bullets)) {
        bullet.prevPos = bullet.pos;
    }
}

void PlayerMove(GameState& state) {
    Player& player = state.inGameData.player;

    if (state.curTime < player.lastMoveTime + player.stats.MoveSpeed) {
        return;
    }

    if (player.moveDir.x == 0 && player.moveDir.y == 0) {
        return;
    }

    player.prevPos = player.pos;

    player.pos.x += player.moveDir.x * 2;
    player.pos.y += player.moveDir.y;

    player.pos.x = std::max(0, std::min(player.pos.x, WIDTH - 1));
    player.pos.y = std::max(0, std::min(player.pos.y, HEIGHT - 1));

    player.lastMoveTime = state.curTime;
}

void PlayerAttack(GameState& state) {
    Player& player = state.inGameData.player;
    if (GetKey(state.settingData.movementSettingData.SelectKey)) {
        if (state.curTime >= player.lastAttackTime + player.stats.attackSpeed) {
            Bullet bullet = Bullet(player.pos, Position{ 0,-1 }, player.stats.attackPower, 20.0f, 3000, ProjectileType::Player);
            state.inGameData.bullets.push_back(bullet);
            player.lastAttackTime = state.curTime;
        }
    }
}