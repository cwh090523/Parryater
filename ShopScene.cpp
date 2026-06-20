#include "Console.h"
#include "ShopScene.h"
#include "GameState.h"
#include <string>

using std::string;

enum class ShopItemType
{
    MAX_HP,
    ATTACK_POWER,
    ATTACK_SPEED,
    MOVE_SPEED,
    DASH_COOLDOWN
};

struct ShopItem
{
    string name;
    string desc;
    int price;
    ShopItemType type;
    int value;
};

const ShopItem shopItems[] =
{
    { "HP UP              ",           "Max HP +5           ", 300, ShopItemType::MAX_HP,        5 },
    { "ATTACK UP          ",       "Attack Power +1     ",        500, ShopItemType::ATTACK_POWER,  1 },
    { "ATTACK SPEED UP     ", "Attack Cooldown -50 ",    400, ShopItemType::ATTACK_SPEED, 50 },
    { "MOVE SPEED UP      ",   "Move Speed +10      ",         350, ShopItemType::MOVE_SPEED,   10 },
    { "DASH COOL DOWN      ",  "Dash Cooldown -100  " ,     450, ShopItemType::DASH_COOLDOWN,100 }
};

const int SHOP_ITEM_COUNT = sizeof(shopItems) / sizeof(shopItems[0]);

void BuyShopItem(GameState& state, const ShopItem& item)
{
    Player& player = state.inGameData.player;

    if (state.inGameData.score < item.price)
    {
        state.shopData.message = "돈이 충분하지 않다!";
        return;
    }

    state.inGameData.score -= item.price;

    switch (item.type)
    {
    case ShopItemType::MAX_HP:
        player.stats.maxHp += item.value;
        player.stats.hp += item.value;
        break;

    case ShopItemType::ATTACK_POWER:
        player.stats.attackPower += item.value;
        break;

    case ShopItemType::ATTACK_SPEED:
        player.stats.attackSpeed -= item.value;

        if (player.stats.attackSpeed < 100)
            player.stats.attackSpeed = 100;
        break;

    case ShopItemType::MOVE_SPEED:
        player.stats.MoveSpeed += item.value;
        break;

    case ShopItemType::DASH_COOLDOWN:
        player.stats.DashCooldown -= item.value;

        if (player.stats.DashCooldown < 300)
            player.stats.DashCooldown = 300;
        break;
    }

    state.shopData.message = "구매함: " + item.name;
}

void ShopInit(GameState& state)
{
    system("cls");

    state.shopData.selectedIndex = 0;
    //state.shopData.message = "LEFT / RIGHT : Select, ENTER / SPACE : Buy, ESC : Back";
}

void ShopUpdate(GameState& state)
{
    ShopData& shop = state.shopData;

    if (GetKeyDown(VK_ESCAPE))
    {
        state.curScene = Scene::INGAME;
        return;
    }

    if (GetKeyDown(VK_LEFT))
    {
        shop.selectedIndex--;

        if (shop.selectedIndex < 0)
            shop.selectedIndex = SHOP_ITEM_COUNT - 1;
    }

    if (GetKeyDown(VK_RIGHT))
    {
        shop.selectedIndex++;

        if (shop.selectedIndex >= SHOP_ITEM_COUNT)
            shop.selectedIndex = 0;
    }

    if (GetKeyDown(VK_SPACE) || GetKeyDown(VK_RETURN))
    {
        BuyShopItem(state, shopItems[shop.selectedIndex]);
    }
}

void DrawShopCard(int x, int y, const ShopItem& item, bool selected)
{
    if (selected)
        SetColor(Color::BLACK, Color::LIGHT_YELLOW);
    else
        SetColor(Color::WHITE, Color::BLACK);

    GotoXY(x, y);
    cout << "======================";

    GotoXY(x, y + 1);
    cout << "|                    |";

    GotoXY(x, y + 2);
    cout << "| " << item.name;

    GotoXY(x + 21, y + 2);
    cout << "|";

    GotoXY(x, y + 3);
    cout << "| " << item.desc;

    GotoXY(x + 21, y + 3);
    cout << "|";

    GotoXY(x, y + 4);
    cout << "| 가격: " << item.price << "          ";

    GotoXY(x + 21, y + 4);
    cout << "|";

    GotoXY(x, y + 5);
    cout << "|                    |";

    GotoXY(x, y + 6);
    cout << "======================";

    SetColor();
}

void ShopRender(const GameState& state)
{
    const ShopData& shop = state.shopData;
    const Player& player = state.inGameData.player;

    GotoXY(0, 0);

    SetColor(Color::LIGHT_YELLOW);
    cout << "============================== SHOP ==============================";
    SetColor();

    GotoXY(3, 2);
    cout << "Score : " << state.inGameData.score;

    GotoXY(3, 3);
    cout << "HP : " << player.stats.hp << " / " << player.stats.maxHp;

    GotoXY(20, 3);
    cout << "Attack : " << player.stats.attackPower;

    GotoXY(38, 3);
    cout << "Attack Speed : " << player.stats.attackSpeed;

    GotoXY(62, 3);
    cout << "Move Speed : " << player.stats.MoveSpeed;

    int startX = 5;
    int y = 7;
    int gap = 24;

    for (int i = 0; i < SHOP_ITEM_COUNT; ++i)
    {
        DrawShopCard(startX + i * gap, y, shopItems[i], i == shop.selectedIndex);
    }

    GotoXY(5, 17);
    SetColor(Color::LIGHT_GREEN);
    cout << shop.message;
    SetColor();

    GotoXY(5, 19);
    cout << "LEFT / RIGHT : 선택";

    GotoXY(5, 20);
    cout << "ENTER / SPACE : 구매";

    GotoXY(5, 21);
    cout << "ESC : 게임으로";
}