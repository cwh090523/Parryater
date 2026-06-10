#pragma once
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <memory>
#include "Enums.h"
#include "MainGameData.h"


constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

struct MovementSettingData
{
    char moveUpKey = 'W';
    char moveDownKey = 'S';
    char moveLeftKey = 'A';
    char moveRightKey = 'D';
    char moveUpArrowKey = VK_UP;
    char moveDownArrowKey = VK_DOWN;
    char moveLeftArrowKey = VK_LEFT;
    char moveRightArrowKey = VK_RIGHT;
    char SelectKey = 'Q';
    char BombKey = 'E';
    char dashKey = VK_SPACE;
};

struct SettingData
{
    SettingsMenu curMenu = SettingsMenu::VOLUME;
    bool isSelected = false;
    int selectIndex = 0;
    float bgmVolume = 0.5f;
    float sfxVolume = 0.5f;
    MovementSettingData movementSettingData;

    void MovecurMenu(int direction) {
        selectIndex += direction;
        if (selectIndex < 0) selectIndex = 0;
        else if (selectIndex > static_cast<int>(SettingsMenu::BACK))
            selectIndex = static_cast<int>(SettingsMenu::BACK);

        curMenu = static_cast<SettingsMenu>(selectIndex);
    }

    void SelectMenu() {
        if (curMenu == SettingsMenu::RESET) {
            ResetSettings();
            return;
        }
        isSelected = !isSelected;
    }

    void ResetSettings() {
        bgmVolume = 0.5f;
        sfxVolume = 0.5f;
        movementSettingData = MovementSettingData();
    }
};

struct TitleData
{
    Menu curMenu = Menu::START;
};

struct InGameData
{
    bool isPaused = false;
    bool isGameOver = false;
    int score = 0;
    Player player;
    vector<unique_ptr<Enemy>> enemies;
    vector<Bullet> bullets;
};

struct ShopData {};
struct StageData {};

struct GameState
{
    Scene prevScene = Scene::NONE;
    Scene curScene = Scene::INGAME;
    bool isRunning = true;
    TitleData titleData;
    SettingData settingData;
    InGameData inGameData;
    ShopData shopData;
    ULONGLONG curTime = 0;
};