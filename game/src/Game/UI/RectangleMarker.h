#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"
#include "System/SystemGlobals.h"

class RectangleMarker : public ScreenRelatedObject
{
public:
	RectangleMarker() = delete;
	RectangleMarker(float positionX, float positionY, float sizeX, float sizeY);
	RectangleMarker(Vector2 position, Vector2 size);
	~RectangleMarker();

	virtual void Update() override;

	void SetShouldMarkDelegate(BoolFunction shouldMarkFunction);
	void SetShouldHighlightDelegate(BoolFunction shouldHighlightFunction);

private:
	Vector2 _size;
	CLITERAL(Color) _normalColor;
	CLITERAL(Color) _highlightedColor;
	BoolFunction _shouldMark;
	BoolFunction _shouldHighlight;
};