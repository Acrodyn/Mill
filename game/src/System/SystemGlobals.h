#pragma once

#define GRAYISH       CLITERAL(Color){ 64, 77, 95, 255 }

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