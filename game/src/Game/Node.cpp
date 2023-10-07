#include "Node.h"
#include "System/Core.h"

Node::Node(float positionX, float positionY) : ScreenRelatedObject{ positionX,  positionY }
{

}

Node::~Node()
{
	
}

void Node::Update()
{
	DrawCircle(GetPositionX(), GetPositionY(), NODE_SIZE, RAYWHITE);
}

void Node::PairWith(Node* node)
{
	_pairedNodes.push_back(node);
}

float Node::GetSize()
{
	return NODE_SIZE;
}

void Node::SetHostedPiece(Piece* piece)
{
	_hostedPiece = piece;
}

void Node::ResetHostedPiece()
{
	_hostedPiece = nullptr;
}

Piece* Node::GetOccupiedPiece()
{
	return _hostedPiece;
}
