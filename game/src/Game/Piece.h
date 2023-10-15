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
	Piece(const Vector2& position, const Player* player);
	~Piece();

	void Update() override;
	void MarkAsRemovable(bool isRemovable = true);
	void MoveToPosition(const Vector2& destination, Function onMovementEnd = nullptr);
	void MarkAsSelected(bool isSelected = true);
	void MarkAsSelectable(bool isSelectable = true);
	const uint8_t GetOwningPlayerID() const;
	bool IsMoving() const;
	bool IsRemovable() const;

private:
	void CheckForMovement();
	CLITERAL(Color) GetOutlineColor();

private:
	const float PIECE_SIZE = 30.f;

	CLITERAL(Color) _pieceColor;
	const uint8_t _owningPlayerID;
	bool _isRemovable = false;
	bool _isMoving = false;
	bool _isSelected = false;
	bool _isSelectable = false;
	float _movementSpeed = 0.5f;
	Vector2 _destination;
	Function _onMovementEnd = nullptr;
};