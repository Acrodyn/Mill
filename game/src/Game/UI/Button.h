#pragma once

#include "raylib.h"
#include "IClickable.h"
#include "System/ScreenRelatedObject.h"

class Label;

class Button : public ScreenRelatedObject, public ICLickable
{
public:
	Button() = delete;
	Button(float positionX, float positionY, float width, float height);
	~Button();

	void Update() override;
	bool IsMouseOnObject() override;
	void OnClickPressed() override;
	void OnClickReleased() override;

	void SetColor(CLITERAL(Color) color);
	void SetPressedColor(CLITERAL(Color) color);
	void AttachLabel(Label* label);
	Label* GetLabel();

private:
	void CheckForClick();

private:
	Vector2 _size;
	CLITERAL(Color) _buttonColor;
	CLITERAL(Color) _pressedColor;
	Label* _attachedLabel = nullptr;
	bool _isPressed = false;
};