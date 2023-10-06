#pragma once

enum class AppPhase {
    Unset,
    Menu,
    Game
};

enum class GamePhaseState {
    Unset,
    Starting,
    Ending,
    Ended,
    Running,
    Paused
};