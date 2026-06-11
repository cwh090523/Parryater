#include "Console.h"
#include "MainGameData.h" 
#include "InGameScene.h"
#include "GameState.h"
#include <cmath>
#include <algorithm> 
#include <iostream>

using namespace std;

// =================================================================
// 1. 적 스폰 팩토리 함수 정의
// =================================================================
static unique_ptr<Enemy> SpawnRusher(Stats stat, Position pos) { return make_unique<EnemyRusher>(stat, pos); }
static unique_ptr<Enemy> SpawnShooter(Stats stat, Position pos) { return make_unique<EnemyShooter>(stat, pos); }
static unique_ptr<Enemy> SpawnZigzag(Stats stat, Position pos) { return make_unique<EnemyZigzag>(stat, pos); }

// =================================================================
// 2. 스테이지 관리 로직
// =================================================================
void StageInit(GameState& state) {
    state.stageData.curWave = 0;
    state.stageData.enemiesRemaining = 0;
    state.stageData.lastSpawnTime = state.curTime;
    state.stageData.waves = {
        {  5, 1500, 3, 300, 2000, SpawnRusher  },
        {  5, 1200, 3, 280, 1800, SpawnZigzag  },
        {  8, 1000, 5, 250, 1500, SpawnShooter },
        {  8,  900, 5, 240, 1400, SpawnRusher  },
        { 10,  700, 8, 200, 1000, SpawnZigzag  },
        { 10,  600, 8, 180,  900, SpawnShooter },
    };
    state.stageData.enemiesRemaining = state.stageData.waves[0].enemyCount;
}

void StageUpdate(GameState& state) {
    StageData& sd = state.stageData;
    if (sd.curWave >= (int)sd.waves.size()) return;

    StageWave& wave = sd.waves[sd.curWave];

    if (sd.enemiesRemaining <= 0 && state.inGameData.enemies.empty()) {
        sd.curWave++;
        if (sd.curWave >= (int)sd.waves.size()) return;
        wave = sd.waves[sd.curWave];
        sd.enemiesRemaining = wave.enemyCount;
    }

    if (sd.enemiesRemaining <= 0) return;
    if (state.curTime < sd.lastSpawnTime + wave.spawnInterval) return;

    Stats estat;
    estat.maxHp = wave.enemyHp;
    estat.hp = wave.enemyHp;
    estat.MoveSpeed = (float)wave.enemyMoveSpeed;
    estat.attackSpeed = wave.enemyAttackSpeed;
    estat.attackPower = 1;

    int spawnX = (rand() % (GAME_WIDTH / 2)) * 2 - 1;
    auto enemy = wave.spawner(estat, Position{ spawnX, 0 });
    enemy->lastMoveTime = state.curTime;
    state.inGameData.enemies.push_back(std::move(enemy));

    sd.enemiesRemaining--;
    sd.lastSpawnTime = state.curTime;
}

// =================================================================
// 3. 인게임 초기화 및 충돌 판정
// =================================================================
void InGameInit(GameState& state) {
    system("cls");
    state.inGameData.isPaused = false;
    state.inGameData.isGameOver = false;
    state.inGameData.score = 0;

    state.inGameData.enemies.clear();
    state.inGameData.bullets.clear();

    // 플레이어 기본 스탯 초기화 추가
    state.inGameData.player.stats.maxHp = 10;
    state.inGameData.player.stats.hp = 10;
    state.inGameData.player.stats.attackPower = 1;
    state.inGameData.player.stats.attackSpeed = 200;
    state.inGameData.player.pos = { 55, 35 };
    state.inGameData.player.floatPos = { 55.0f, 35.0f };
    state.inGameData.player.prevPos = { 55, 35 };
    state.inGameData.player.stats.MoveSpeed = 50;
    state.inGameData.player.lastMoveTime = state.curTime;
    state.inGameData.player.lastAttackTime = state.curTime;

    StageInit(state);
}

void InGameCollision(GameState& state) {
    Player& player = state.inGameData.player;

    for (Bullet& bullet : state.inGameData.bullets) {
        if (!bullet.isActive) continue;

        // 적 총알 -> 플레이어 충돌 체크
        if (bullet.type != ProjectileType::Player) {
            if (abs(bullet.pos.x - player.pos.x) <= 1 && bullet.pos.y == player.pos.y) {
                if (!player.IsDashing(state.curTime)) {
                    bullet.isActive = false; // 맞은 총알 비활성화 추가
                    player.stats.hp -= bullet.damage;
                    ShakeConsoleWindow(5, 50, 25);
                    if (player.stats.hp <= 0) {
                        state.inGameData.isGameOver = true;
                    }
                }
                else {
                    // 대시로 투사체 파괴 처리 시
                    ShakeConsoleWindow(10, 100, 25);
                    bullet.isActive = false;
                }
            }
        }

        // 플레이어 총알 -> 적 충돌 체크
        for (auto& enemy : state.inGameData.enemies) {
            if (!enemy->isAlive) continue;
            if (bullet.type == ProjectileType::Player) {
                if (abs(bullet.pos.x - enemy->pos.x) <= 1 && bullet.pos.y == enemy->pos.y) {
                    bullet.isActive = false;
                    enemy->stats.hp -= player.stats.attackPower;
                    if (enemy->stats.hp <= 0) {
                        enemy->isAlive = false;
                        state.inGameData.score += 100;
                    }
                    break;
                }
            }
        }
    }

    // 적 캐릭터 -> 플레이어 충돌 체크
    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;
        if (abs(enemy->pos.x - player.pos.x) <= 1 && enemy->pos.y == player.pos.y) {
            if (!player.IsDashing(state.curTime)) {
                player.stats.hp--;
                ShakeConsoleWindow(5, 50, 25);
                if (player.stats.hp <= 0) {
                    state.inGameData.isGameOver = true;
                }
            }
            else {
                // 플레이어가 대시로 몸통 박치기 시 적에게 데미지
                enemy->stats.hp -= player.stats.attackPower;
                ShakeConsoleWindow(10, 100, 25);
                if (enemy->stats.hp <= 0) {
                    enemy->isAlive = false;
                    state.inGameData.score += 100;
                }
            }
        }
    }
}

// =================================================================
// 4. 업데이트 루프 메인
// =================================================================
void InGameUpdate(GameState& state) {
    if (GetKeyDown(VK_ESCAPE)) { state.isRunning = false; return; }
    if (state.inGameData.isGameOver) { state.curScene = Scene::GAMEOVER; return; }

    Player& player = state.inGameData.player;
    MovementSettingData& msd = state.settingData.movementSettingData;

    player.lastMoveDir = player.moveDir;
    player.moveDir = { 0, 0 };

    // 키 입력 버그 수정 (ArrowKey 매핑 누락 복구 및 중복 제거)
    if (GetKey(VK_UP) || GetKey(msd.moveUpArrowKey))    player.moveDir.y = -1;
    if (GetKey(VK_DOWN) || GetKey(msd.moveDownArrowKey))  player.moveDir.y = 1;
    if (GetKey(VK_LEFT) || GetKey(msd.moveLeftArrowKey))  player.moveDir.x = -1;
    if (GetKey(VK_RIGHT) || GetKey(msd.moveRightArrowKey)) player.moveDir.x = 1;
    if (GetKeyDown(msd.dashKey)) DashPlayer(state);

    // 1. 플레이어 및 스테이지 상태 업데이트
    PlayerMove(state);
    PlayerAttack(state);
    StageUpdate(state);

    // 2. 총알 및 적 객체들 개별 프레임 이동 업데이트
    for (Bullet& bullet : state.inGameData.bullets) {
        if (bullet.isActive) {
            bullet.ProjectileUpdate(state);
        }
    }
    for (auto& enemy : state.inGameData.enemies) {
        if (enemy->isAlive) {
            enemy->EnemyUpdate(state);
        }
    }

    // 3. 이동 연산이 모두 끝난 최종 좌표 기준 충돌 처리
    InGameCollision(state);

    // 4. 비활성화된 총알 메모리 및 화면 잔상 정리
    auto iter = state.inGameData.bullets.begin();
    while (iter != state.inGameData.bullets.end()) {
        if (!iter->isActive) {
            iter = state.inGameData.bullets.erase(iter);
        }
        else {
            ++iter;
        }
    }

    // 5. 죽은 적 메모리 및 화면 잔상 정리 (루프 꼬임 방지 고착화)
    auto iter2 = state.inGameData.enemies.begin();
    while (iter2 != state.inGameData.enemies.end()) {
        if ((*iter2)->isAlive) {
            ++iter2;
        }
        else {
            GotoXY((*iter2)->prevPos.x, (*iter2)->prevPos.y); cout << " ";
            GotoXY((*iter2)->pos.x, (*iter2)->pos.y);         cout << " ";
            iter2 = state.inGameData.enemies.erase(iter2);
        }
    }
}

// =================================================================
// 5. 렌더링 및 사후 업데이트
// =================================================================
void InGameRender(const GameState& state) {
    const Player& player = state.inGameData.player;

    RenderBorder();
    RenderUI(state);

    SetUnicodeMode();

    // 1. 적 그리기
    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;
        GotoXY(enemy->prevPos.x, enemy->prevPos.y);
        wcout << L" ";
        GotoXY(enemy->pos.x, enemy->pos.y);
        if (dynamic_cast<EnemyShooter*>(enemy.get()))     SetColor(Color::SKYBLUE);
        else if (dynamic_cast<EnemyZigzag*>(enemy.get())) SetColor(Color::YELLOW);
        else                                              SetColor(Color::RED);
        wcout << L"▼";
        SetColor();
    }

    // 2. 총알 그리기
    for (const Bullet& bullet : state.inGameData.bullets) {
        GotoXY(bullet.prevPos.x, bullet.prevPos.y);
        wcout << L" ";
        if (bullet.isActive) {
            GotoXY(bullet.pos.x, bullet.pos.y);
            SetColor(bullet.type == ProjectileType::Player ? Color::LIGHT_RED : Color::LIGHT_YELLOW);
            wcout << L"●";
        }
    }

    // 3. 플레이어 그리기
    GotoXY(player.prevPos.x, player.prevPos.y);
    wcout << L" ";
    SetColor(player.IsDashing(state.curTime) ? Color::WHITE : Color::LIGHT_GREEN);
    GotoXY(player.pos.x, player.pos.y);
    wcout << L"▲";

    SetDeraultMode();
    SetColor();
}

void InGameAfterUpdate(GameState& state) {
    state.inGameData.player.prevPos = state.inGameData.player.pos;
    for (Bullet& bullet : state.inGameData.bullets) {
        bullet.prevPos = bullet.pos;
    }
    for (auto& enemy : state.inGameData.enemies) {
        enemy->prevPos = enemy->pos;
    }
}

// =================================================================
// 6. 플레이어 서브 액션 (대시, 이동, 공격, UI)
// =================================================================
void DashPlayer(GameState& state) {
    Player& player = state.inGameData.player;
    if (!player.CanDash(state.curTime)) return;

    player.dashStartTime = state.curTime;
    player.dashEndTime = state.curTime + 200;
    player.dashCooldownEndTime = state.curTime + player.stats.DashCooldown;
}

void PlayerMove(GameState& state) {
    Player& player = state.inGameData.player;

    // 삼항 연산자 우선순위 버그 수정: 전체 조건 나눗셈을 괄호 분리 처리
    int speedDivider = player.IsDashing(state.curTime) ? 2 : 1;
    if (state.curTime < player.lastMoveTime + ((ULONGLONG)player.stats.MoveSpeed / speedDivider)) return;
    if (player.moveDir.x == 0 && player.moveDir.y == 0) return;

    player.pos.x += player.moveDir.x * 2;
    player.pos.y += player.moveDir.y;

    player.pos.x = std::max(0, std::min(player.pos.x, GAME_WIDTH - 1));
    player.pos.y = std::max(0, std::min(player.pos.y, HEIGHT - 1));

    player.lastMoveTime = state.curTime;
}

void PlayerAttack(GameState& state) {
    Player& player = state.inGameData.player;
    if (GetKey(state.settingData.movementSettingData.SelectKey)) {
        if (state.curTime >= player.lastAttackTime + (ULONGLONG)player.stats.attackSpeed) {
            Bullet bullet(player.pos, Position{ 0,-1 }, player.stats.attackPower, 20.0f, 3000, ProjectileType::Player);
            bullet.spawnTime = state.curTime;
            state.inGameData.bullets.push_back(bullet);
            player.lastAttackTime = state.curTime;
        }
    }
}

void RenderBorder() {
    SetColor(Color::WHITE);
    for (int y = 0; y < HEIGHT; ++y) {
        GotoXY(UI_X - 2, y);
        cout << "|";
    }
    SetColor();
}

void RenderUI(const GameState& state) {
    const Player& player = state.inGameData.player;
    const InGameData& data = state.inGameData;

    SetColor(Color::LIGHT_YELLOW);
    GotoXY(UI_X, 2);
    cout << "SCORE";
    SetColor(Color::WHITE);
    GotoXY(UI_X, 3);
    cout << data.score;

    GotoXY(UI_X, 6);
    SetColor(Color::LIGHT_YELLOW);
    cout << "STAGE";
    SetColor(Color::WHITE);
    GotoXY(UI_X, 7);
    cout << state.stageData.curWave + 1;

    DrawBar(UI_X, 10, "HP", player.stats.hp, player.stats.maxHp, 10);

    GotoXY(UI_X, 14);
    SetColor(Color::LIGHT_YELLOW);
    cout << "STATS";
    SetColor(Color::WHITE);
    GotoXY(UI_X, 15);
    cout << "ATK : " << player.stats.attackPower;
    GotoXY(UI_X, 16);
    cout << "SPD : " << (int)player.stats.MoveSpeed;
    GotoXY(UI_X, 17);
    cout << "DASH: " << (player.CanDash(state.curTime) ? "READY" : "COOL ");

    SetColor();
}