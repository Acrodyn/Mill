#include "Piece.h"
#include "Player.h"
#include "Node.h"
#include "raymath.h"
#include "System/Core.h"

Piece::Piece(const Vector2& position, const Player* player) : ScreenRelatedObject{ position }, _owningPlayerID(player->GetID()), _pieceColor(player->GetChosenColor()), _destination(Vector2{})
{

}

Piece::~Piece()
{
	
}

void Piece::Update()
{
	CheckForMovement();
	Vector2 position = GetPixelPosition();

	DrawCircleV(position, PIECE_SIZE, _pieceColor);
	DrawRing(position, 10.f, 12.f, 0.f, 360.f, 0, Fade(BLACK, .7f));
	DrawRing(position, 25.f, 27.f, 0.f, 360.f, 0, Fade(BLACK, .7f));
	DrawRing(position, PIECE_SIZE, PIECE_SIZE + 3.f, 0.f, 360.f, 0, GetOutlineColor());
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

void Piece::MoveToPosition(const Vector2& destination, Function onMovementEnd)
{
	_destination = destination;
	_onMovementEnd = onMovementEnd;
	_isMoving = true;
}

bool Piece::IsMoving() const
{
	return _isMoving;
}

void Piece::MarkAsSelected(bool isSelected)
{
	_isSelected = isSelected;
}

void Piece::MarkAsSelectable(bool isSelectable)
{
	_isSelectable = isSelectable;
}

void Piece::CheckForMovement()
{
	if (!_isMoving)
	{
		return;
	}

	SetScreenRelatedPosition(Vector2MoveTowards(GetScreenRelatedPosition(), _destination, _movementSpeed * GetFrameTime()));

	if (Vector2Equals(GetScreenRelatedPosition(), _destination))
	{
		_isMoving = false;
		_onMovementEnd();
	}
}

CLITERAL(Color) Piece::GetOutlineColor()
{
	if (_isSelected)
	{
		return GREEN;
	}
	else if (_isSelectable)
	{
		return PURPLE;
	}
	else if (_isRemovable)
	{
		return RED;
	}

	return BLACK;
}
