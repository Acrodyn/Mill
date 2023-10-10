#pragma once

#include "Game/Board.h"
#include "raylib.h"

class ThreeBoard : public Board
{
public:
	ThreeBoard();
	~ThreeBoard();

private:
	void SetupBoard() override;
	bool CheckForWinConditions() override;
};