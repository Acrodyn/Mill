#pragma once

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