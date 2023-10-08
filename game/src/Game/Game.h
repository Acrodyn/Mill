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
	void InitPhase() override;
	void DestroyPhase() override;
	void LoopPhase() override;

private:
	void CheckForInput();

private:
	Board* _board = nullptr;
	std::vector<ScreenRelatedObject*> _screenObjects;
};