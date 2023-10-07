#include "Piece.h"
#include "System/Core.h"

Piece::Piece(Vector2 position) : ScreenRelatedObject{ position }
{

}

Piece::~Piece()
{
	
}

void Piece::Update()
{
	DrawCircleV(GetPosition(), PIECE_SIZE, RED);
}
