#include "RectangleMarker.h"
#include "raymath.h"
#include "System/Core.h"

RectangleMarker::RectangleMarker(float positionX, float positionY, float sizeX, float sizeY) : ScreenRelatedObject(positionX, positionY), _size(Vector2({ sizeX, sizeY })), _normalColor(MAROON), _highlightedColor(GOLD)
{
	SetOffset(Vector2Negate(Vector2Scale(_size, 0.5f)));
}

RectangleMarker::RectangleMarker(Vector2 position, Vector2 size) : ScreenRelatedObject(position.x, position.y), _size(size), _normalColor(RED), _highlightedColor(YELLOW)
{
	SetOffset(Vector2Negate(Vector2Scale(_size, 0.5f)));
}

RectangleMarker::~RectangleMarker()
{
}

void RectangleMarker::Update()
{
	if (!_shouldMark())
	{
		return;
	}

	DrawRectangleRoundedLines(Rectangle({ (float)GetPixelPositionX(), (float)GetPixelPositionY(), _size.x, _size.y }), 5.f, 1, 5.f, _shouldHighlight() ? _highlightedColor : _normalColor);
}

void RectangleMarker::SetShouldMarkDelegate(BoolFunction shouldMarkFunction)
{
	_shouldMark = shouldMarkFunction;
}

void RectangleMarker::SetShouldHighlightDelegate(BoolFunction shouldHighlightFunction)
{
	_shouldHighlight = shouldHighlightFunction;
}
