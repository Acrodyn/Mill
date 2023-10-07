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
	DrawCircle(100, 100, 50.f, RED);
}
