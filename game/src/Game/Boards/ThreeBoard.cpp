#include "ThreeBoard.h"
#include "System/Core.h"
#include "Game/Connection.h"

ThreeBoard::ThreeBoard() : Board(3, true)
{

}

ThreeBoard::~ThreeBoard()
{
	
}

void ThreeBoard::SetupBoard()
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

	CreateConnection(midCenter, topLeft, ConnectionDirection::DiagonalRight);
	CreateConnection(midCenter, topCenter, ConnectionDirection::Vertical);
	CreateConnection(midCenter, topRight, ConnectionDirection::DiagonalLeft);
	CreateConnection(midCenter, midLeft, ConnectionDirection::Horizontal);
	CreateConnection(midCenter, midRight, ConnectionDirection::Horizontal);
	CreateConnection(midCenter, botLeft, ConnectionDirection::DiagonalLeft);
	CreateConnection(midCenter, botCenter, ConnectionDirection::Vertical);
	CreateConnection(midCenter, botRight, ConnectionDirection::DiagonalRight);

	CreateConnection(topLeft, topCenter, ConnectionDirection::Horizontal);
	CreateConnection(topCenter, topRight, ConnectionDirection::Horizontal);
	CreateConnection(topLeft, midLeft, ConnectionDirection::Vertical);
	CreateConnection(topRight, midRight, ConnectionDirection::Vertical);
	CreateConnection(botLeft, botCenter, ConnectionDirection::Horizontal);
	CreateConnection(botLeft, midLeft, ConnectionDirection::Vertical);
	CreateConnection(botCenter, botRight, ConnectionDirection::Horizontal);
	CreateConnection(botRight, midRight, ConnectionDirection::Vertical);
}

bool ThreeBoard::CheckForWinConditions()
{
	return false;
}
