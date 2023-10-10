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

ScreenRelatedObject::ScreenRelatedObject(Vector2 screenRelatedPosition)
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

int ScreenRelatedObject::GetPositionX() const
{
	if (_anchorObject != nullptr)
	{
		return _anchorObject->GetPositionX() + (int)_offset.x;
	}

	return (int)(Core::GetPixelPositionWidth(_screenRelatedPosition.x) + _offset.x);
}

int ScreenRelatedObject::GetPositionY() const
{
	if (_anchorObject != nullptr)
	{
		return _anchorObject->GetPositionY() + (int)_offset.y;
	}

	return (int)(Core::GetPixelPositionHeight(_screenRelatedPosition.y) + _offset.y);
}

Vector2 ScreenRelatedObject::GetPosition() const
{
	if (_anchorObject != nullptr)
	{
		return Vector2Add(_anchorObject->GetPosition(), _offset);
	}

	return Vector2Add(Core::GetPixelPosition(_screenRelatedPosition.x, _screenRelatedPosition.y), _offset);
}

Vector2 ScreenRelatedObject::GetScreenRelatedPosition() const
{
	return _screenRelatedPosition;
}

void ScreenRelatedObject::SetAnchorObject(ScreenRelatedObject* anchorObject)
{
	_anchorObject = anchorObject;
}

void ScreenRelatedObject::SetOffset(Vector2 offset)
{
	_offset = offset;
}