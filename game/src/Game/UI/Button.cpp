#include "Button.h"
#include "Label.h"
#include "raymath.h"
#include <algorithm>

Button::Button(float positionX, float positionY, float width, float height) : ScreenRelatedObject{ positionX, positionY }, _size(Vector2{ width, height}), _buttonColor(MAGENTA)
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
	DrawRectangleV(GetPosition(), _size, _buttonColor);

	if (_attachedLabel != nullptr)
	{
		_attachedLabel->Update();
	}
}

void Button::SetColor(CLITERAL(Color) color)
{
	_buttonColor = color;
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
