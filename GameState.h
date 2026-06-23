#pragma once
#define NOMINMAX
#include <Windows.h>
#include <vector>
#include <memory>
#include <string>
#include "Enums.h"
#include "MainGameData.h"
#include "SettingData.h"


constexpr int WIDTH = 160;
constexpr int HEIGHT = 45;

constexpr int GAME_WIDTH = 80;
constexpr int UI_X = 83;


struct TitleData
{
    Menu curMenu = Menu::START;
};

struct InGameData
{
    bool isGamming = false;
    bool isPaused = false;
    bool isGameOver = false;
    int score = 0;
    Player player;
    vector<unique_ptr<Enemy>> enemies;
    vector<unique_ptr<DecoObject>> decoObject;
    vector<unique_ptr<DecoObject>> decoSpawnQueue;
    vector<Bullet> bullets;
};
struct WaveEnemyData {

    int enemyCount;
    ULONGLONG spawnInterval;
    int enemyHp;
    int enemyMoveSpeed;
    int enemyAttackSpeed;
    unique_ptr<Enemy>(*spawner)(Stats, Position);
    int spawnCount;
};
struct StageWave {
    vector<WaveEnemyData> data;
    StageWave() = default;
    StageWave(initializer_list<WaveEnemyData> init) : data(init) {}
};
struct ShopData
{
    int selectedIndex = 0;
    std::string message = "";
    Scene returnScene = Scene::INGAME;
};
struct StageData {
    int curStage = 1;
    int curWave = 0;
    int curWaveEnemyDataNumber = 0;
    int enemiesRemaining = 0;
    ULONGLONG lastSpawnTime = 0;
    vector<StageWave> waves;
    bool isEndless = false;
    ULONGLONG endlessStartTime = 0;
    ULONGLONG lastEndlessSpawnTime = 0;
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

