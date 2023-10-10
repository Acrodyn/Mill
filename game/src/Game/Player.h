#pragma once

#include "raylib.h"
#include <cstdint>

class Player
{
public:
	Player();
	~Player();

	void SetPieceCount(uint8_t pieceCount);
	void AddPiece();
	void RemovePiece();
	uint8_t GetRemainingPieces();

private:
	uint8_t _remainingPieces = 0;
	uint8_t _maxPieces = 0;
};