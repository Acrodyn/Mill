#pragma once

#include <functional>
#include <string>

#define GRAYISH       CLITERAL(Color){ 64, 77, 95, 255 }

typedef std::function<void()> VoidFunction;
typedef std::function<bool()> BoolFunction;
typedef std::function<std::string()> StringFunction;

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