#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"

#include <string>

class Label : public ScreenRelatedObject
{
public:
	Label() = delete;
	Label(float positionX, float positionY);
	Label(int fontSize, std::string text = " ");
	Label(float positionX, float positionY, int fontSize, std::string text = " ");
	virtual ~Label();

	virtual void Update() override;

	void SetFontSize(int fontSize);
	void SetText(const std::string& text);
	void SetColor(const CLITERAL(Color)& color);
	void RefreshOffset();
	Vector2 GetTextDimensions();

protected:
	const int DEFAULT_SIZE = 30;

	int _fontSize;
	std::string _text;
	CLITERAL(Color) _textColor;
};