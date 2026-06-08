#pragma once
#include "Console.h"
#include "MainGameData.h" 
#include "InGameScene.h"
#include "GameState.h"
#include <cmath>

void InGameInit(GameState& state) {
    state.inGameData.isPaused = false;
    state.inGameData.isGameOver = false;
    state.inGameData.score = 0;


    state.inGameData.enemies.clear();
    state.inGameData.bullets.clear();

    state.inGameData.player.pos = { 10, 10 };
    state.inGameData.player.floatPos = { 10.0f, 10.0f };
    state.inGameData.player.prevPos = { 10, 10 };
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
    Player player = state.inGameData.player;

    GotoXY(player.prevPos.x, player.prevPos.y);
    cout << " ";

    GotoXY(player.pos.x, player.pos.y);
    SetColor(Color::LIGHT_GREEN);
    cout << "@";

    player.prevPos = player.pos;
}

void PlayerMove(GameState& state) {
    Player& player = state.inGameData.player;

    if (player.moveDir.x != 0 && player.moveDir.y != 0) {
        float scale = 1.0f / std::sqrt(2.0f);
        player.floatPos.x += player.moveDir.x * player.stats.MoveSpeed * scale * 0.016f;
        player.floatPos.y += player.moveDir.y * player.stats.MoveSpeed * scale * 0.016f;
    }
    else {
        player.floatPos.x += player.moveDir.x * player.stats.MoveSpeed * 0.016f;
        player.floatPos.y += player.moveDir.y * player.stats.MoveSpeed * 0.016f;
    }

    player.pos.x = static_cast<int>(player.floatPos.x);
    player.pos.y = static_cast<int>(player.floatPos.y);
}