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

}

void ThreeBoard::Update()
{
	Board::Update();
}
