#pragma once

#include "Game/Board.h"
#include "raylib.h"

class NineBoard : public Board
{
public:
	NineBoard();
	~NineBoard();

	void Init() override;
	void Update() override;

private:
	bool CheckForWinConditions() override;
};