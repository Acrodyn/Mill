#pragma once

#include <functional>

#define GRAYISH       CLITERAL(Color){ 64, 77, 95, 255 }

typedef std::function<bool()> BoolFunction;
typedef std::function<void()> VoidFunction;

enum class AppState {
    Unset,
    Menu,
    Game
};

enum class GamePhaseState {
    Unset,
    Starting,
    Running,
    Ending,
    Ended,
    Paused,
    Reseting,
    Reset
};