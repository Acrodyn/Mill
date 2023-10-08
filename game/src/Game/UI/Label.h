#pragma once

#include "raylib.h"
#include "System/ScreenRelatedObject.h"

class Label : public ScreenRelatedObject
{
public:
	Label() = delete;
	Label(float positionX, float positionY);
	Label(int fontSize, char* text);
	Label(float positionX, float positionY, int fontSize, char* text);
	~Label();

	void Update() override;

	Vector2 GetTextDimensions();
	void SetFontSize(int fontSize);
	void SetText(char* text);
	void SetColor(CLITERAL(Color) color);

private:
	const int DEFAULT_SIZE = 10;

	int _fontSize;
	char* _text;
	CLITERAL(Color) _textColor;
};