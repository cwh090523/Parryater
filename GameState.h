#pragma once
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <memory>
#include "Enums.h"
#include "MainGameData.h"
#include "SettingData.h"


constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

constexpr int GAME_WIDTH = 110;
constexpr int UI_X = 113;

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

struct StageWave {
    int enemyCount;
    ULONGLONG spawnInterval;
    int enemyHp;
    int enemyMoveSpeed;
    int enemyAttackSpeed;
    unique_ptr<Enemy>(*spawner)(Stats, Position);
};
struct ShopData {};
struct StageData {
    int curStage = 1;
    int curWave = 0;
    int enemiesRemaining = 0;
    ULONGLONG lastSpawnTime = 0;
    vector<StageWave> waves;
};
struct GameState
{
    Scene prevScene = Scene::NONE;
    Scene curScene = Scene::TITLE;
    bool isRunning = true;
    TitleData titleData;
    SettingData settingData;
    StageData stageData;
    InGameData inGameData;
    ShopData shopData;
    ULONGLONG curTime = 0;
};

