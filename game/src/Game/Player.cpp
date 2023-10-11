#include "Player.h"
#include "System/Core.h"

Player::Player(uint8_t id) : _id(id)
{

}

Player::~Player()
{
	
}

const uint8_t Player::GetID() const
{
	return _id;
}

void Player::SetPieceCount(uint8_t pieceCount)
{
	_maxPieces = pieceCount;
	_remainingPieces = _maxPieces;
}

void Player::AddPiece()
{
	if (_remainingPieces < _maxPieces)
	{
		++_remainingPieces;
	}
}

void Player::RemovePiece()
{
	if (_remainingPieces > 0)
	{
		--_remainingPieces;
	}
}

uint8_t Player::GetRemainingPieces() const
{
	return _remainingPieces;
}

void Player::SetColor(CLITERAL(Color) color)
{
	_chosenColor = color;
}

CLITERAL(Color) Player::GetChosenColor() const
{
	return _chosenColor;
}
