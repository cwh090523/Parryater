#pragma once
#include "GameState.h"
#include "Console.h"
void InitTitle(GameState& state);
void UpdateTitle(GameState& state);
void RenderTitle(const GameState& state);

void UpdateInfo(GameState& state);
void RenderInfo(const GameState& state);

void PlayTransition();
void FlashAnimation(COORD resolution, int count, int delayMs);
void CrossAnimation(COORD resolution, int delayMs);
char RandomChar();
void MatirixAinimaion(const string& target, int frames, int ms);
