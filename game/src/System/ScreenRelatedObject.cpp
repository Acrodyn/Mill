#include "ScreenRelatedObject.h"
#include "System/Core.h"

ScreenRelatedObject::ScreenRelatedObject()
{
	_positionInRelationToScreen = Vector2();
}

ScreenRelatedObject::ScreenRelatedObject(float screenRelatedPosX, float screenRelatedPosY)
{
	_positionInRelationToScreen = Vector2({ screenRelatedPosX, screenRelatedPosY });
}

ScreenRelatedObject::ScreenRelatedObject(Vector2 positionInRelationToScreen)
{
	_positionInRelationToScreen = positionInRelationToScreen;
}

ScreenRelatedObject::~ScreenRelatedObject()
{

}

int ScreenRelatedObject::GetPositionX()
{
	return Core::GetPixelPositionWidth(_positionInRelationToScreen.x);
}

int ScreenRelatedObject::GetPositionY()
{
	return Core::GetPixelPositionHeight(_positionInRelationToScreen.y);
}

Vector2 ScreenRelatedObject::GetPosition()
{
	return Core::GetPixelPosition(_positionInRelationToScreen.x, _positionInRelationToScreen.y);
}

Vector2 ScreenRelatedObject::GetPositionInRelationToScreen()
{
	return _positionInRelationToScreen;
}