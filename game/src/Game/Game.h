#pragma once

#include "raylib.h"
#include "System/GamePhase.h"
#include <vector>

class Board;
class Button;
class ScreenRelatedObject;

class Game : public GamePhase
{
public:
	Game(TransitionData** transitionData = nullptr);
	~Game();

protected:
	void Init() override;
	void InitUI() override;
	void Destroy() override;
	void Loop() override;
	void Reset() override;

private:
	void InitBoard();
	void ResetGame();
	void ReturnToMenu();

private:
	Board* _board = nullptr;
};