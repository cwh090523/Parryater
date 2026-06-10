#include "Console.h"
#include "MainGameData.h" 
#include "InGameScene.h"
#include "GameState.h"
#include <cmath>
#include <algorithm> 
using namespace std;

void InGameInit(GameState& state) {
    state.inGameData.isPaused = false;
    state.inGameData.isGameOver = false;
    state.inGameData.score = 0;

    state.inGameData.enemies.clear();
    state.inGameData.bullets.clear();

    state.inGameData.player.pos = { 55, 35 };
    state.inGameData.player.floatPos = { 55.0f, 35.0f };
    state.inGameData.player.prevPos = { 55, 35 };
    state.inGameData.player.stats.MoveSpeed = 50;
    state.inGameData.player.lastMoveTime = state.curTime;
    state.inGameData.player.lastAttackTime = state.curTime;
}

void InGameCollision(GameState& state) {
    Player& player = state.inGameData.player;

    for (Bullet& bullet : state.inGameData.bullets) {
        if (!bullet.isActive) continue;
        if (bullet.type != ProjectileType::Player) continue;

        for (auto& enemy : state.inGameData.enemies) {
            if (!enemy->isAlive) continue;
            if (abs(bullet.pos.x - enemy->pos.x) <= 1 && bullet.pos.y == enemy->pos.y) {
                bullet.isActive = false;
                enemy->isAlive = false;
                state.inGameData.score += 100;
                break;
            }
        }
    }

    for (const auto& enemy : state.inGameData.enemies) {
        if (!enemy->isAlive) continue;
        if (abs(enemy->pos.x - player.pos.x) <= 1 && enemy->pos.y == player.pos.y) {
            if (!player.IsDashing(state.curTime)) {
                player.stats.hp--;
                if (player.stats.hp <= 0) {
                    state.inGameData.isGameOver = true;
                }
            }
        }
    }
}

void InGameUpdate(GameState& state) {
    if (GetKeyDown(VK_ESCAPE)) {
        state.isRunning = false;
        return;
    }
    if (state.inGameData.isGameOver) {
        state.curScene = Scene::GAMEOVER;
        return;
    }

    Player& player = state.inGameData.player;
    MovementSettingData& msd = state.settingData.movementSettingData;

    player.lastMoveDir = player.moveDir;
    player.moveDir = { 0, 0 };

    if (GetKey(msd.moveUpKey) || GetKey(msd.moveUpArrowKey))    player.moveDir.y = -1;
    if (GetKey(msd.moveDownKey) || GetKey(msd.moveDownArrowKey))  player.moveDir.y = 1;
    if (GetKey(msd.moveLeftKey) || GetKey(msd.moveLeftArrowKey))  player.moveDir.x = -1;
    if (GetKey(msd.moveRightKey) || GetKey(msd.moveRightArrowKey)) player.moveDir.x = 1;
    if (GetKeyDown(msd.dashKey)) DashPlayer(state);

    PlayerMove(state);
    PlayerAttack(state);
    InGameCollision(state);

    auto iter = state.inGameData.bullets.begin();
    while (iter != state.inGameData.bullets.end()) {
        if (!iter->isActive) {
            iter = state.inGameData.bullets.erase(iter);
        }
        else {
            iter->ProjectileUpdate(state);
            ++iter;
        }
    }

    auto iter2 = state.inGameData.enemies.begin();
    while (iter2 != state.inGameData.enemies.end()) {
        if ((*iter2)->isAlive) {
            (*iter2)->EnemyUpdate(state);
            ++iter2;
        }
        else {
            GotoXY((*iter2)->pos.x, (*iter2)->pos.y);
            cout << " ";
            iter2 = state.inGameData.enemies.erase(iter2);
        }
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

    if (state.curTime < player.lastMoveTime + (ULONGLONG)player.stats.MoveSpeed) return;
    if (player.moveDir.x == 0 && player.moveDir.y == 0) return;

    int speed = player.IsDashing(state.curTime) ? 2 : 1;

    player.pos.x += player.moveDir.x * 2 * speed;
    player.pos.y += player.moveDir.y * speed;

    player.pos.x = std::max(0, std::min(player.pos.x, GAME_WIDTH - 1));
    player.pos.y = std::max(0, std::min(player.pos.y, HEIGHT - 1));

    player.lastMoveTime = state.curTime;
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
    cout << "1";

    GotoXY(UI_X, 10);
    SetColor(Color::LIGHT_YELLOW);
    cout << "HP";
    SetColor(Color::LIGHT_RED);
    GotoXY(UI_X, 11);
    string hp = "";
    for (int i = 0; i < player.stats.maxHp; ++i)
        hp += (i < player.stats.hp) ? "♥ " : "♡ ";
    cout << hp;

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

void InGameRender(const GameState& state) {
    const Player& player = state.inGameData.player;

    RenderBorder();
    RenderUI(state);

    SetUnicodeMode();
    for (const Bullet& bullet : state.inGameData.bullets) {
        GotoXY(bullet.prevPos.x, bullet.prevPos.y);
        wcout << L" ";
        if (bullet.isActive) {
            GotoXY(bullet.pos.x, bullet.pos.y);
            SetColor(Color::LIGHT_RED);
            wcout << L"●";
        }
    }

    GotoXY(player.prevPos.x, player.prevPos.y);
    wcout << L" ";

    SetColor(player.IsDashing(state.curTime) ? Color::WHITE : Color::LIGHT_GREEN);
    GotoXY(player.pos.x, player.pos.y);
    wcout << L"▲";
    SetDeraultMode();
    SetColor();
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

void InGameAfterUpdate(GameState& state) {
    state.inGameData.player.prevPos = state.inGameData.player.pos;
    for (Bullet& bullet : state.inGameData.bullets) {
        bullet.prevPos = bullet.pos;
    }
}