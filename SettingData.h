#pragma once
#define NOMINMAX

#include <Windows.h>
#include "Enums.h"

struct MovementSettingData
{
    int moveUpArrowKey = 'W';
    int moveDownArrowKey = 'S';
    int moveLeftArrowKey = 'A';
    int moveRightArrowKey = 'D';

    int attackKey = 'Q';
    int dashKey = VK_SPACE;
};

struct SettingData
{
    SettingsMenu curMenu = SettingsMenu::VOLUME;

    bool isSelected = false;
    int selectIndex = 0;

    float bgmVolume = 0.5f;
    float sfxVolume = 0.5f;

    MovementSettingData movementSettingData;
};