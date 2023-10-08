#include "Label.h"
#include "System/Core.h"

Label::Label(float positionX, float positionY) : ScreenRelatedObject{ positionX, positionY }, _fontSize(DEFAULT_SIZE), _text(nullptr), _textColor(BLACK)
{

}

Label::Label(int fontSize, char* text) : _fontSize(fontSize), _text(text), _textColor(BLACK)
{

}

Label::Label(float positionX, float positionY, int fontSize, char* text) : ScreenRelatedObject{ positionX, positionY }, _fontSize(fontSize), _text(text), _textColor(BLACK)
{

}

Label::~Label()
{
	
}

void Label::Update()
{
	DrawText(_text, GetPositionX(), GetPositionY(), _fontSize, _textColor);
}

Vector2 Label::GetTextDimensions()
{
	return MeasureTextEx(GetFontDefault(), _text, (float)_fontSize, 0.f);
}

void Label::SetFontSize(int fontSize)
{
	_fontSize = fontSize;
}

void Label::SetText(char* text)
{
	_text = text;
}

void Label::SetColor(CLITERAL(Color) color)
{
	_textColor = color;
}
