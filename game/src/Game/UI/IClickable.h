#pragma once

#include <functional>

typedef std::function<void()> Function;


class IClickable
{
public:
	IClickable() {};
	virtual ~IClickable() {};

	virtual bool IsMouseOnObject() = 0;
	virtual void OnClickPressed() = 0;
	virtual void OnClickReleased() = 0;
	virtual void RegisterOnClick(Function onClick) = 0;
	virtual void RegisterOnRelease(Function onRelease) = 0;
};