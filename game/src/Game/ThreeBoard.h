#pragma once

#include "Board.h"
#include "raylib.h"

class ThreeBoard : public Board
{
public:
	ThreeBoard();
	~ThreeBoard();

	void Init() override;
	void Update() override;

private:
};