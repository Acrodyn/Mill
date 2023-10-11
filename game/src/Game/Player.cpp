#include "Player.h"
#include "Board.h"
#include "System/Core.h"

Player::Player(uint8_t id) : _id(id), _currentPhase(PlayerPhase::Unset),  _previousPhase(PlayerPhase::Unset)
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

void Player::SetPhase(PlayerPhase phase)
{
	_previousPhase = _currentPhase;
	_currentPhase = phase;
}

void Player::BacktrackPhase()
{
	if (_previousPhase == PlayerPhase::Unset)
	{
		return;
	}

	_currentPhase = _previousPhase;
	_previousPhase = PlayerPhase::Unset;
}

PlayerPhase Player::GetPhase()
{
	return _currentPhase;
}
