#include "Console.h"
#include "TitleScene.h"
#include "AsciiArt.h"
#include <chrono>
static AsciiObjs objs;
void InitTitle(GameState& state)
{
	system("cls");
	AsciiInit(objs);
	MatrixAnimation("Parryater ", 40, 50);
	system("cls");

}
void UpdateTitle(GameState& state)
{
	AsciiUpdate(objs);
	// 키 입력 화살표 왔다갔다
	if (GetKeyDown(VK_UP))
	{
		state.titleData.curMenu = (Menu)std::max((int)Menu::START, (int)state.titleData.curMenu - 1);
	}
	if (GetKeyDown(VK_DOWN))
	{
		state.titleData.curMenu = (Menu)std::min((int)Menu::QUIT, (int)state.titleData.curMenu + 1);
	}
	if (GetKeyDown(VK_SPACE) || GetKeyDown(VK_RETURN))
	{
		switch (state.titleData.curMenu)
		{
		case Menu::START:
			PlayTransition();
			state.curScene = Scene::INGAME;
			break;
		case Menu::SETTING:
			state.curScene = Scene::SETTING;
			break;
		case Menu::QUIT:
			state.isRunning = false;
			break;
		}
	}
}

void RenderTitle(const GameState& state)
{
	AsciiRender(objs);
	// 그려주기
	COORD res = GetConsoleResolution();
	int x = res.X / 2 - 4;
	int y = res.Y / 3 * 2;

	const string labels[] = { "게임 시작", "게임 설정", "게임 종료" };
	for (int i = 0;i < 3; ++i) {
		GotoXY(x - 2, y + i);
		cout << (i == (int)state.titleData.curMenu ? ">" : " ") << " " << labels[i];
	}
	const wstring ascii[] =
	{
		L"███████████                                                      █████						",
		L"▒▒███▒▒▒▒▒███                                                    ▒▒███						",
		L" ▒███    ▒███  ██████   ████████  ████████  █████ ████  ██████   ███████    ██████  ████████  ",
		L" ▒██████████  ▒▒▒▒▒███ ▒▒███▒▒███▒▒███▒▒███▒▒███ ▒███  ▒▒▒▒▒███ ▒▒▒███▒    ███▒▒███▒▒███▒▒███	",
		L" ▒███▒▒▒▒▒▒    ███████  ▒███ ▒▒▒  ▒███ ▒▒▒  ▒███ ▒███   ███████   ▒███    ▒███████  ▒███ ▒▒▒	",
		L" ▒███         ███▒▒███  ▒███      ▒███      ▒███ ▒███  ███▒▒███   ▒███ ███▒███▒▒▒   ▒███		",
		L" █████       ▒▒████████ █████     █████     ▒▒███████ ▒▒████████  ▒▒█████ ▒▒██████  █████		",
		L"▒▒▒▒▒         ▒▒▒▒▒▒▒▒ ▒▒▒▒▒     ▒▒▒▒▒       ▒▒▒▒▒███  ▒▒▒▒▒▒▒▒    ▒▒▒▒▒   ▒▒▒▒▒▒  ▒▒▒▒▒		",
		L"											 ███ ▒███											",
		L"											▒▒██████											",
		L"											 ▒▒▒▒▒▒												"
	};
	int titleX = (res.X - 70) / 2;
	int titleY = res.Y / 3;
	SetUnicodeMode();
	for (int i = 0; i < 7; ++i) {
		GotoXY(titleX - 20, titleY + i);
		wcout << ascii[i];
	}
	SetDeraultMode();
}

void PlayTransition()
{
	COORD res = GetConsoleResolution();
	int delayMs = 10;
	int flashCount = 5;
	FlashAnimation(res, flashCount, delayMs);
	CrossAnimation(res, delayMs);
}

void FlashAnimation(COORD resolution, int count, int delayMs)
{
	for (int i = 0; i < count; ++i) {
		SetColor(Color::BLACK, Color::GREEN);
		system("cls");
		Sleep(delayMs);

		SetColor(Color::BLACK, Color::BLACK);
		system("cls");
		Sleep(delayMs);
	}
}

void CrossAnimation(COORD resolution, int delayMs)
{
	SetColor(Color::BLACK, Color::WHITE);
	for (int x = 0; x < resolution.X / 2; ++x) {
		for (int y = 0; y < resolution.Y ; y += 2) {
			GotoXY(x * 2, y);
			cout << "  ";
		}
		for (int y = 1; y < resolution.Y; y += 2) {
			GotoXY(resolution.X - 2 - x * 2, y);
			cout << "  ";
		}
		Sleep(delayMs);
	}
	SetColor();
}


char RandomChar()
{
	std::string pool = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#$%";
	return pool[std::rand() % pool.size()];
}

void MatrixAnimation(const string& target, int frames, int ms)
{
	int n = target.size();

	int startX = (WIDTH - n) / 2;
	int startY = HEIGHT / 2;
	for (int i = 0; i < frames; ++i)
	{
		GotoXY(startX, startY);
		for (int j = 0; j < n; ++j)
		{
			if (j < i * n / frames)
			{
				SetColor(Color::LIGHT_GREEN);
				cout << target[j];
			}
			else
			{
				SetColor(Color::GREEN);
				cout << RandomChar();
			}
		}
		Sleep(ms);
	}
	GotoXY(startX, startY);
	SetColor(Color::LIGHT_GREEN);
	cout << target;
	SetColor();
	Sleep(500);
}
