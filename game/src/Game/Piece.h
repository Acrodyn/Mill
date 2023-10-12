#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"

#include <cstdint>

class Player;

class Piece : public ScreenRelatedObject
{
public:
	Piece() = delete;
	Piece(Vector2 position, const Player* player);
	~Piece();

	void Update() override;
	const uint8_t GetOwningPlayerID() const;
	bool IsRemovable() const;
	void MarkAsRemovable(bool isRemovable = true);

private:
	const float PIECE_SIZE = 40.f;
	CLITERAL(Color) _pieceColor;
	const uint8_t _owningPlayerID;
	bool _isRemovable = false;
};