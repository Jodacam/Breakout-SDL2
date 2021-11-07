#ifndef _GAMECONST_H_
#define _GAMECONST_H_

#define GAME_FIELD_W 240
#define GAME_FIELD_H 320
#define GAME_FIELD_CENTER_X 240
#define GAME_FIELD_POSITIVE_X_LIMIT GAME_FIELD_CENTER_X + (GAME_FIELD_W / 2)
#define GAME_FIELD_NEGATIVE_X_LIMIT GAME_FIELD_CENTER_X - (GAME_FIELD_W / 2)
#include <algorithm>
namespace GameEngine
{
    template <typename T>
    T clamp(const T &n, const T &lower, const T &upper)
    {
        return std::max(lower, std::min(n, upper));
    }
}
#endif