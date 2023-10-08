#pragma once


class ICLickable
{
public:
	virtual bool IsMouseOnObject() = 0;
	virtual void OnClickPressed() = 0;
	virtual void OnClickReleased() = 0;
};