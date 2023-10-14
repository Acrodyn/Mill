#pragma once

#include "System/GamePhase.h"

enum class GameType;

class Menu : public GamePhase
{
public:
	Menu(TransitionData** transitionData = nullptr);
	~Menu();

protected:
	void Loop() override;

private:

	void InitiateTransfer(GameType gameType, bool hasFlying = false);
};