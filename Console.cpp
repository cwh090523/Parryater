#include "Console.h"

//#undef max;

void SetUnicodeMode() {
	(void)_setmode(_fileno(stdout), _O_U16TEXT);
}
void SetDeraultMode() {
	(void)_setmode(_fileno(stdout), _O_TEXT);
}
void RenderChar(char ch, int delayTime, bool isSkip)
{
	cout << ch;
	// @#$%^&*
	// string의 find랑 비슷한데 더 빠름
	// 오타연출
	if (strchr("@$%^&*", ch))
	{

	}
	if (isSkip)
		return;
	int calcDelay = delayTime + (rand() & 11 - 5);
	switch (ch)
	{
		// 오타연출
		// '\b' : 벡스페이스
	case '#':
		// #을 만난순간 잠깐 멈칫하고
		// 지워주고
		// 다시 그려주기
		Sleep(200);
		cout << "\b \b";
		//cout << "\b";

		break;
	case '?':
	case '!':
	case '.':
		calcDelay += 400;
		break;
	case ',':
		calcDelay += 200;
		break;
	case '\n':
		calcDelay += 500;
		break;
	case ' ':
		calcDelay += 50;
		break;
	default:
		break;

	}
	Sleep(std::max(0, calcDelay));
}

void RanderDialogue(const string& text, int delayTime)
{
	bool isSkip = false;
	for (int i = 0; i < text.size(); ++i) {
		//스킵 기능
		if (!isSkip && _kbhit())
		{
			_getch(); //버퍼 비우기용.
			isSkip = true;
		}
		RenderChar(text[i], delayTime, isSkip);
	}
}
void SetConsoleGameTitle(const wstring& title)
{
	SetConsoleTitle(title.c_str());
}

void SetConsoleSize(int width, int height)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	// 뷰포트 설정
	SMALL_RECT rect = { 0,0,1,1 };
	SetConsoleWindowInfo(handle, true, &rect);

	// 버퍼
	COORD size = { (short)width, (short)height };
	SetConsoleScreenBufferSize(handle, size);

	rect.Right = width - 1;
	rect.Bottom = height - 1;
	SetConsoleWindowInfo(handle, true, &rect);

	// 가운데 설정
	//Sleep(100);
	HWND hWnd = GetConsoleWindow();

	//RECT windowRect;
	//GetWindowRect(hWnd, &windowRect);
	//int windowWidth = windowRect.right - windowRect.left;
	//int windowHeight= windowRect.bottom- windowRect.top;

	CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontinfo);

	int windowWidth = fontinfo.dwFontSize.X * width;
	int windowHeight = fontinfo.dwFontSize.Y * height;
	int screenWigth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int posX = (screenWigth - windowWidth) / 2;
	int posY = (screenHeight - windowHeight) / 2;

	SetWindowPos(hWnd, nullptr, posX, posY, 0, 0, SWP_NOSIZE);

}

void SetConsoleFullScreen()
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontinfo);

	SetConsoleDisplayMode(handle,
		CONSOLE_FULLSCREEN_MODE, 0);

	int wigth = GetSystemMetrics(SM_CXSCREEN) / fontinfo.dwFontSize.X;
	int height = GetSystemMetrics(SM_CYSCREEN) / fontinfo.dwFontSize.Y;
	SetConsoleSize(wigth, height);
}

void SetConsoleWindowStyle(bool showTitlebar)
{
	HWND hWnd = GetConsoleWindow();
	LONG style = GetWindowLong(hWnd, GWL_STYLE);
	style &= ~WS_SIZEBOX & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX & ~WS_SYSMENU;
	if (!showTitlebar)
		style &= ~WS_CAPTION;
	SetWindowLong(hWnd, GWL_STYLE, style);
	SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0
		, SWP_NOSIZE | SWP_NOMOVE | SWP_FRAMECHANGED);

}

void ShakeConsoleWindow(int intensity, int duration, int interval)
{
	//intensity = 강도
	// duration = 시간
	// interval = 텀
	HWND hWnd = GetConsoleWindow();
	RECT windowRect;
	GetWindowRect(hWnd, &windowRect);
	int otiginX = windowRect.left;
	int otiginY = windowRect.top;


	//흔들고 
	int count = duration / interval;
	for (int i = 0; i < count; ++i) {
		int offsetX = rand() % (intensity * 2 + 1) - intensity;
		int offsetY = rand() % (intensity * 2 + 1) - intensity;

		SetWindowPos(hWnd, nullptr,
			offsetX + offsetY,
			offsetY + offsetX,
			0, 0, SWP_NOSIZE);
		Sleep(interval);
	}


	// 원상 복귀

	SetWindowPos(hWnd, nullptr, otiginX, otiginY, 0, 0
		, SWP_NOSIZE);
}

void GotoXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD curPos = { (short)x, (short)y };
	SetConsoleCursorPosition(handle, curPos);
}

BOOL IsGotoXY(int x, int y)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD curPos = { (short)x, (short)y };
	return SetConsoleCursorPosition(handle, curPos);
}

void SetcursorVisble(bool visible, DWORD size)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO curInfo;
	curInfo.bVisible = visible; // on off 기능
	curInfo.dwSize = size; // 1~ 100

	SetConsoleCursorInfo(handle, &curInfo);
}

COORD GetConsoleResolution()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	short width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	short height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	return { width, height };
}

void SetColor(Color textColor, Color bgColor)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int text = (int)textColor;
	int bg = (int)bgColor;
	SetConsoleTextAttribute(handle, (bg << 4) | text);
}

void DrawBar(int x, int y, const string& label, int value, int maxValue, int barWidth, const string& fillChar, const string& emptyChar)
{
	Color color;
	if (value > maxValue * 0.6f)
		color = Color::LIGHT_GREEN;
	else if (value > maxValue * 0.3f)
		color = Color::LIGHT_YELLOW;
	else
		color = Color::LIGHT_RED;
	// 그릴 지점으로 가서
	GotoXY(x, y);
	// 색을 원래 대로 돌리고
	SetColor();
	cout << label;

	SetColor(color);

	// bar 출력
	// batWidth; // 10칸

	// 10칸 value 60 / maxValue 100
	int fillCount = barWidth * value / maxValue;
	for (int i = 0; i < barWidth; ++i)
		cout << (i < fillCount ? fillChar : emptyChar);

	SetColor();
	// 10 / 100
	int digits = std::to_string(maxValue).length();
	cout << " " << std::setw(digits) << value << "/"
		<< std::setw(digits) << maxValue;
}

void DrawLine(char ch, int width)
{
	//setw(): 한번에 끝
	// setfill() : 한번하면 계속
	cout << std::setfill(ch) << std::setw(width) << ""
		<<std::setfill(' ');
	// "" : 허위 출력
}

bool GetKey(int vKey)
{
	return GetAsyncKeyState(vKey) & 0x8000;
}
constexpr int KEY_COUNT = 256;
static bool prevDown[KEY_COUNT] = {};
static bool curDown[KEY_COUNT] = {};
bool GetKeyDown(int vKey)
{

	return curDown[vKey] && !prevDown[vKey];;
}

void UpdateInput()
{
	for (int i = 0; i < 256; ++i) {
		prevDown[i] = curDown[i];
		curDown[i] = GetAsyncKeyState(i) & 0x8000;
	}

	/*bool cur = GetAsyncKeyState(vKey) & 0x8000;
	bool down = cur && !prevDown[vKey];
	prevDown[vKey] = cur;*/

}

void SetConsoleMouseInputDisabled()
{
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(handle, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	mode &= ~ENABLE_INSERT_MODE;

	mode |= ENABLE_MOUSE_INPUT;
	mode |= ENABLE_EXTENDED_FLAGS;
	SetConsoleMode(handle, mode);
}

POINT GetMouseCellPos()
{
	POINT pt;
	GetCursorPos(&pt);
	HWND hWnd = GetConsoleWindow();
	ScreenToClient(hWnd, &pt);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontinfo = { sizeof(CONSOLE_FONT_INFOEX) };
	GetCurrentConsoleFontEx(handle, false, &fontinfo);

	POINT celllPos = { pt.x / fontinfo.dwFontSize.X,
	pt.y / fontinfo.dwFontSize.Y };

	return celllPos;
}

void FrameSync(int fps)
{
	static ULONGLONG prevTick = GetTickCount64();

	ULONGLONG  curTick = GetTickCount64();
	ULONGLONG targetTick = 1000 / fps;
	ULONGLONG elapsed = curTick - prevTick;
	if (elapsed < targetTick)
		Sleep(targetTick - elapsed);
	prevTick = GetTickCount64();
}

int GetCursorX()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	return csbi.dwCursorPosition.X;
}

void SetConsoleFont(const wstring& fontName, COORD size, UINT weight)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX info = {};
	info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	info.dwFontSize = size; // 폭, 높이
	info.FontWeight = weight; // FW_ ~ 
	// 폰트 이름 복사
	wcscpy_s(info.FaceName, fontName.c_str());
	SetCurrentConsoleFontEx(handle, false, &info);

}
