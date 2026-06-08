#pragma once
#include <string>
#include "GameState.h"
#include "Console.h"

void InitTitle(GameState& state);
void UpdateTitle(TitleData& title, GameState& state);
void RenderTitle(const TitleData& title);

void UpdateInfo(GameState& state);
void RenderInfo(const GameState& state);

void PlayTransition();
void FlashAnimation(COORD resolution, int count, int delayMs);
void CrossAnimation(COORD resolution, int delayMs);
char RandomChar();
void MatrixAnimation(const std::string& target, int frames, int ms);