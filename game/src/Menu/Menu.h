#pragma once

#include "System/GamePhase.h"

enum class GameType;
class Label;

class Menu : public GamePhase
{
public:
	Menu(TransitionData** transitionData = nullptr);
	~Menu();

protected:
	void Loop() override;
	void InitUI() override;

private:
	void InitiateTransfer(GameType gameType, bool hasFlying = false);
	void AnimateTitle();

private:
	Label* _titleLabel = nullptr;
	float _fontSizeStart = 255.f;
	float _fontsizeEnd = 265.f;
	float _fontSizeCurrent = 0.f;
	float _sizeChangeRate = 20.f;
	bool _isTitleGrowing = true;
};