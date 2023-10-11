#pragma once

#include "raylib.h"
#include <cstdint>

class Player
{
public:
	Player(uint8_t id);
	~Player();

	const uint8_t GetID() const;
	void SetPieceCount(uint8_t pieceCount);
	void AddPiece();
	void RemovePiece();
	uint8_t GetRemainingPieces() const;
	void SetColor(CLITERAL(Color) color);
	CLITERAL(Color) GetChosenColor() const;

private:
	const uint8_t _id = 0;
	uint8_t _remainingPieces = 0;
	uint8_t _maxPieces = 0;
	CLITERAL(Color) _chosenColor = WHITE;
};