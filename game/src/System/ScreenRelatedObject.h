#pragma once

#include "raylib.h"

class ScreenRelatedObject
{
public:
	ScreenRelatedObject();
	ScreenRelatedObject(float screenRelatedPosX, float screenRelatedPosY);
	ScreenRelatedObject(Vector2 positionInRelationToScreen);
	virtual ~ScreenRelatedObject();

	int GetPositionX();
	int GetPositionY();
	Vector2 GetPosition();
	Vector2 GetPositionInRelationToScreen();

protected:
	Vector2 _positionInRelationToScreen;
};