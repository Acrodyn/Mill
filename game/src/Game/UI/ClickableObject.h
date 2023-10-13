#pragma once

#include <functional>

typedef std::function<void()> Function;


class ClickableObject
{
public:
	ClickableObject() {};
	virtual ~ClickableObject() {};

	void RegisterOnClick(Function onClick);
	void RegisterOnRelease(Function onRelease);
	void CheckForClick();

protected:
	virtual bool IsMouseOnObject() = 0;
	virtual void OnClickPressed();
	virtual void OnClickReleased();

protected:
	bool _isPressed = false;

	Function _onClick = nullptr;
	Function _OnRelease = nullptr;
};