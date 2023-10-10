#pragma once

#include "raylib.h"

class ScreenRelatedObject
{
public:
	ScreenRelatedObject();
	ScreenRelatedObject(float screenRelatedPosX, float screenRelatedPosY);
	ScreenRelatedObject(Vector2 screenRelatedPosition);
	ScreenRelatedObject(ScreenRelatedObject* anchorObject);
	virtual ~ScreenRelatedObject();

	virtual void Update() = 0;

	int GetPositionX() const;
	int GetPositionY() const;
	Vector2 GetPosition() const;
	Vector2 GetScreenRelatedPosition() const;
	void SetAnchorObject(ScreenRelatedObject* anchorObject);
	void SetOffset(Vector2 offset);

protected:
	Vector2 _screenRelatedPosition;
	ScreenRelatedObject* _anchorObject = nullptr;
	Vector2 _offset;
};