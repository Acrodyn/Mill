#pragma once

#include "raylib.h"
#include <cstdint>

enum class PlayerPhase;

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
	bool HasRemainingPieces() const;
	void SetColor(CLITERAL(Color) color);
	CLITERAL(Color) GetChosenColor() const;
	void SetPhase(PlayerPhase phase);
	void MarkAsVictor();
	PlayerPhase GetPhase() const;
	bool IsVictor() const;
	void ResetPlayer();

private:
	const uint8_t _id = 0;
	uint8_t _remainingPieces = 0;
	uint8_t _maxPieces = 0;
	uint16_t _winCount = 0;
	CLITERAL(Color) _chosenColor = WHITE;
	PlayerPhase _currentPhase;
	bool _isVictor = false;
};