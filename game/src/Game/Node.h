#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"
#include <vector>

class Piece;

class Node : public ScreenRelatedObject
{
public:
	Node() = delete;
	Node(float positionX, float positionY);
	~Node();

	void Update();
	void PairWith(Node* node);
	float GetSize();

private:
	const float NODE_SIZE = 10.f;

	std::vector<Node*> _pairedNodes;
	Piece* _hostedPiece = nullptr;

};