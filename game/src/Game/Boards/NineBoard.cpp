#include "NineBoard.h"
#include "System/Core.h"
#include "Game/Connection.h"

NineBoard::NineBoard() : Board(9)
{

}

NineBoard::~NineBoard()
{
	
}

void NineBoard::SetupBoard()
{
	Node* firstLayerLeft = CreateNode(0.2f, 0.05f);
	Node* firstLayerCenter = CreateNode(0.5f, 0.05f);
	Node* firstLayerRight = CreateNode(0.8f, 0.05f);

	Node* secondLayerLeft = CreateNode(0.3f, 0.2f);
	Node* secondLayerCenter = CreateNode(0.5f, 0.2f);
	Node* secondLayerRight = CreateNode(0.7f, 0.2f);

	Node* thirdLayerLeft = CreateNode(0.4f, 0.35f);
	Node* thirdLayerCenter = CreateNode(0.5f, 0.35f);
	Node* thirdLayerRight = CreateNode(0.6f, 0.35f);

	Node* fourthLayerLeft = CreateNode(0.2f, 0.5f);
	Node* fourthLayerCenter = CreateNode(0.3f, 0.5f);
	Node* fourthLayerRight = CreateNode(0.4f, 0.5f);

	Node* fifthLayerLeft = CreateNode(0.6f, 0.5f);
	Node* fifthLayerCenter = CreateNode(0.7f, 0.5f);
	Node* fifthLayerRight = CreateNode(0.8f, 0.5f);

	Node* sixthLayerLeft = CreateNode(0.4f, 0.65f);
	Node* sixthLayerCenter = CreateNode(0.5f, 0.65f);
	Node* sixthLayerRight = CreateNode(0.6f, 0.65f);

	Node* seventhLayerLeft = CreateNode(0.3f, 0.8f);
	Node* seventhLayerCenter = CreateNode(0.5f, 0.8f);
	Node* seventhLayerRight = CreateNode(0.7f, 0.8f);

	Node* eightLayerLeft = CreateNode(0.2f, 0.95f);
	Node* eightLayerCenter = CreateNode(0.5f, 0.95f);
	Node* eightLayerRight = CreateNode(0.8f, 0.95f);

	CreateConnection(firstLayerLeft, firstLayerCenter, firstLayerRight, ConnectionDirection::Horizontal);
	CreateConnection(secondLayerLeft, secondLayerCenter, secondLayerRight, ConnectionDirection::Horizontal);
	CreateConnection(thirdLayerLeft, thirdLayerCenter, thirdLayerRight, ConnectionDirection::Horizontal);
	CreateConnection(fourthLayerLeft, fourthLayerCenter, fourthLayerRight, ConnectionDirection::Horizontal);
	CreateConnection(fifthLayerLeft, fifthLayerCenter, fifthLayerRight, ConnectionDirection::Horizontal);
	CreateConnection(sixthLayerLeft, sixthLayerCenter, sixthLayerRight, ConnectionDirection::Horizontal);
	CreateConnection(seventhLayerLeft, seventhLayerCenter, seventhLayerRight, ConnectionDirection::Horizontal);
	CreateConnection(eightLayerLeft, eightLayerCenter, eightLayerRight, ConnectionDirection::Horizontal);

	CreateConnection(firstLayerLeft, fourthLayerLeft, eightLayerLeft, ConnectionDirection::Vertical);
	CreateConnection(secondLayerLeft, fourthLayerCenter, seventhLayerLeft, ConnectionDirection::Vertical);
	CreateConnection(thirdLayerLeft, fourthLayerRight, sixthLayerLeft, ConnectionDirection::Vertical);
	CreateConnection(firstLayerCenter, secondLayerCenter, thirdLayerCenter, ConnectionDirection::Vertical);
	CreateConnection(thirdLayerRight, fifthLayerLeft, sixthLayerRight, ConnectionDirection::Vertical);
	CreateConnection(secondLayerRight, fifthLayerCenter, seventhLayerRight, ConnectionDirection::Vertical);
	CreateConnection(sixthLayerCenter, seventhLayerCenter, eightLayerCenter, ConnectionDirection::Vertical);
	CreateConnection(firstLayerRight, fifthLayerRight, eightLayerRight, ConnectionDirection::Vertical);
}

bool NineBoard::CheckForWinConditions(WinCondition winCondition)
{
	return winCondition == WinCondition::LowPieceCount || winCondition == WinCondition::InsufficientMoves;
}
