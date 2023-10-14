#include "Menu.h"
#include "raylib.h"
#include "System/Core.h"
#include "Game/UI/Button.h"
#include "Game/UI/Label.h"
#include "Game/GameTransitionData.h"

Menu::Menu(TransitionData** transitionData) : GamePhase(transitionData)
{
	InitiateTransfer(GameType::ThreeManMorris);
}

Menu::~Menu()
{

}

void Menu::Loop()
{
	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), DARKGRAY);
	DrawText("Test", 200, 200, 20, WHITE);

	if (_phaseState != GamePhaseState::Ending)
	{
		if (Core::IsInteractPressed())
		{
			_phaseState = GamePhaseState::Ending;
		}
	}
}

void Menu::InitiateTransfer(GameType gameType, bool hasFlying)
{
	if (*_transitionData != nullptr)
	{
		delete *_transitionData;
	}

	GameTransitionData* transferData = new GameTransitionData();
	transferData->GameType = gameType;
	transferData->HasFlight = hasFlying;
	(*_transitionData) = transferData;

	_phaseState = GamePhaseState::Ending;
}
