#pragma once

#include "System/GamePhase.h"

class Menu : public GamePhase
{
public:
	Menu();

protected:
	void LoopPhase() override;

private:
};