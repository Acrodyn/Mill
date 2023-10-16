#pragma once

#include "Label.h"
#include "System/SystemGlobals.h"
#include <functional>

class RefreshedLabel : public Label
{
public:
	RefreshedLabel() = delete;
	RefreshedLabel(float positionX, float positionY);
	RefreshedLabel(int fontSize, const std::string& text = " ");
	RefreshedLabel(float positionX, float positionY, int fontSize, const std::string& text = " ");
	~RefreshedLabel();

	void Update() override;

	void RegisterRefreshFunction(StringFunction refreshFunction);
	void SetRefreshRate(float refreshRate);

private:
	StringFunction _refreshFunction;
	float _refreshRate = 0.3f;
	float _timeUntilRefresh = 0.f;
};