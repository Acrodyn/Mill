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

Vector2 Core::GetPixelPosition(float percentageX, float percentageY)
{
	return Vector2({ (float)GetPixelPositionWidth(percentageX), (float)GetPixelPositionHeight(percentageY)});
}

int Core::GetPixelPositionWidth(float percentage)
{
	return (int)(percentage * GetDisplayWidth());
}

int Core::GetPixelPositionHeight(float percentage)
{
	return (int)(percentage * GetDisplayHeight());
}

bool Core::Init()
{
	try
	{
		SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
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
	InitAppState(AppState::Game); // for testing

	return true;
}

void Core::Terminate()
{
	CloseWindow();
}

void Core::InitAppState(AppState newState)
{
	_currentState = newState;

	if (_gamePhase != nullptr)
	{
		_gamePhase->End();
		delete _gamePhase;
	}

	switch (_currentState)
	{
	case AppState::Menu:
		_gamePhase = new Menu();
		break;
	case AppState::Game:
		_gamePhase = new Game();
		break;
	default:
		return;
	}

	if (_gamePhase != nullptr)
	{
		_gamePhase->Start();
	}
}

void Core::ReinitAppState()
{
	if (_gamePhase == nullptr)
	{
		return;
	}

	_gamePhase->End();
	_gamePhase->Start();
}

void Core::CheckForPhaseChange()
{
	if (_gamePhase->IsEnded())
	{
		InitAppState(GetNextPhase());
	}
	else if (_gamePhase->IsReset())
	{
		ReinitAppState();
	}
}

void Core::CheckForSystemInputs()
{
	if (IsScreenModifierPressed())
	{
		SwitchFullScreen();
	}
}

AppState Core::GetNextPhase()
{
	if (_gamePhase == nullptr)
	{
		return AppState::Unset;
	}

	switch (_currentState)
	{
	case AppState::Menu:
		return AppState::Game;
	case AppState::Game:
		return AppState::Menu;
	default:
		return AppState::Unset;
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
