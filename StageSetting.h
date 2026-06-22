#pragma once
#include "Console.h"
#include "MainGameData.h" 
#include "InGameScene.h"
#include "GameState.h"
#include <cmath>
#include <algorithm> 
#include <iostream>
static unique_ptr<Enemy> SpawnRusher(Stats stat, Position pos) { return make_unique<EnemyRusher>(stat, pos); }
static unique_ptr<Enemy> SpawnShooter(Stats stat, Position pos) { return make_unique<EnemyShooter>(stat, pos); }
static unique_ptr<Enemy> SpawnZigzag(Stats stat, Position pos) { return make_unique<EnemyZigzag>(stat, pos); }
void StageInit(GameState& state);

void StageUpdate(GameState& state);
void StageRender(const GameState state);