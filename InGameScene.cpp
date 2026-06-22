#include "Console.h"
#include "MainGameData.h" 
#include "InGameScene.h"
#include "StageSetting.h"
#include "GameState.h"
#include <cmath>
#include <algorithm> 
#include <iostream>
#include "SoundManager.h"
using namespace std;

void InGameInit(GameState& state) {
    
    system("cls");
    state.inGameData.isPaused = false;
    state.inGameData.isGameOver = false;
    state.inGameData.score = 0;

    state.inGameData.enemies.clear();
    state.inGameData.bullets.clear();
    if (!state.inGameData.isGamming) {

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
    state.inGameData.player.invisibleEndTime = 0;
    state.inGameData.isGamming = true;

    }

    StageInit(state);
}

void InGameCollision(GameState& state) {
    Player& player = state.inGameData.player;
    bool playerInvincible = player.IsDashing(state.curTime) || state.curTime < player.invisibleEndTime;

    for (Bullet& bullet : state.inGameData.bullets) {
        if (!bullet.isActive) continue;

        if (bullet.type == ProjectileType::Player) {
            for (auto& enemy : state.inGameData.enemies) {
                if (!enemy->isAlive) continue;

                int minEnemyX = min(enemy->prevPos.x, enemy->pos.x) - 1;
                int maxEnemyX = max(enemy->prevPos.x, enemy->pos.x) + 1;
                int minEnemyY = min(enemy->prevPos.y, enemy->pos.y) - 1;
                int maxEnemyY = max(enemy->prevPos.y, enemy->pos.y) + 1;

                int minBulletX = min(bullet.prevPos.x, bullet.pos.x);
                int maxBulletX = max(bullet.prevPos.x, bullet.pos.x);
                int minBulletY = min(bullet.prevPos.y, bullet.pos.y);
                int maxBulletY = max(bullet.prevPos.y, bullet.pos.y);
                
                if (maxBulletX >= minEnemyX && minBulletX <= maxEnemyX && maxBulletY >= minEnemyY && minBulletY <= maxEnemyY) {
                    bullet.isActive = false;
                    enemy->stats.hp -= player.stats.attackPower;
                    if (enemy->stats.hp <= 0) {
                        enemy->isAlive = false;
                        state.inGameData.score += 100;
                        SOUND->PlaySFX("damage3");
                    }
                    break;
                }
            }
        }
        else {
            int minPlayerX = min(player.prevPos.x, player.pos.x) - 1;
            int maxPlayerX = max(player.prevPos.x, player.pos.x) + 1;
            int minPlayerY = min(player.prevPos.y, player.pos.y) - 1;
            int maxPlayerY = max(player.prevPos.y, player.pos.y) + 1;

            int minBulletX = min(bullet.prevPos.x, bullet.pos.x);
            int maxBulletX = max(bullet.prevPos.x, bullet.pos.x);
            int minBulletY = min(bullet.prevPos.y, bullet.pos.y);
            int maxBulletY = max(bullet.prevPos.y, bullet.pos.y);

            if (maxBulletX >= minPlayerX && minBulletX <= maxPlayerX && maxBulletY >= minPlayerY && minBulletY <= maxPlayerY) {
                if (player.IsDashing(state.curTime)) {
                    ShakeConsoleWindow(15, 45, 15);
                    bullet.moveDir.x *=-1;
                    bullet.moveDir.y *=-1;
                    bullet.type = ProjectileType::Player;
                    bullet.damage += player.stats.attackPower * 10;
                    bullet.MoveSpeed /= 2;
                    player.invisibleEndTime = state.curTime + 800;
                    player.dashCooldownEndTime = state.curTime;
                    state.inGameData.score += 200;
                    auto wave = new WaveDeco(state, Color::WHITE, 50, player.pos, 2, 0);
                    state.inGameData.decoObject.push_back(std::unique_ptr<DecoObject>(wave));
                    SOUND->PlaySFX("damage3");
                }
                else if (!playerInvincible) {
                bullet.isActive = false;
                    player.stats.hp -= bullet.damage;
                    player.invisibleEndTime = state.curTime + 500;
                    ShakeConsoleWindow(5, 50, 25);
                    SOUND->PlaySFX("damage3");
                    if (player.stats.hp <= 0) state.inGameData.isGameOver = true;
                }
            }
        }
    }

    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;

        int range = player.IsDashing(state.curTime) ? 1 : 0;

        int minPlayerX = min(player.prevPos.x, player.pos.x) - range * 2;
        int maxPlayerX = max(player.prevPos.x, player.pos.x) + range * 2;
        int minPlayerY = min(player.prevPos.y, player.pos.y) - range;
        int maxPlayerY = max(player.prevPos.y, player.pos.y) + range;

        int minEnemyX = min(enemy->prevPos.x, enemy->pos.x);
        int maxEnemyX = max(enemy->prevPos.x, enemy->pos.x);
        int minEnemyY = min(enemy->prevPos.y, enemy->pos.y);
        int maxEnemyY = max(enemy->prevPos.y, enemy->pos.y);

        if (maxEnemyX >= minPlayerX && minEnemyX <= maxPlayerX &&
            maxEnemyY >= minPlayerY && minEnemyY <= maxPlayerY) {

            if (player.IsDashing(state.curTime)) {
                ShakeConsoleWindow(50, 30, 10);
                player.invisibleEndTime = state.curTime + 1000;
                player.dashCooldownEndTime = state.curTime;
                auto wave = new WaveDeco(state, Color::WHITE, 50, player.pos, 2, 0);
                state.inGameData.decoObject.push_back(std::unique_ptr<DecoObject>(wave));

                state.inGameData.score += 300;

                const_cast<Enemy*>(enemy.get())->stats.hp -= (player.stats.attackPower * 3);
                if (enemy->stats.hp <= 0) {
                    const_cast<Enemy*>(enemy.get())->isAlive = false;
                    state.inGameData.score += 100;
                }
            }
            else if (!playerInvincible) {
                player.stats.hp--;
                player.invisibleEndTime = state.curTime + 500;
                SetColor(Color::WHITE, Color::LIGHT_RED);
                system("cls");
                ShakeConsoleWindow(50, 50, 10);

                SetColor();
                system("cls");
                if (player.stats.hp <= 0) state.inGameData.isGameOver = true;
            }
        }
    }
}

void InGameUpdate(GameState& state) {
    if (GetKeyDown(VK_ESCAPE)) { state.isRunning = false; return; }
    if (state.inGameData.isGameOver) { state.curScene = Scene::GAMEOVER; return; }
    if (GetKeyDown('B'))
    {
        state.curScene = Scene::SHOP;
        return;
    }
    if (GetKeyDown(VK_TAB))
    {
        state.settingData.returnScene = state.curScene;
        state.curScene = Scene::SETTING;
        return;
    }

    Player& player = state.inGameData.player;
    MovementSettingData& msd = state.settingData.movementSettingData;

    player.lastMoveDir = player.moveDir;
    player.moveDir = { 0, 0 };

    if (GetKey(VK_UP) || GetKey(msd.moveUpArrowKey))    player.moveDir.y = -1;
    if (GetKey(VK_DOWN) || GetKey(msd.moveDownArrowKey))  player.moveDir.y = 1;
    if (GetKey(VK_LEFT) || GetKey(msd.moveLeftArrowKey))  player.moveDir.x = -1;
    if (GetKey(VK_RIGHT) || GetKey(msd.moveRightArrowKey)) player.moveDir.x = 1;
    if (GetKeyDown(msd.dashKey)) DashPlayer(state);

    PlayerMove(state);
    PlayerAttack(state);
    StageUpdate(state);

    for (Bullet& bullet : state.inGameData.bullets) {
        if (bullet.isActive) {
            bullet.ProjectileUpdate(state);
            if (bullet.pos.y < 0 || bullet.pos.y >= HEIGHT || bullet.pos.x < 0 || bullet.pos.x >= GAME_WIDTH) {
                bullet.isActive = false;
            }
        }
    }
    for (auto& enemy : state.inGameData.enemies) {
        if (enemy->isAlive) {
            enemy->EnemyUpdate(state);
        }
    }
    for (auto& deco : state.inGameData.decoObject) {
        if (deco->isActive) {
            deco->DecoUpdate(state);
        }
    }
    InGameCollision(state);

    auto iter = state.inGameData.bullets.begin();
    while (iter != state.inGameData.bullets.end()) {
        if (!iter->isActive) {
            GotoXY(iter->prevPos.x, iter->prevPos.y); cout << " ";
            GotoXY(iter->pos.x, iter->pos.y);         cout << " ";
            iter = state.inGameData.bullets.erase(iter);
        }
        else {
            ++iter;
        }
    }auto iter2 = state.inGameData.enemies.begin();
    while (iter2 != state.inGameData.enemies.end()) {
        if ((*iter2)->isAlive) {
            ++iter2;
        }
        else {
            
            auto ClearPos = [](Position p) {
                if (p.x >= 0 && p.x < GAME_WIDTH && p.y >= 0 && p.y < HEIGHT) {
                    GotoXY(p.x, p.y); cout << " ";
                }
                };
            ClearPos((*iter2)->prevPos);
            ClearPos((*iter2)->pos);

            iter2 = state.inGameData.enemies.erase(iter2);
        }
    }
    auto iter3 = state.inGameData.decoObject.begin();
    while (iter3 != state.inGameData.decoObject.end()) {
        if ((*iter3)->isActive) {
            ++iter3;
        }
        else {

            auto ClearPos = [](Position p) {
                if (p.x >= 0 && p.x < GAME_WIDTH && p.y >= 0 && p.y < HEIGHT) {
                    GotoXY(p.x, p.y); cout << " ";
                }
                };
            ClearPos((*iter3)->prevPos);
            ClearPos((*iter3)->pos);

            iter3 = state.inGameData.decoObject.erase(iter3);
        }
    }
    for (auto& deco : state.inGameData.decoObject) {
        if (deco->isActive) deco->DecoUpdate(state);
    }
    if (!state.inGameData.decoSpawnQueue.empty()) {
        for (auto& newDeco : state.inGameData.decoSpawnQueue) {
            state.inGameData.decoObject.push_back(std::move(newDeco));
        }
        state.inGameData.decoSpawnQueue.clear();
    }
}

void InGameRender(const GameState& state) {
    const Player& player = state.inGameData.player;

    RenderBorder();
    RenderUI(state);

    SetUnicodeMode();


    for (const auto& deco : state.inGameData.enemies) {
        GotoXY(deco->prevPos.x, deco->prevPos.y);
        wcout << L"  ";
    }

    for (const auto& enemy : state.inGameData.enemies) {
        GotoXY(enemy->prevPos.x, enemy->prevPos.y);
        wcout << L"  ";
    }
    for (const Bullet& bullet : state.inGameData.bullets) {
        GotoXY(bullet.prevPos.x, bullet.prevPos.y);
        wcout << L"  ";
    }
    GotoXY(player.prevPos.x, player.prevPos.y);
    wcout << L" ";
    for (const auto& deco : state.inGameData.decoObject) {
        if (!deco->isActive) continue;
        if (deco->prevPos.x >= 0 && deco->prevPos.x < GAME_WIDTH &&
            deco->prevPos.y >= 0 && deco->prevPos.y < HEIGHT) {
            GotoXY(deco->prevPos.x, deco->prevPos.y);
            wcout << L"  ";
        }
    }

    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;
        if (enemy->prevPos.x >= 0 && enemy->prevPos.x < GAME_WIDTH &&
            enemy->prevPos.y >= 0 && enemy->prevPos.y < HEIGHT) {
            GotoXY(enemy->prevPos.x, enemy->prevPos.y);
            wcout << L"  ";
        }
    }
    for (const auto& deco : state.inGameData.decoObject) {
        if (!deco->isActive) continue;
        if (deco->pos.x >= 0 && deco->pos.x < GAME_WIDTH &&
            deco->pos.y >= 0 && deco->pos.y < HEIGHT) {
            GotoXY(deco->pos.x, deco->pos.y);
            SetColor(deco->colors);
            wcout << L"■";
        }
    }
    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;
        if (enemy->pos.x >= 0 && enemy->pos.x < GAME_WIDTH &&
            enemy->pos.y >= 0 && enemy->pos.y < HEIGHT) {
            GotoXY(enemy->pos.x, enemy->pos.y);
            if (dynamic_cast<EnemyShooter*>(enemy.get()))     SetColor(Color::SKYBLUE);
            else if (dynamic_cast<EnemyZigzag*>(enemy.get())) SetColor(Color::YELLOW);
            else                                              SetColor(Color::RED);
            wcout << L"▼";
        }
    }
    for (const Bullet& bullet : state.inGameData.bullets) {
        if (bullet.isActive) {
            GotoXY(bullet.pos.x, bullet.pos.y);
            SetColor(bullet.type == ProjectileType::Player ? Color::LIGHT_RED : Color::LIGHT_YELLOW);
            wcout << L"●";
            SetColor();
        }
    }

    if (player.IsDashing(state.curTime)) {
        SetColor(Color::WHITE);
    }
    else if (player.invisibleEndTime > state.curTime) {
        SetColor(Color::GRAY);
    }
    else {
        SetColor(Color::LIGHT_GREEN);
    }
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

void DashPlayer(GameState& state) {
    Player& player = state.inGameData.player;
    if (!player.CanDash(state.curTime)) return;

    player.dashStartTime = state.curTime;
    player.dashEndTime = state.curTime + 200;
    player.dashCooldownEndTime = state.curTime + player.stats.DashCooldown;
}

void PlayerMove(GameState& state) {
    Player& player = state.inGameData.player;

    int speedDivider = player.IsDashing(state.curTime) ? 3 : 1;
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

    if (GetKey(state.settingData.movementSettingData.attackKey)) {

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