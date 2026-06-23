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
static unique_ptr<Enemy> SpawnWaver(Stats stat, Position pos) { return make_unique<EnemyWaver>(stat, pos); }
static unique_ptr<Enemy> SpawnZigzag(Stats stat, Position pos) { return make_unique<EnemyZigzag>(stat, pos); }

static unique_ptr<Enemy> SpawnSideShooter(Stats stat, Position pos) { return make_unique<EnemySideShooter>(stat, pos); }
static unique_ptr<Enemy> SpawnCrossShooter(Stats stat, Position pos) { return make_unique<EnemyCrossShooter>(stat, pos); }
static unique_ptr<Enemy> SpawnRadialShooter(Stats stat, Position pos) { return make_unique<EnemyRadialShooter>(stat, pos); }
static unique_ptr<Enemy> SpawnTrackerX(Stats stat, Position pos) { return make_unique<EnemyTrackerX>(stat, pos); }
static unique_ptr<Enemy> SpawnChaser(Stats stat, Position pos) { return make_unique<EnemyChaser>(stat, pos); }

void StageInit(GameState& state);

void StageUpdate(GameState& state);
void StageRender(const GameState state);