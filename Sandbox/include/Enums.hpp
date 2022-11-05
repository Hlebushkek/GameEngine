#pragma once

enum Direction { FORWARD = 1, BACKWARD = 2, LEFT = 4, RIGHT = 8, UP = 16, DOWN = 32 };
const int DIRECTION_ALL = FORWARD | BACKWARD | LEFT | RIGHT | UP | DOWN;

inline Direction operator|(Direction a, Direction b)
{
    return static_cast<Direction>(static_cast<int>(a) | static_cast<int>(b));
}

inline Direction operator&(Direction a, Direction b)
{
    return static_cast<Direction>(static_cast<int>(a) & static_cast<int>(b));
}