#include "SettingService.h"
#include <algorithm>

void MoveSettingMenu(SettingData& setting, int direction)
{
    int index = static_cast<int>(setting.curMenu);
    index += direction;

    index = std::max((int)SettingsMenu::VOLUME, index);
    index = std::min((int)SettingsMenu::BACK, index);

    setting.curMenu = static_cast<SettingsMenu>(index);
}

void MoveSettingSelectIndex(SettingData& setting, int direction, int maxIndex)
{
    setting.selectIndex += direction;

    setting.selectIndex = std::max(0, setting.selectIndex);
    setting.selectIndex = std::min(maxIndex, setting.selectIndex);
}

void EnterSettingSubMenu(SettingData& setting)
{
    setting.isSelected = true;
    setting.selectIndex = 0;
}

void ExitSettingSubMenu(SettingData& setting)
{
    setting.isSelected = false;
    setting.selectIndex = 0;
}

void ChangeSettingVolume(SettingData& setting, int direction)
{
    if (setting.selectIndex == 0)
    {
        setting.bgmVolume += direction * 0.1f;
        setting.bgmVolume = std::max(0.0f, setting.bgmVolume);
        setting.bgmVolume = std::min(1.0f, setting.bgmVolume);
    }
    else
    {
        setting.sfxVolume += direction * 0.1f;
        setting.sfxVolume = std::max(0.0f, setting.sfxVolume);
        setting.sfxVolume = std::min(1.0f, setting.sfxVolume);
    }
}

void ChangeControlKey(SettingData& setting, int key)
{
    MovementSettingData& move = setting.movementSettingData;

    switch (setting.selectIndex)
    {
    case 0:
        move.moveUpArrowKey = key;
        break;
    case 1:
        move.moveDownArrowKey = key;
        break;
    case 2:
        move.moveLeftArrowKey = key;
        break;
    case 3:
        move.moveRightArrowKey = key;
        break;
    case 4:
        move.AttackKey = key;
        break;
    case 5:
        move.dashKey = key;
        break;
    }
}

void ResetSettingData(SettingData& setting)
{
    setting.bgmVolume = 0.5f;
    setting.sfxVolume = 0.5f;
    setting.movementSettingData = MovementSettingData();
    setting.selectIndex = 0;
}