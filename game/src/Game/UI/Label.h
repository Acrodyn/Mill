#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"

#include <string>

class Label : public ScreenRelatedObject
{
public:
	Label() = delete;
	Label(float positionX, float positionY);
	Label(int fontSize, std::string text);
	Label(float positionX, float positionY, int fontSize, std::string text);
	virtual ~Label();

	virtual void Update() override;

	Vector2 GetTextDimensions();
	void SetFontSize(int fontSize);
	void SetText(char* text);
	void SetText(std::string text);
	void SetColor(CLITERAL(Color) color);
	void RefreshOffset();

protected:
	const int DEFAULT_SIZE = 50;

	int _fontSize;
	std::string _text;
	CLITERAL(Color) _textColor;
};