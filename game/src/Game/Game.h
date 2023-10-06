#pragma once

#include "raylib.h"
#include "System/GamePhase.h"


class Game : public GamePhase
{
public:
	Game();
	~Game();

protected:
	void InitPhase() override;
	void DestroyPhase() override;
	void LoopPhase() override;

private:

private:
};