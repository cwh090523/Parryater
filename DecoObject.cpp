#include "MainGameData.h"
#include "GameState.h"
#include <algorithm>
using namespace std;


WaveDeco::WaveDeco(GameState& state, Color color, int lifeTime, Position position, int size, int count, const string& text, Position dir)
	: DecoObject(state, color, lifeTime, position, text)
{	
	counts = count;
	sizes = size;
    startTime = state.curTime;
    dirs = dir;
    disableTime = startTime + lifeTime;
}


void WaveDeco::DecoUpdate(GameState& state) {
    if (state.curTime >= disableTime) {
        if (counts < sizes) {


            if (dirs.x == 0 && dirs.y == 0) {
                Position directions[8] = {
                    {0, -1}, {2, -1}, {2, 0}, {2, 1},
                    {0, 1}, {-2, 1}, {-2, 0}, {-2, -1}
                };

                for (int i = 0; i < 8; ++i) {
                    Position nextPos = { pos.x + directions[i].x, pos.y + directions[i].y };
                    auto wave = new WaveDeco(state, colors, lifeTimes, nextPos, sizes, counts + 1, showText, directions[i]);
                    state.inGameData.decoSpawnQueue.push_back(std::unique_ptr<DecoObject>(wave));
                }
            }
            else {
                Position nextPos = { pos.x + dirs.x, pos.y + dirs.y };
                auto wave = new WaveDeco(state, colors, lifeTimes, nextPos, sizes, counts + 1, showText, dirs);
                state.inGameData.decoSpawnQueue.push_back(std::unique_ptr<DecoObject>(wave));
            }
        }
        isActive = false;
    }
}