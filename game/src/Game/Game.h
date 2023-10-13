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
	Game();
	~Game();

protected:
	void Init() override;
	void Clean() override;
	void Loop() override;

private:
	void InitBoard();
	void InitUI();
	void Reset();
	void ReturnToMenu();

private:
	Board* _board = nullptr;
	std::vector<ScreenRelatedObject*> _screenObjects;
};