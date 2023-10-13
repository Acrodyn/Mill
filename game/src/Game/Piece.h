#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"
#include "UI/ClickableObject.h"

#include <cstdint>

typedef std::function<void()> Function;

class Player;
class Node;

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
	void MoveToPosition(Vector2 destination, Function onMovementEnd = nullptr);
	bool IsMoving() const;
	void SetAsSelected(bool isSelected = true);

private:
	void CheckForMovement();
	CLITERAL(Color) GetOutlineColor();

private:
	const float PIECE_SIZE = 40.f;

	CLITERAL(Color) _pieceColor;
	const uint8_t _owningPlayerID;
	bool _isRemovable = false;
	bool _isMoving = false;
	bool _isSelected = false;
	Vector2 _destination;
	float _movementSpeed = 0.8f;
	Function _onMovementEnd = nullptr;
};