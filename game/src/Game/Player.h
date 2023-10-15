#pragma once

#include "raylib.h"
#include <cstdint>

enum class PlayerPhase;

class Player
{
public:
	Player(uint8_t id);
	~Player();

	void SetPieceCount(uint8_t pieceCount);
	void AddPiece();
	void RemovePiece();
	void SetColor(const CLITERAL(Color)& color);
	void SetPhase(PlayerPhase phase);
	void MarkAsVictor();
	void Reset();
	const uint8_t GetID() const;
	const uint8_t GetRemainingPieces() const;
	bool IsWinner() const;
	bool HasRemainingPieces() const;
	PlayerPhase GetPhase() const;
	const CLITERAL(Color) GetChosenColor() const;

private:
	const uint8_t _id = 0;
	uint8_t _remainingPieces = 0;
	uint8_t _maxPieces = 0;
	uint16_t _winCount = 0;
	CLITERAL(Color) _chosenColor = WHITE;
	PlayerPhase _currentPhase;
	bool _isWinner = false;
};