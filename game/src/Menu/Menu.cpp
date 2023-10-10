#include "Menu.h"
#include "raylib.h"
#include "System/Core.h"

Menu::Menu()
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
