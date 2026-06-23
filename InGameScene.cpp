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
    if (!state.inGameData.isGamming) {

    StageInit(state);
    SOUND->PlayBGM("Stage0+");
    state.inGameData.isPaused = false;
    state.inGameData.isGameOver = false;
    state.inGameData.score = 0;

    state.inGameData.enemies.clear();
    state.inGameData.bullets.clear();
    state.inGameData.player.stats.maxHp = 5;
    state.inGameData.player.stats.hp = 5;
    state.inGameData.player.stats.attackPower = 5;
    state.inGameData.player.stats.attackSpeed = 500;
    state.inGameData.player.pos = { 55, 35 };
    state.inGameData.player.floatPos = { 55.0f, 35.0f };
    state.inGameData.player.prevPos = { 55, 35 };
    state.inGameData.player.stats.MoveSpeed = 40;
    state.inGameData.player.stats.DashCooldown = 2000;
    state.inGameData.player.lastMoveTime = state.curTime;
    state.inGameData.player.lastAttackTime = state.curTime;
    state.inGameData.player.invisibleEndTime = 0;
    state.inGameData.isGamming = true;

    }

}

void InGameCollision(GameState& state) {
    Player& player = state.inGameData.player;
    bool playerInvincible = player.IsDashing(state.curTime) || state.curTime < player.invisibleEndTime;

    for (Bullet& bullet : state.inGameData.bullets) {
        if (!bullet.isActive) continue;

        if (bullet.type == ProjectileType::Player) {
            for (auto& enemy : state.inGameData.enemies) {
                if (!enemy->isAlive) continue;

                int minEnemyX = min(enemy->prevPos.x, enemy->pos.x) - 2;
                int maxEnemyX = max(enemy->prevPos.x, enemy->pos.x) + 2;
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
                        state.inGameData.score += 50;
                        
                    }
                    break;
                }
            }
        }
        else {
            int range = player.IsDashing(state.curTime) ? 1 : 0;

            int minPlayerX = min(player.prevPos.x, player.pos.x) - range * 4;
            int maxPlayerX = max(player.prevPos.x, player.pos.x) + range * 4;
            int minPlayerY = min(player.prevPos.y, player.pos.y) - range * 2;
            int maxPlayerY = max(player.prevPos.y, player.pos.y) + range * 2;

            int minBulletX = min(bullet.prevPos.x, bullet.pos.x);
            int maxBulletX = max(bullet.prevPos.x, bullet.pos.x);
            int minBulletY = min(bullet.prevPos.y, bullet.pos.y);
            int maxBulletY = max(bullet.prevPos.y, bullet.pos.y);

            if (maxBulletX >= minPlayerX && minBulletX <= maxPlayerX && maxBulletY >= minPlayerY && minBulletY <= maxPlayerY) {
                if (player.IsDashing(state.curTime)) {
                    ShakeConsoleWindow(10, 20, 10);
                    bullet.moveDir.x *=-1;
                    bullet.moveDir.y *=-1;
                    bullet.type = ProjectileType::Player;
                    bullet.damage += player.stats.attackPower * 10;
                    bullet.MoveSpeed /= 2;
                    player.invisibleEndTime = state.curTime + 800;
                    player.dashCooldownEndTime = state.curTime;
                    state.inGameData.score += 20;
                    auto wave = new WaveDeco(state, Color::WHITE, 50, player.pos, 2, 0);
                    state.inGameData.decoObject.push_back(std::unique_ptr<DecoObject>(wave));
                    SOUND->PlaySFX("ParrySFX");
                }
                else if (!playerInvincible) {
                bullet.isActive = false;
                    player.stats.hp -= bullet.damage;
                    player.invisibleEndTime = state.curTime + 500;
                    ShakeConsoleWindow(5, 10, 10);
                    SOUND->PlaySFX("HitSFX");
                    if (player.stats.hp <= 0) {
                        state.curScene = Scene::TITLE;
                        state.inGameData.isGameOver = true;
                        state.inGameData.isGamming = false;
                    }
                }
            }
        }
    }

    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;

        int range = player.IsDashing(state.curTime) ? 1 : 0;

        int minPlayerX = min(player.prevPos.x, player.pos.x) - range * 4;
        int maxPlayerX = max(player.prevPos.x, player.pos.x) + range * 4;
        int minPlayerY = min(player.prevPos.y, player.pos.y) - range * 2;
        int maxPlayerY = max(player.prevPos.y, player.pos.y) + range * 2;

        int minEnemyX = min(enemy->prevPos.x, enemy->pos.x);
        int maxEnemyX = max(enemy->prevPos.x, enemy->pos.x);
        int minEnemyY = min(enemy->prevPos.y, enemy->pos.y);
        int maxEnemyY = max(enemy->prevPos.y, enemy->pos.y);

        if (maxEnemyX >= minPlayerX && minEnemyX <= maxPlayerX &&
            maxEnemyY >= minPlayerY && minEnemyY <= maxPlayerY) {
            if (player.IsDashing(state.curTime)) {

                Enemy* e = const_cast<Enemy*>(enemy.get());

                if (state.curTime - e->lastHitTime < 300)
                    continue;

                e->lastHitTime = state.curTime;

                ShakeConsoleWindow(10, 20, 10);

                player.invisibleEndTime = state.curTime + 1000;
                player.dashCooldownEndTime = state.curTime;

                auto wave = new WaveDeco(state, Color::WHITE, 50, player.pos, 2, 0);
                state.inGameData.decoObject.push_back(std::unique_ptr<DecoObject>(wave));

                state.inGameData.score += 25;
                SOUND->PlaySFX("ParrySFX");

                e->stats.hp -= (player.stats.attackPower * 2);

                if (e->stats.hp <= 0) {
                    e->isAlive = false;
                    state.inGameData.score += 50;
                }
            }
            else if (!playerInvincible) {
                player.stats.hp--;
                player.invisibleEndTime = state.curTime + 500;
                //SetColor(Color::WHITE, Color::LIGHT_RED);
                //system("cls");
                ShakeConsoleWindow(5, 10, 10);

                //SetColor();
                //system("cls");
                SOUND->PlaySFX("HitSFX");
                if (player.stats.hp <= 0) {
                    state.curScene = Scene::TITLE;
                    state.inGameData.isGameOver = true;
                    state.inGameData.isGamming = false;
                }
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
    if (player.CanDash(state.curTime)) {
        if (!player.dashReadyTriggered) {
            player.dashReadyTriggered = true;

            auto wave = new WaveDeco(
                state,
                Color::LIGHT_YELLOW,
                40,
                player.pos,
                2,
                0
            );

            state.inGameData.decoObject.push_back(std::unique_ptr<DecoObject>(wave));
        }
    }
    else {
        player.dashReadyTriggered = false;
    }
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
    if (player.IsDashing(state.curTime)) {
        auto trail = new TrailDeco(
            state,
            Color::GRAY,
            120,
            player.prevPos,
            "."
        );

        state.inGameData.decoObject.push_back(std::unique_ptr<DecoObject>(trail));
    }
}void InGameRender(const GameState& state) {
    const Player& player = state.inGameData.player;
    RenderBorder();
    RenderUI(state);
    SetUnicodeMode();

    for (const auto& enemy : state.inGameData.enemies) {
        if (enemy->prevPos == enemy->pos) continue;
        GotoXY(enemy->prevPos.x, enemy->prevPos.y);
        wcout << L"  ";
    }
    for (const Bullet& bullet : state.inGameData.bullets) {
        if (bullet.prevPos == bullet.pos) continue;
        GotoXY(bullet.prevPos.x, bullet.prevPos.y);
        wcout << L"  ";
    }
    if (!(player.prevPos == player.pos)) {
        GotoXY(player.prevPos.x, player.prevPos.y);
        wcout << L" ";
    }
    for (const auto& deco : state.inGameData.decoObject) {
        if (!deco->isActive) continue;
        if (deco->prevPos == deco->pos) continue;
        if (deco->prevPos.x >= 0 && deco->prevPos.x < GAME_WIDTH &&
            deco->prevPos.y >= 0 && deco->prevPos.y < HEIGHT) {
            GotoXY(deco->prevPos.x, deco->prevPos.y);
            wcout << L"  ";
        }
    }
    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;
        if (enemy->prevPos == enemy->pos) continue;
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

            if (dynamic_cast<EnemyShooter*>(enemy.get())) {
                SetColor(Color::SKYBLUE);
                wcout << L"▼";
            }
            else if (dynamic_cast<EnemyZigzag*>(enemy.get())) {
                SetColor(Color::YELLOW);
                wcout << L"▼";
            }
            else if (dynamic_cast<EnemyWaver*>(enemy.get())) {
                SetColor(Color::CYAN);
                wcout << L"◆";
            }
            else if (dynamic_cast<EnemySideShooter*>(enemy.get())) {
                SetColor(Color::LIGHT_GREEN);
                wcout << L"◆";
            }
            else if (dynamic_cast<EnemyCrossShooter*>(enemy.get())) {
                SetColor(Color::LIGHT_VIOLET);
                wcout << L"✚";
            }
            else if (dynamic_cast<EnemyRadialShooter*>(enemy.get())) {
                SetColor(Color::LIGHT_RED);
                wcout << L"◆";
            }
            else if (dynamic_cast<EnemyTrackerX*>(enemy.get())) {
                SetColor(Color::LIGHT_BLUE);
                wcout << L"■";
            }
            else if (dynamic_cast<EnemyChaser*>(enemy.get())) {
                SetColor(Color::LIGHT_YELLOW);
                wcout << L"★";
            }
            else {
                SetColor(Color::RED);
                wcout << L"▼";
            }
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
    else if (!player.CanDash(state.curTime)) {
        SetColor(Color::LIGHT_GRAY);
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
    player.dashEndTime = state.curTime + 230;
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
    GotoXY(UI_X, 21);
    cout << "SHOP: B KEY";
    GotoXY(UI_X, 22);
    cout << "SETTING: TAB KEY";

    SetColor();
}