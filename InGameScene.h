#pragma once
#include "Console.h"
struct GameState;
void InGameInit(GameState& state);
void InGameUpdate(GameState& state);
void InGameRender(const GameState& state);

void PlayerMove(GameState& state);