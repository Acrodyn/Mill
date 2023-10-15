#include "ScreenRelatedObject.h"
#include "System/Core.h"
#include "raymath.h"

ScreenRelatedObject::ScreenRelatedObject()
{
	_screenRelatedPosition = Vector2();
	_offset = Vector2();
}

ScreenRelatedObject::ScreenRelatedObject(float screenRelatedPosX, float screenRelatedPosY)
{
	_screenRelatedPosition = Vector2({ screenRelatedPosX, screenRelatedPosY });
	_offset = Vector2();
}

ScreenRelatedObject::ScreenRelatedObject(const Vector2& screenRelatedPosition)
{
	_screenRelatedPosition = screenRelatedPosition;
	_offset = Vector2();
}

ScreenRelatedObject::ScreenRelatedObject(ScreenRelatedObject* anchorObject) : _anchorObject(anchorObject)
{
	_screenRelatedPosition = Vector2({ 0.f, 0.f });
	_offset = Vector2();
}

ScreenRelatedObject::~ScreenRelatedObject()
{

}

int ScreenRelatedObject::GetPixelPositionX() const
{
	if (_anchorObject != nullptr)
	{
		return _anchorObject->GetPixelPositionX() + (int)_offset.x;
	}

	return (int)(Core::GetPixelPositionWidth(_screenRelatedPosition.x) + _offset.x);
}

int ScreenRelatedObject::GetPixelPositionY() const
{
	if (_anchorObject != nullptr)
	{
		return _anchorObject->GetPixelPositionY() + (int)_offset.y;
	}

	return (int)(Core::GetPixelPositionHeight(_screenRelatedPosition.y) + _offset.y);
}

Vector2 ScreenRelatedObject::GetPixelPosition() const
{
	if (_anchorObject != nullptr)
	{
		return Vector2Add(_anchorObject->GetPixelPosition(), _offset);
	}

	return Vector2Add(Core::GetPixelPosition(_screenRelatedPosition.x, _screenRelatedPosition.y), _offset);
}

Vector2 ScreenRelatedObject::GetScreenRelatedPosition() const
{
	return _screenRelatedPosition;
}

void ScreenRelatedObject::SetScreenRelatedPosition(const Vector2& newPosition)
{
	_screenRelatedPosition = newPosition;
}

void ScreenRelatedObject::SetPosition(const Vector2& newPosition)
{
	_screenRelatedPosition = Core::GetScreenRelatedPosition(newPosition);
}

void ScreenRelatedObject::SetAnchorObject(ScreenRelatedObject* anchorObject)
{
	_anchorObject = anchorObject;
}

void ScreenRelatedObject::SetOffset(const Vector2& offset)
{
	_offset = offset;
}