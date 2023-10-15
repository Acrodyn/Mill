#include "ClickableObject.h"
#include "raylib.h"

void ClickableObject::OnClickPressed()
{
	if (_onClick != nullptr)
	{
		_onClick();
	}
}

void ClickableObject::OnClickReleased()
{
	if (_OnRelease != nullptr)
	{
		_OnRelease();
	}
}

void ClickableObject::RegisterOnClick(VoidFunction onClick)
{
	_onClick = onClick;
}

void ClickableObject::RegisterOnRelease(VoidFunction onRelease)
{
	_OnRelease = onRelease;
}

void ClickableObject::CheckForClick()
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && IsMouseOnObject())
	{
		_isPressed = true;
		OnClickPressed();
	}
	else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		if (IsMouseOnObject())
		{
			OnClickReleased();
		}

		_isPressed = false;
	}
}
