#include "Label.h"
#include "raymath.h"
#include "System/Core.h"

Label::Label(float positionX, float positionY) : ScreenRelatedObject{ positionX, positionY }, _fontSize(DEFAULT_SIZE), _text(std::string()), _textColor(BLACK)
{

}

Label::Label(int fontSize, std::string text) : _fontSize(fontSize), _text(text), _textColor(BLACK)
{
	RefreshOffset();
}

Label::Label(float positionX, float positionY, int fontSize, std::string text) : ScreenRelatedObject{ positionX, positionY }, _fontSize(fontSize), _text(text), _textColor(BLACK)
{
	RefreshOffset();
}

Label::~Label()
{
	
}

void Label::Update()
{
	DrawText(_text.c_str(), GetPixelPositionX(), GetPixelPositionY(), _fontSize, _textColor);
}

Vector2 Label::GetTextDimensions()
{
	return MeasureTextEx(GetFontDefault(), _text.c_str(), (float)_fontSize, 2.f);
}

void Label::SetFontSize(int fontSize)
{
	_fontSize = fontSize;
	RefreshOffset();
}

void Label::SetText(const std::string& text)
{
	_text = text;
	RefreshOffset();
}

void Label::SetColor(const CLITERAL(Color)& color)
{
	_textColor = color;
}

void Label::RefreshOffset()
{
	SetOffset(Vector2Negate(Vector2Scale(GetTextDimensions(), 0.5f)));
}