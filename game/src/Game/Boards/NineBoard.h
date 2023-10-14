#pragma once

#include "Game/Board.h"
#include "raylib.h"

class NineBoard : public Board
{
public:
	NineBoard();
	~NineBoard();

private:
	void SetupBoard() override;
	bool CheckForWinConditions(WinCondition winCondition) override;
};