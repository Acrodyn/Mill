#pragma once

#include "SystemGlobals.h"
#include "raylib.h"

class GamePhase;

class Core
{
public:
	Core();
	void Run();

	static bool IsInteractPressed();
	static bool IsInteractDown();
	static bool IsScreenModifierPressed();
	static Vector2 GetScreenCenter();
	static int GetDisplayWidth();
	static int GetDisplayHeight();
	static Vector2 GetPixelPosition(float percentageX, float percentageY);
	static int GetPixelPositionWidth(float percentage);
	static int GetPixelPositionHeight(float percentage);

private:
	bool Init();
	void Terminate();
	void InitAppState(AppPhase newState);

	void CheckForPhaseChange();
	void CheckForSystemInputs();
	AppPhase GetNextPhase();

	void SetFullScreen();
	void ExitFullScreen();
	void SwitchFullScreen();

private:
	AppPhase _currentState = AppPhase::Unset;
	GamePhase* _gamePhase = nullptr;

	int defaultScreenWidth = 1280;
	int defaultScreenHeight = 800;
};