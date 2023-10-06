#include "ThreeBoard.h"
#include "System/Core.h"

ThreeBoard::ThreeBoard()
{
	_piecesPerPlayer = 3;
	_nodesCount = 9;
}

ThreeBoard::~ThreeBoard()
{
	
}

void ThreeBoard::Init()
{
	Node* topLeft = CreateNode(0.3f, 0.2f);
	Node* topCenter = CreateNode(0.5f, 0.2f);
	Node* topRight = CreateNode(0.7f, 0.2f);

	Node* midLeft = CreateNode(0.3f, 0.5f);
	Node* midCenter = CreateNode(0.5f, 0.5f);
	Node* midRight = CreateNode(0.7f, 0.5f);

	Node* botLeft = CreateNode(0.3f, 0.8f);
	Node* botCenter = CreateNode(0.5f, 0.8f);
	Node* botRight = CreateNode(0.7f, 0.8f);

	CreateConnection(midCenter, topLeft);
	CreateConnection(midCenter, topCenter);
	CreateConnection(midCenter, topRight);
	CreateConnection(midCenter, midLeft);
	CreateConnection(midCenter, midRight);
	CreateConnection(midCenter, botLeft);
	CreateConnection(midCenter, botCenter);
	CreateConnection(midCenter, botRight);

	CreateConnection(topLeft, topCenter);
	CreateConnection(topCenter, topRight);
	CreateConnection(topLeft, midLeft);
	CreateConnection(topRight, midRight);
	CreateConnection(botLeft, botCenter);
	CreateConnection(botLeft, midLeft);
	CreateConnection(botCenter, botRight);
	CreateConnection(botRight, midRight);

}

void ThreeBoard::Update()
{
	Board::Update();
}
