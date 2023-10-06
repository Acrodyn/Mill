#include "Node.h"
#include "System/Core.h"

Node::Node(float positionX, float positionY)
{
	_position = { positionX, positionY };
}

Node::~Node()
{
	
}

void Node::Update()
{
	DrawCircle(GetPositionX(), GetPositionY(), 10.f, RAYWHITE);
}

void Node::PairWith(Node* node)
{
	_pairedNodes.push_back(node);
}

int Node::GetPositionX()
{
	return Core::GetPixelPositionWidth(_position.x);
}

int Node::GetPositionY()
{
	return Core::GetPixelPositionHeight(_position.y);
}
