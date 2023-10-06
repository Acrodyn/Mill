#pragma once

#include "raylib.h"
#include <vector>

class Node;

class Board
{
public:
	Board();
	virtual ~Board();

	virtual void Init() = 0;
	virtual void Update();

protected:
	int _piecesPerPlayer = 0;
	int _nodesCount = 0;

	std::vector<Node*> _nodes;
};