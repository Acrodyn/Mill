#include "Player.h"
#include "System/Core.h"

Player::Player()
{

}

Player::~Player()
{
	
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

uint8_t Player::GetRemainingPieces()
{
	return _remainingPieces;
}
