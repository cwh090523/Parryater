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
            w.data.push_back({ 20, 900, 2, 220, 1500, SpawnRusher, 5 });
            w.data.push_back({ 20, 900, 2, 220, 1500, SpawnZigzag, 5 });
            w.data.push_back({ 20, 900, 2, 220, 1500, SpawnRusher, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 2
        {
            StageWave w;
            w.data.push_back({ 25, 850, 2, 210, 1400, SpawnRusher, 5 });
            w.data.push_back({ 20, 850, 2, 210, 1400, SpawnZigzag, 5 });
            w.data.push_back({ 15, 850, 2, 210, 1400, SpawnShooter, 5 });
            w.data.push_back({ 20, 850, 2, 210, 1400, SpawnRusher, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 3
        {
            StageWave w;
            w.data.push_back({ 25, 800, 3, 200, 1300, SpawnShooter, 5 });
            w.data.push_back({ 20, 800, 3, 200, 1300, SpawnZigzag, 5 });
            w.data.push_back({ 20, 800, 3, 200, 1300, SpawnWaver, 5 });
            w.data.push_back({ 20, 800, 3, 200, 1300, SpawnShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 4
        {
            StageWave w;
            w.data.push_back({ 30, 750, 3, 190, 1200, SpawnWaver, 5 });
            w.data.push_back({ 25, 750, 3, 190, 1200, SpawnShooter, 5 });
            w.data.push_back({ 20, 750, 3, 190, 1200, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 750, 3, 190, 1200, SpawnZigzag, 5 });
            w.data.push_back({ 20, 750, 3, 190, 1200, SpawnWaver, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 5
        {
            StageWave w;
            w.data.push_back({ 30, 700, 4, 180, 1100, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 700, 3, 180, 1100, SpawnZigzag, 5 });
            w.data.push_back({ 20, 700, 3, 180, 1100, SpawnShooter, 5 });
            w.data.push_back({ 20, 700, 3, 180, 1100, SpawnWaver, 5 });
            w.data.push_back({ 20, 700, 4, 180, 1100, SpawnSideShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 6
        {
            StageWave w;
            w.data.push_back({ 35, 650, 4, 170, 1000, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 650, 3, 170, 1000, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 650, 3, 170, 1000, SpawnShooter, 5 });
            w.data.push_back({ 20, 650, 3, 170, 1000, SpawnZigzag, 5 });
            w.data.push_back({ 20, 650, 4, 170, 1000, SpawnTrackerX, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 7
        {
            StageWave w;
            w.data.push_back({ 35, 600, 5, 160, 900, SpawnCrossShooter, 5 });
            w.data.push_back({ 25, 600, 4, 160, 900, SpawnShooter, 5 });
            w.data.push_back({ 20, 600, 4, 160, 900, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 600, 4, 160, 900, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 600, 5, 160, 900, SpawnCrossShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 8
        {
            StageWave w;
            w.data.push_back({ 40, 600, 5, 150, 850, SpawnCrossShooter, 5 });
            w.data.push_back({ 30, 600, 4, 150, 850, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 600, 4, 150, 850, SpawnShooter, 5 });
            w.data.push_back({ 20, 600, 4, 150, 850, SpawnWaver, 5 });
            w.data.push_back({ 20, 600, 4, 150, 850, SpawnZigzag, 5 });
            w.data.push_back({ 20, 600, 5, 150, 850, SpawnCrossShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 9
        {
            StageWave w;
            w.data.push_back({ 40, 550, 6, 140, 800, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 550, 5, 140, 800, SpawnZigzag, 5 });
            w.data.push_back({ 25, 550, 5, 140, 800, SpawnShooter, 5 });
            w.data.push_back({ 20, 550, 5, 140, 800, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 550, 5, 140, 800, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 550, 6, 140, 800, SpawnRadialShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 10
        {
            StageWave w;
            w.data.push_back({ 45, 550, 6, 130, 750, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 550, 5, 130, 750, SpawnTrackerX, 5 });
            w.data.push_back({ 25, 550, 5, 130, 750, SpawnCrossShooter, 5 });
            w.data.push_back({ 20, 550, 5, 130, 750, SpawnShooter, 5 });
            w.data.push_back({ 20, 550, 5, 130, 750, SpawnZigzag, 5 });
            w.data.push_back({ 20, 550, 6, 130, 750, SpawnRadialShooter, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 11
        {
            StageWave w;
            w.data.push_back({ 40, 500, 7, 120, 700, SpawnChaser, 5 });
            w.data.push_back({ 30, 500, 6, 120, 700, SpawnCrossShooter, 5 });
            w.data.push_back({ 25, 500, 6, 120, 700, SpawnRadialShooter, 5 });
            w.data.push_back({ 20, 500, 6, 120, 700, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 500, 6, 120, 700, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 500, 7, 120, 700, SpawnChaser, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 12
        {
            StageWave w;
            w.data.push_back({ 45, 500, 7, 110, 650, SpawnChaser, 5 });
            w.data.push_back({ 30, 500, 6, 110, 650, SpawnRadialShooter, 5 });
            w.data.push_back({ 25, 500, 6, 110, 650, SpawnCrossShooter, 5 });
            w.data.push_back({ 20, 500, 6, 110, 650, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 500, 6, 110, 650, SpawnShooter, 5 });
            w.data.push_back({ 20, 500, 7, 110, 650, SpawnChaser, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 13
        {
            StageWave w;
            w.data.push_back({ 50, 450, 8, 100, 600, SpawnChaser, 5 });
            w.data.push_back({ 30, 450, 7, 100, 600, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 450, 7, 100, 600, SpawnRadialShooter, 5 });
            w.data.push_back({ 20, 450, 7, 100, 600, SpawnCrossShooter, 5 });
            w.data.push_back({ 20, 450, 7, 100, 600, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 450, 8, 100, 600, SpawnChaser, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 14
        {
            StageWave w;
            w.data.push_back({ 55, 450, 9, 90, 550, SpawnChaser, 5 });
            w.data.push_back({ 35, 450, 8, 90, 550, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 450, 8, 90, 550, SpawnCrossShooter, 5 });
            w.data.push_back({ 25, 450, 8, 90, 550, SpawnSideShooter, 5 });
            w.data.push_back({ 20, 450, 8, 90, 550, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 450, 9, 90, 550, SpawnChaser, 5 });
            state.stageData.waves.push_back(w);
        }

        // Wave 15
        {
            StageWave w;
            w.data.push_back({ 60, 400, 10, 80, 500, SpawnChaser, 5 });
            w.data.push_back({ 40, 400, 9, 80, 500, SpawnCrossShooter, 5 });
            w.data.push_back({ 35, 400, 9, 80, 500, SpawnRadialShooter, 5 });
            w.data.push_back({ 30, 400, 9, 80, 500, SpawnSideShooter, 5 });
            w.data.push_back({ 25, 400, 9, 80, 500, SpawnTrackerX, 5 });
            w.data.push_back({ 20, 400, 9, 80, 500, SpawnShooter, 5 });
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