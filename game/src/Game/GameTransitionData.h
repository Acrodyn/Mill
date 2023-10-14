#pragma once

#include "System/TransitionData.h"

enum class GameType
{
	Unset,
	ThreeManMorris,
	NineMenMorris
};

struct GameTransitionData : public TransitionData
{
	GameType GameType = GameType::Unset;
	bool HasFlight = false;
};