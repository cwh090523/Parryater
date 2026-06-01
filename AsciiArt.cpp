#include "AsciiArt.h"
#include "Console.h"
#include "GameState.h"
void AsciiInit(AsciiObjs& objs)
{
	objs.plane =
	{
	   "        _        ",
	   "      -= \`\     ",
	   "  | \ ____\_\__  ",
	   "-= \c`""""""" "`)",
	   "   `~~~~~/ /~~`  ",
	   "     -= = / /    ",
	   "       '-'       ",
	};

	objs.cloud =
	{
	 "      _  _       ",
	 "    ( `   )_     ",
	 "   (    )    `)  ",
	 " (_   (_ .  _) _)",
	};
	for (string& line : objs.plane)
		line.resize(WIDTH, ' ');
	for (string& line : objs.cloud)
		line.resize(WIDTH, ' ');
}

void AsciiUpdate(AsciiObjs& objs)
{
	for (string& line : objs.cloud)
		std::rotate(line.begin(), line.begin() + 1, line.end());
	for (string& line : objs.plane)
		std::rotate(line.rbegin(), line.rbegin() + 1, line.rend());

}

void AsciiRender(const AsciiObjs& objs)
{
	int planeLines = (int)objs.plane.size();
	int cloudLines = (int)objs.cloud.size();
	COORD res = GetConsoleResolution();

	SetColor(Color::LIGHT_YELLOW);
	for (int i = 0; i < planeLines; ++i)
	{
		GotoXY(0, i);
		cout << objs.plane[i];
	}

	SetColor(Color::CYAN);
	for (int i = 0; i < cloudLines; ++i)
	{
		GotoXY(0, planeLines + i);
		cout << objs.cloud[i];
	}
	SetColor();
}
