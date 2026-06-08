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
	state.inGameData.player.lastMoveTime = state.curTime;;
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

    PlayerMove(state);
}

void InGameRender(const GameState& state) {
    const Player& player = state.inGameData.player;

    if (player.prevPos.x != player.pos.x || player.prevPos.y != player.pos.y) {
        GotoXY(player.prevPos.x, player.prevPos.y);
        cout << " ";

        GotoXY(player.pos.x, player.pos.y);
        SetColor(Color::LIGHT_GREEN);
        cout << "@";

        const_cast<Player&>(player).prevPos = player.pos;
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

    // float dt = 0.016f;
    // float moveAmount = player.stats.MoveSpeed * dt;
    // if (player.moveDir.x != 0 && player.moveDir.y != 0) {
    //     moveAmount *= (1.0f / std::sqrt(2.0f));
    // }
    // player.floatPos.x += player.moveDir.x * moveAmount;
    // ...

}