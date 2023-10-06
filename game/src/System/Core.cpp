#include "Core.h"
#include "GamePhase.h"
#include "Menu/Menu.h"
#include "Game/Game.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

Core::Core()
{

}

void Core::Run()
{
	if (!Init())
	{
		return;
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		_gamePhase->Update();
		EndDrawing();
		CheckForPhaseChange();
		CheckForSystemInputs();

		//std::cout << GetFPS() << std::endl;
	}

	Terminate();
}

bool Core::IsInteractPressed()
{
	return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE);
}

bool Core::IsInteractDown()
{
	return IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_SPACE);;
}

bool Core::IsScreenModifierPressed()
{
	return IsKeyReleased(KEY_ENTER);
}

Vector2 Core::GetScreenCenter()
{
	return { (GetDisplayWidth()) / 2.0f, GetDisplayHeight() / 2.0f };
}

int Core::GetDisplayWidth()
{
	if (IsWindowFullscreen())
	{
		int display = GetCurrentMonitor();
		return GetMonitorWidth(display);
	}
	else
	{
		return GetScreenWidth();
	}
}

int Core::GetDisplayHeight()
{
	if (IsWindowFullscreen())
	{
		int display = GetCurrentMonitor();
		return GetMonitorHeight(display);
	}
	else
	{
		return GetScreenHeight();
	}
}

int Core::GetPixelPositionWidth(float percentage)
{
	return percentage * GetDisplayWidth();
}

int Core::GetPixelPositionHeight(float percentage)
{
	return percentage * GetDisplayHeight();
}

bool Core::Init()
{
	try
	{
		SetConfigFlags(FLAG_MSAA_4X_HINT);
		InitWindow(defaultScreenWidth, defaultScreenHeight, "Mlin");
		SetTargetFPS(120);
		//SetFullScreen();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return false;
	}

	//InitAppState(AppPhase::Menu);
	InitAppState(AppPhase::Game); // for testing

	return true;
}

void Core::Terminate()
{
	CloseWindow();
}

void Core::InitAppState(AppPhase newState)
{
	if (_currentState == newState)
	{
		return;
	}

	_currentState = newState;

	if (_gamePhase != nullptr)
	{
		_gamePhase->End();
		delete _gamePhase;
	}

	switch (_currentState)
	{
	case AppPhase::Menu:
		_gamePhase = new Menu();
		break;
	case AppPhase::Game:
		_gamePhase = new Game();
		break;
	default:
		return;
	}

	_gamePhase->Start();
}

void Core::CheckForPhaseChange()
{
	if (_gamePhase->IsEnded())
	{
		InitAppState(GetNextPhase());
	}
}

void Core::CheckForSystemInputs()
{
	if (IsScreenModifierPressed())
	{
		SwitchFullScreen();
	}
}

AppPhase Core::GetNextPhase()
{
	if (_gamePhase == nullptr)
	{
		return AppPhase::Unset;
	}

	switch (_currentState)
	{
	case AppPhase::Menu:
		return AppPhase::Game;
	case AppPhase::Game:
		return AppPhase::Menu;
	default:
		return AppPhase::Unset;
	}
}

void Core::SetFullScreen()
{
	int display = GetCurrentMonitor();
	SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
	ToggleFullscreen();
}

void Core::ExitFullScreen()
{
	if (IsWindowFullscreen())
	{
		ToggleFullscreen();
		SetWindowSize(defaultScreenWidth, defaultScreenHeight);
	}
}

void Core::SwitchFullScreen()
{
	if (IsWindowFullscreen())
	{
		ExitFullScreen();
	}
	else
	{
		SetFullScreen();
	}
}
