#pragma once
#include <vector>
#include <string>
#include <algorithm>
using std::vector;
using std::string;

struct AsciiObjs {
	vector<string> plane;
	vector<string> cloud;
};

void AsciiInit(AsciiObjs& objs);
void AsciiUpdate(AsciiObjs& objs);
void AsciiRender(const AsciiObjs& objs);
