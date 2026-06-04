#include "Title.h"
#include "Console.h"
#include "AsciiArt.h"
static AsciiObjs objs;
void IitTitle(GameState& state)
{
	AsciiInit(objs);
}
void UpdateTitle(GameState& state)
{
	AsciiUpdate(objs);
	// 키 입력 화살표 왔다갔다
	if (GetKeyDown(VK_UP))
	{
		state.curMenu = (Menu)std::max((int)Menu::START, (int)state.curMenu - 1);
	}
	if (GetKeyDown(VK_DOWN))
	{
		state.curMenu = (Menu)std::min((int)Menu::QUIT, (int)state.curMenu + 1);
	}
	if (GetKeyDown(VK_SPACE) || GetKeyDown(VK_RETURN))
	{
		switch (state.curMenu)
		{
		case Menu::START:
			PlayTransition();
			state.curScene = Scene::INGAME;
			break;
		case Menu::SETTING:
			state.curScene = Scene::INFO;
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

	const string labels[] = { "게임 시작", "게임 정보", "게임 종료" };
	for (int i = 0;i < 3; ++i) {
		GotoXY(x - 2, y + i);
		cout << (i == (int)state.curMenu ? ">" : " ") << " " << labels[i];
	}

	const wstring ascii[] =
	{
	
		L".______      ___      .______      .______     ____    ____  ___   .___________. _______ .______      ",
		L"|   _  \    /   \     |   _  \     |   _  \    \   \  /   / /   \  |           ||   ____||   _  \     ",
		L"|  |_)  |  /  ^  \    |  |_)  |    |  |_)  |    \   \/   / /  ^  \ `---|  |----`|  |__   |  |_)  |    ",
		L"|   ___/  /  /_\  \   |      /     |      /      \_    _/ /  /_\  \    |  |     |   __|  |      /     ",
		L"|  |     /  _____  \  |  |\  \----.|  |\  \----.   |  |  /  _____  \   |  |     |  |____ |  |\  \----.",
		L"| _|    /__/     \__\ | _| `._____|| _| `._____|   |__| /__/     \__\  |__|     |_______|| _| `._____|"                                                                                                

	};
	int titleX = (res.X - 70) / 2;
	int titleY = res.Y / 3;
	SetUnicodeMode();
	for (int i = 0; i < 7; ++i) {
		GotoXY(titleX - 20, titleY + i);
		wcout << ascii[i];
	}
	SetDeraultMode();
	//GotoXY(x, y);
	//cout << "게임 시작";
	//GotoXY(x, y+1);
	//cout << "게임 정보";
	//GotoXY(x, y+2);
	//cout << "게임 종료";

	//GotoXY(x-2,y);
	//cout << (state.curMenu == Menu::START? ">" : " ");
	//GotoXY(x - 2, y+1);
	//cout << (state.curMenu == Menu::INFO ? ">" : " ");
	//GotoXY(x - 2, y+2);
	//cout << (state.curMenu == Menu::QUIT? ">" : " ");
}

void UpdateInfo(GameState& state)
{
	if (GetKeyDown(VK_ESCAPE)) {
		state.curScene = Scene::TITLE;
	}
}

void RenderInfo(const GameState& state)
{
	// 화면 중앙에 출력
	COORD res = GetConsoleResolution();
	int cx = res.X / 2;
	int cy = res.Y / 3;

	const string infoLabels[] =
	{
		"[ 조작 방법 ]",
		"방향키  : 이동",
		"SPACE  : 폭탄 설치",
		"Z      : 스킬",
		"ESC 로 돌아가기"
	};
	for (int i = 0; i < 5; ++i)
	{
		GotoXY(cx - 6, cy + i);
		if (i == 0)
			SetColor(Color::LIGHT_YELLOW);
		else if (i == 4)
			SetColor(Color::LIGHT_GRAY);
		else
			SetColor();
		cout << infoLabels[i];
	}
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
		SetColor(Color::BLACK, Color::RED);
		system("cls");
		Sleep(delayMs);

		SetColor(Color::BLACK, Color::BLUE);
		system("cls");
		Sleep(delayMs);
	}
}

void CrossAnimation(COORD resolution, int delayMs)
{
	SetColor(Color::BLACK, Color::WHITE);
	for (int x = 0; x < resolution.X / 2; ++x) {
		for (int y = 0; y < resolution.Y; y += 2) {
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
