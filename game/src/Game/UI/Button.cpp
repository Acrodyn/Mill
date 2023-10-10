#include "Button.h"
#include "Label.h"
#include "raymath.h"
#include <algorithm>

Button::Button(float positionX, float positionY, float width, float height) : ScreenRelatedObject{ positionX, positionY }, _size(Vector2{ width, height}), _buttonColor(LIGHTGRAY), _pressedColor(GRAY)
{
	SetOffset(Vector2Negate(Vector2Scale(_size, 0.5f)));
}

Button::~Button()
{
	if (_attachedLabel != nullptr)
	{
		delete _attachedLabel;
	}
}

void Button::Update()
{
	CheckForClick();

	CLITERAL(Color) color = _isPressed ? _pressedColor : _buttonColor;
	DrawRectangleV(GetPosition(), _size, color);

	if (_attachedLabel != nullptr)
	{
		_attachedLabel->Update();
	}
}

bool Button::IsMouseOnObject()
{
	return CheckCollisionPointRec(GetMousePosition(), Rectangle({(float)GetPositionX(), (float)GetPositionY(), _size.x, _size.y}));
}

void Button::OnClickPressed()
{
	if (_onClick != nullptr)
	{
		_onClick();
	}
}

void Button::OnClickReleased()
{
	if (_OnRelease !=  nullptr)
	{
		_OnRelease();
	}
}

void Button::RegisterOnClick(Function onClick)
{
	_onClick = onClick;
}

void Button::RegisterOnRelease(Function onRelease)
{
	_OnRelease = onRelease;
}

void Button::SetColor(CLITERAL(Color) color)
{
	_buttonColor = color;
}

void Button::SetPressedColor(CLITERAL(Color) color)
{
	_pressedColor = color;
}

void Button::AttachLabel(Label* label)
{
	_attachedLabel = label;
	_attachedLabel->SetAnchorObject(this);

	Vector2 labelDimensions = label->GetTextDimensions();
	int gapX = std::max((int)(_size.x - labelDimensions.x), 0);
	int gapY = std::max((int)(_size.y - labelDimensions.y), 0);
	label->SetOffset(Vector2({ gapX / 2.f, gapY / 2.f }));
}

Label* Button::GetLabel()
{
	return _attachedLabel;
}

void Button::CheckForClick()
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
