#include "Piece.h"
#include "Player.h"
#include "System/Core.h"

Piece::Piece(Vector2 position, const Player* player) : ScreenRelatedObject{ position }, _owningPlayerID(player->GetID()), _pieceColor(player->GetChosenColor())
{

}

Piece::~Piece()
{
	
}

void Piece::Update()
{
	Vector2 position = GetPosition();

	DrawCircleV(position, PIECE_SIZE, _pieceColor);
	DrawRing(position, 10.f, 12.f, 0.f, 360.f, 0, Fade(BLACK, .7f));
	DrawRing(position, 25.f, 27.f, 0.f, 360.f, 0, Fade(BLACK, .7f));
	DrawRing(position, PIECE_SIZE, PIECE_SIZE + 3.f, 0.f, 360.f, 0, _isRemovable ? GREEN : BLACK);
}

const uint8_t Piece::GetOwningPlayerID() const
{
	return _owningPlayerID;
}

bool Piece::IsRemovable() const
{
	return _isRemovable;
}

void Piece::MarkAsRemovable(bool isRemovable)
{
	_isRemovable = isRemovable;
}
