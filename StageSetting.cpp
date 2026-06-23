#pragma once
#include "StageSetting.h"
#include "SoundManager.h"
void StageInit(GameState& state) {
    if (!state.inGameData.isGamming) {
        state.stageData.curWave = 0;
        state.stageData.enemiesRemaining = 0;
        state.stageData.lastSpawnTime = state.curTime;
        state.stageData.waves.clear();

        // Wave 1
        {
            StageWave w;
            w.data.push_back({ 20, 900, 10, 220, 1500, SpawnRusher, 5 });
            w.data.push_back({ 20, 900, 10, 220, 1500, SpawnZigzag, 5 });
            w.data.push_back({ 20, 900, 10, 220, 1500, SpawnRusher, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 2
        {
            StageWave w;
            w.data.push_back({ 25, 880, 16, 218, 1475, SpawnRusher, 5 });
            w.data.push_back({ 20, 880, 16, 218, 1475, SpawnZigzag, 5 });
            w.data.push_back({ 15, 880, 16, 218, 1475, SpawnShooter, 5 });
            w.data.push_back({ 20, 880, 16, 218, 1475, SpawnRusher, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 3
        {
            StageWave w;
            w.data.push_back({ 25, 860, 22, 216, 1450, SpawnShooter, 5 });
            w.data.push_back({ 20, 860, 22, 216, 1450, SpawnZigzag, 5 });
            w.data.push_back({ 20, 860, 22, 216, 1450, SpawnWaver, 5 });
            w.data.push_back({ 20, 860, 22, 216, 1450, SpawnShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 4
        {
            StageWave w;
            w.data.push_back({ 30, 840, 28, 214, 1425, SpawnWaver, 5 });
            w.data.push_back({ 25, 840, 28, 214, 1425, SpawnShooter, 5 });
            w.data.push_back({ 20, 840, 28, 214, 1425, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 840, 28, 214, 1425, SpawnZigzag, 5 });
            w.data.push_back({ 20, 840, 28, 214, 1425, SpawnWaver, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 5
        {
            StageWave w;
            w.data.push_back({ 30, 820, 36, 212, 1400, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 820, 36, 212, 1400, SpawnZigzag, 5 });
            w.data.push_back({ 20, 820, 36, 212, 1400, SpawnShooter, 5 });
            w.data.push_back({ 20, 820, 36, 212, 1400, SpawnWaver, 5 });
            w.data.push_back({ 20, 820, 36, 212, 1400, SpawnSideShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 6
        {
            StageWave w;
            w.data.push_back({ 35, 800, 44, 210, 1375, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 800, 44, 210, 1375, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 800, 44, 210, 1375, SpawnShooter, 5 });
            w.data.push_back({ 20, 800, 44, 210, 1375, SpawnZigzag, 5 });
            w.data.push_back({ 20, 800, 44, 210, 1375, SpawnTrackerX, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 7
        {
            StageWave w;
            w.data.push_back({ 35, 780, 52, 208, 1350, SpawnCrossShooter, 5 });
            w.data.push_back({ 25, 780, 52, 208, 1350, SpawnShooter, 5 });
            w.data.push_back({ 20, 780, 52, 208, 1350, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 780, 52, 208, 1350, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 780, 52, 208, 1350, SpawnCrossShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 8
        {
            StageWave w;
            w.data.push_back({ 40, 760, 62, 206, 1325, SpawnCrossShooter, 5 });
            w.data.push_back({ 30, 760, 62, 206, 1325, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 760, 62, 206, 1325, SpawnShooter, 5 });
            w.data.push_back({ 20, 760, 62, 206, 1325, SpawnWaver, 5 });
            w.data.push_back({ 20, 760, 62, 206, 1325, SpawnZigzag, 5 });
            w.data.push_back({ 20, 760, 62, 206, 1325, SpawnCrossShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 9
        {
            StageWave w;
            w.data.push_back({ 40, 740, 72, 204, 1300, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 740, 72, 204, 1300, SpawnZigzag, 5 });
            w.data.push_back({ 25, 740, 72, 204, 1300, SpawnShooter, 5 });
            w.data.push_back({ 20, 740, 72, 204, 1300, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 740, 72, 204, 1300, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 740, 72, 204, 1300, SpawnRadialShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 10
        {
            StageWave w;
            w.data.push_back({ 45, 720, 82, 202, 1275, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 720, 82, 202, 1275, SpawnTrackerX, 5 });
            w.data.push_back({ 25, 720, 82, 202, 1275, SpawnCrossShooter, 5 });
            w.data.push_back({ 20, 720, 82, 202, 1275, SpawnShooter, 5 });
            w.data.push_back({ 20, 720, 82, 202, 1275, SpawnZigzag, 5 });
            w.data.push_back({ 20, 720, 82, 202, 1275, SpawnRadialShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 11
        {
            StageWave w;
            w.data.push_back({ 50, 700, 94, 200, 1250, SpawnChaser, 5 });
            w.data.push_back({ 30, 700, 94, 200, 1250, SpawnCrossShooter, 5 });
            w.data.push_back({ 25, 700, 94, 200, 1250, SpawnRadialShooter, 5 });
            w.data.push_back({ 20, 700, 94, 200, 1250, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 700, 94, 200, 1250, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 700, 94, 200, 1250, SpawnShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 12
        {
            StageWave w;
            w.data.push_back({ 50, 680, 106, 198, 1225, SpawnChaser, 5 });
            w.data.push_back({ 30, 680, 106, 198, 1225, SpawnRadialShooter, 5 });
            w.data.push_back({ 25, 680, 106, 198, 1225, SpawnCrossShooter, 5 });
            w.data.push_back({ 20, 680, 106, 198, 1225, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 680, 106, 198, 1225, SpawnShooter, 5 });
            w.data.push_back({ 20, 680, 106, 198, 1225, SpawnChaser, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 13
        {
            StageWave w;
            w.data.push_back({ 55, 660, 118, 196, 1200, SpawnChaser, 5 });
            w.data.push_back({ 35, 660, 118, 196, 1200, SpawnSideShooter, 5 });
            w.data.push_back({ 30, 660, 118, 196, 1200, SpawnRadialShooter, 5 });
            w.data.push_back({ 25, 660, 118, 196, 1200, SpawnCrossShooter, 5 });
            w.data.push_back({ 20, 660, 118, 196, 1200, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 660, 118, 196, 1200, SpawnChaser, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 14
        {
            StageWave w;
            w.data.push_back({ 55, 640, 130, 194, 1175, SpawnChaser, 5 });
            w.data.push_back({ 35, 640, 130, 194, 1175, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 640, 130, 194, 1175, SpawnCrossShooter, 5 });
            w.data.push_back({ 25, 640, 130, 194, 1175, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 640, 130, 194, 1175, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 640, 130, 194, 1175, SpawnChaser, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 15
        {
            StageWave w;
            w.data.push_back({ 60, 620, 142, 192, 1150, SpawnChaser, 5 });
            w.data.push_back({ 40, 620, 142, 192, 1150, SpawnCrossShooter, 5 });
            w.data.push_back({ 35, 620, 142, 192, 1150, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 620, 142, 192, 1150, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 620, 142, 192, 1150, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 620, 142, 192, 1150, SpawnShooter, 5 });
            state.stageData.waves.push_back(w);
        }
    }
}







void StageUpdate(GameState& state) {
    StageData& sd = state.stageData;

    if (sd.curWave >= 15) {
        if (!sd.isEndless) {
            sd.isEndless = true;
            sd.endlessStartTime = state.curTime;
            sd.lastEndlessSpawnTime = state.curTime;
            SOUND->PlayBGM("Stage15+");
        }
    }

    if (sd.isEndless) {
        ULONGLONG elapsed = state.curTime - sd.endlessStartTime;

        float difficulty = 1.0f + (elapsed / 15000.0f);

        int spawnInterval = 750;

        if (state.curTime >= sd.lastEndlessSpawnTime + spawnInterval) {

            int spawnCount = 1 + (int)(difficulty / 2); 

            for (int i = 0; i < spawnCount; ++i) {

                int spawnX = (rand() % (GAME_WIDTH / 2)) * 2;

                int r = rand() % 100;

                unique_ptr<Enemy> enemy;

                Stats estat;
                if (r < 30) {
                    estat = { 3,3,1,1200,200,0,0 };
                    enemy = SpawnRusher(estat, { spawnX,0 });
                }
                else if (r < 45) {
                    estat = { 3,3,1,1000,200,0,0 };
                    enemy = SpawnZigzag(estat, { spawnX,0 });
                }
                else if (r < 60) {
                    estat = { 4,4,1,900,180,0,0 };
                    enemy = SpawnShooter(estat, { spawnX,0 });
                }
                else if (r < 70) {
                    estat = { 4,4,1,900,180,0,0 };
                    enemy = SpawnWaver(estat, { spawnX,0 });
                }
                else if (r < 80) {
                    estat = { 5,5,1,800,170,0,0 };
                    enemy = SpawnSideShooter(estat, { spawnX,0 });
                }
                else if (r < 85) {
                    estat = { 6,6,1,700,160,0,0 };
                    enemy = SpawnCrossShooter(estat, { spawnX,0 });
                }
                else if (r < 88) {
                    estat = { 6,6,1,700,150,0,0 };
                    enemy = SpawnRadialShooter(estat, { spawnX,0 });
                }
                else if (r < 95) {
                    estat = { 5,5,1,800,160,0,0 };
                    enemy = SpawnTrackerX(estat, { spawnX,0 });
                }
                else {
                    estat = { 8,8,1,600,140,0,0 };
                    enemy = SpawnChaser(estat, { spawnX,0 });
                }

                enemy->lastMoveTime = state.curTime;
                state.inGameData.enemies.push_back(std::move(enemy));
            }

            sd.lastEndlessSpawnTime = state.curTime;
        }

        return;
    }

    if (sd.curWave >= (int)sd.waves.size()) return;

    StageWave& wave = sd.waves[sd.curWave];


    if (sd.curWaveEnemyDataNumber >= (int)wave.data.size()) {
        if (state.inGameData.enemies.empty()) {
            sd.curWave++;

            if (sd.curWave == 4) {
                SOUND->PlayBGM("Stage4+");
            }
            else if (sd.curWave == 7) {
                SOUND->PlayBGM("Stage7+");
            }
            else if (sd.curWave == 10) {
                SOUND->PlayBGM("Stage10+");
            }
 

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
void StageRender(const GameState state) {

}