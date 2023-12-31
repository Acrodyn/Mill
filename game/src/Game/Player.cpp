#include "Player.h"
#include "Board.h"
#include "System/Core.h"

Player::Player(uint8_t id) : _id(id), _currentPhase(PlayerPhase::Unset)
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

bool Player::HasRemainingPieces() const
{
	return _remainingPieces > 0;
}

const uint8_t Player::GetRemainingPieces() const
{
	return _remainingPieces;
}

void Player::SetColor(const CLITERAL(Color)& color)
{
	_chosenColor = color;
}

const CLITERAL(Color) Player::GetChosenColor() const
{
	return _chosenColor;
}

void Player::SetPhase(PlayerPhase phase)
{
	_currentPhase = phase;
}

void Player::MarkAsVictor()
{
	++_winCount;
	_isWinner = true;
}

PlayerPhase Player::GetPhase() const
{
	return _currentPhase;
}

bool Player::IsWinner() const
{
	return _isWinner;
}

void Player::Reset()
{
	_isWinner = false;
	_remainingPieces = _maxPieces;
	_currentPhase = PlayerPhase::Placing;
}
