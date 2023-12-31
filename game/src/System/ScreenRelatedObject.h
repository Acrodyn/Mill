#pragma once

#include "raylib.h"

class ScreenRelatedObject
{
public:
	ScreenRelatedObject();
	ScreenRelatedObject(float screenRelatedPosX, float screenRelatedPosY);
	ScreenRelatedObject(const Vector2& screenRelatedPosition);
	ScreenRelatedObject(ScreenRelatedObject* anchorObject);
	virtual ~ScreenRelatedObject();

	virtual void Update() = 0;

	int GetPixelPositionX() const;
	int GetPixelPositionY() const;
	Vector2 GetPixelPosition() const;
	Vector2 GetScreenRelatedPosition() const;
	void SetScreenRelatedPosition(const Vector2& newPosition);
	void SetPosition(const Vector2& newPosition);
	void SetAnchorObject(ScreenRelatedObject* anchorObject);
	void SetOffset(const Vector2& offset);

protected:
	Vector2 _screenRelatedPosition;
	ScreenRelatedObject* _anchorObject = nullptr;
	Vector2 _offset;
};