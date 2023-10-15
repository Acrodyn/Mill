#pragma once

#include "System/SystemGlobals.h"

#include <functional>

class ClickableObject
{
public:
	ClickableObject() {};
	virtual ~ClickableObject() {};

	void RegisterOnClick(VoidFunction onClick);
	void RegisterOnRelease(VoidFunction onRelease);
	void CheckForClick();

protected:
	virtual bool IsMouseOnObject() = 0;
	virtual void OnClickPressed();
	virtual void OnClickReleased();

protected:
	bool _isPressed = false;

	VoidFunction _onClick = nullptr;
	VoidFunction _OnRelease = nullptr;
};