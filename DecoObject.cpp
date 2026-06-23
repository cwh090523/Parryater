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

TrailDeco::TrailDeco(GameState& state, Color color, int lifeTime, Position position, const string& text)
    : DecoObject(state, color, lifeTime, position, text)
{
    startTime = state.curTime;
    disableTime = startTime + lifeTime;
}

void TrailDeco::DecoUpdate(GameState& state)
{
    if (state.curTime >= disableTime) {
        isActive = false;
        return;
    }

    float t = (float)(state.curTime - startTime) / (disableTime - startTime);

    if (t < 0.3f) colors = Color::WHITE;
    else if (t < 0.6f) colors = Color::LIGHT_GRAY;
    else colors = Color::GRAY;
}