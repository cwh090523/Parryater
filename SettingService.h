#pragma once
#include "SettingData.h"

void MoveSettingMenu(SettingData& setting, int direction);
void MoveSettingSelectIndex(SettingData& setting, int direction, int maxIndex);

void EnterSettingSubMenu(SettingData& setting);
void ExitSettingSubMenu(SettingData& setting);

void ChangeSettingVolume(SettingData& setting, int direction);
void ChangeControlKey(SettingData& setting, int key);

void ResetSettingData(SettingData& setting);