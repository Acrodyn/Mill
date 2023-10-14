#include "Label.h"
#include "System/Core.h"
#include "RefreshedLabel.h"

RefreshedLabel::RefreshedLabel(float positionX, float positionY) : Label(positionX, positionY)
{

}

RefreshedLabel::RefreshedLabel(int fontSize, const std::string& text) : Label(fontSize, text)
{

}

RefreshedLabel::RefreshedLabel(float positionX, float positionY, int fontSize, const std::string& text) : Label(positionX, positionY, fontSize, text)
{

}

RefreshedLabel::~RefreshedLabel()
{
	
}

void RefreshedLabel::Update()
{
	Label::Update();

	_timeUntilRefresh -= GetFrameTime();

	if (_timeUntilRefresh <= 0.f)
	{
		if (_refreshFunction != nullptr)
		{
			SetText(_refreshFunction());
		}

		_timeUntilRefresh = _refreshRate;
	}
}

void RefreshedLabel::RegisterRefreshFunction(RefreshFunction refreshFunction)
{
	_refreshFunction = refreshFunction;
}

void RefreshedLabel::SetRefreshRate(float refreshRate)
{
	_refreshRate = refreshRate;
	_timeUntilRefresh = 0.f;
}
