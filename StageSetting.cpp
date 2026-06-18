#pragma once
#include "StageSetting.h"

void StageInit(GameState& state) {
    state.stageData.curWave = 0;
    state.stageData.enemiesRemaining = 0;
    state.stageData.lastSpawnTime = state.curTime;
    state.stageData.waves.clear();

    StageWave wave1;
    wave1.data.push_back(WaveEnemyData{
        15,            // enemyCount
        1500,           // spawnInterval
        3,             // enemyHp
        200,           // enemyMoveSpeed
        1000,          // enemyAttackSpeed
        SpawnShooter,    // 함수 포인터
        5, //spawncount
        });
    wave1.data.push_back(WaveEnemyData{
    5,            // enemyCount
    1500,           // spawnInterval
    2,             // enemyHp
    200,           // enemyMoveSpeed
    1000,          // enemyAttackSpeed
    SpawnZigzag,    // 함수 포인터
    5, //spawncount
        });
    state.stageData.waves.push_back(wave1);

    StageWave wave2;
    wave2.data.push_back(WaveEnemyData{
        15,            // enemyCount
        1500,           // spawnInterval
        3,             // enemyHp
        200,           // enemyMoveSpeed
        1000,          // enemyAttackSpeed
        SpawnRusher,    // 함수 포인터
        5, //spawncount
        });
    wave2.data.push_back(WaveEnemyData{
    5,            // enemyCount
    1500,           // spawnInterval
    2,             // enemyHp
    200,           // enemyMoveSpeed
    1000,          // enemyAttackSpeed
    SpawnZigzag,    // 함수 포인터
    5, //spawncount
        });
    state.stageData.waves.push_back(wave2);

    state.stageData.waves.emplace_back();
    state.stageData.waves.emplace_back();
}



void StageUpdate(GameState& state) {
    StageData& sd = state.stageData;

    if (sd.curWave >= (int)sd.waves.size()) return;

    StageWave& wave = sd.waves[sd.curWave];


    if (sd.curWaveEnemyDataNumber >= (int)wave.data.size()) {
        if (state.inGameData.enemies.empty()) {
            sd.curWave++;
            sd.curWaveEnemyDataNumber = 0;
            sd.enemiesRemaining = 0;
            sd.lastSpawnTime = state.curTime;
        }
        return;
    }

    WaveEnemyData& currentData = wave.data[sd.curWaveEnemyDataNumber];

    if (sd.enemiesRemaining == 0) {
        sd.enemiesRemaining = currentData.enemyCount;
    }

    if (state.curTime >= sd.lastSpawnTime + currentData.spawnInterval) {

        Stats estat;
        estat.maxHp = currentData.enemyHp;
        estat.hp = currentData.enemyHp;
        estat.MoveSpeed = (float)currentData.enemyMoveSpeed;
        estat.attackSpeed = currentData.enemyAttackSpeed;
        estat.attackPower = 1;

        int spawnX = (rand() % (GAME_WIDTH / 2)) * 2 - 1;
        auto enemy = currentData.spawner(estat, Position{ spawnX, 0 });
        enemy->lastMoveTime = state.curTime;
        state.inGameData.enemies.push_back(std::move(enemy));

        sd.enemiesRemaining--;
        sd.lastSpawnTime = state.curTime;
        if (sd.enemiesRemaining <= 0) {
            sd.curWaveEnemyDataNumber++;
        }
    }
}