#pragma once

#include "raylib.h"
#include <vector>

class Node
{
public:
	Node() = delete;
	Node(float positionX, float positionY);
	~Node();

	void Update();
	void PairWith(Node* node);
	int GetPositionX();
	int GetPositionY();

private:
	Vector2 _position;
	std::vector<Node*> _pairedNodes;
};