#pragma once
#include "Console.h"
struct GameState;
void InGameInit(GameState& state);
void InGameUpdate(GameState& state);
void InGameRender(const GameState& state);
void InGameAfterUpdate(GameState& state);

void PlayerMove(GameState& state);
void PlayerAttack(GameState& state);
void RenderBorder();
void RenderUI(const GameState& state);
void InGameCollision(GameState& state);
void DashPlayer(GameState& state);
void StageInit(GameState& state);
void StageUpdate(GameState& state);
void InGameAfterUpdate(GameState& state);