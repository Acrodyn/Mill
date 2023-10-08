#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"

class Label;

class Button : public ScreenRelatedObject
{
public:
	Button() = delete;
	Button(float positionX, float positionY, float width, float height);
	~Button();

	void Update() override;

	void SetColor(CLITERAL(Color) color);
	void AttachLabel(Label* label);
	Label* GetLabel();

private:
	Vector2 _size;
	CLITERAL(Color) _buttonColor;
	Label* _attachedLabel = nullptr;
};