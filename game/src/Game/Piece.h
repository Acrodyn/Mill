#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"

class Piece : public ScreenRelatedObject
{
public:
	Piece() = delete;
	Piece(Vector2 position);
	~Piece();

	void Update();

private:
	const float PIECE_SIZE = 40.f;
};