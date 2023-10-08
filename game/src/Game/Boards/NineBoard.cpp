#include "NineBoard.h"
#include "System/Core.h"

NineBoard::NineBoard()
{
	_piecesPerPlayer = 9;
	_nodesCount = 24;
}

NineBoard::~NineBoard()
{
	
}

void NineBoard::Init()
{

}

void NineBoard::Update()
{
	Board::Update();
}

bool NineBoard::CheckForWinConditions()
{
	return false;
}
