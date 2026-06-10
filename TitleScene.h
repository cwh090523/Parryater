#pragma once
//#include <string>
#include "Console.h"
#include "GameState.h"

void InitTitle(GameState& state);
void UpdateTitle(GameState& state);
void RenderTitle(const GameState& state);


void PlayTransition();
void FlashAnimation(COORD resolution, int count, int delayMs);
void CrossAnimation(COORD resolution, int delayMs);
char RandomChar();
void MatrixAnimation(const std::string& target, int frames, int ms);