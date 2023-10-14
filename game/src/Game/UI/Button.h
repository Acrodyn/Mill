#pragma once

#include "raylib.h"
#include "ClickableObject.h"
#include "System/ScreenRelatedObject.h"

class Label;

class Button : public ScreenRelatedObject, public ClickableObject
{
public:
	Button() = delete;
	Button(float positionX, float positionY, float width, float height);
	~Button();

	void Update() override;
	bool IsMouseOnObject() override;

	void SetColor(const CLITERAL(Color)& color);
	void SetPressedColor(const CLITERAL(Color)& color);
	void AttachLabel(Label* label);
	Label* GetLabel();

private:
	Vector2 _size;
	CLITERAL(Color) _buttonColor;
	CLITERAL(Color) _pressedColor;
	Label* _attachedLabel = nullptr;
};