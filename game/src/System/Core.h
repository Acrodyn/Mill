#pragma once

#include "SystemGlobals.h"
#include "raylib.h"

class GamePhase;
struct TransitionData;

class Core
{
public:
	Core();
	~Core();

	void Run();

	static bool IsScreenModifierPressed();
	static int GetDisplayWidth();
	static int GetDisplayHeight();
	static int GetPixelPositionWidth(float percentage);
	static int GetPixelPositionHeight(float percentage);
	static Vector2 GetScreenCenter();
	static Vector2 GetPixelPosition(float percentageX, float percentageY);
	static Vector2 GetPixelPosition(Vector2 percentage);
	static Vector2 GetScreenRelatedPosition(float positionX, float positionY);
	static Vector2 GetScreenRelatedPosition(Vector2 position);

private:
	bool Init();
	void Terminate();
	void InitAppState(AppState newState);
	void ReinitAppState();

	void CheckForPhaseChange();
	void CheckForSystemInputs();
	AppState GetNextPhase();

	void SetFullScreen();
	void ExitFullScreen();
	void SwitchFullScreen();

private:
	AppState _currentState = AppState::Unset;
	GamePhase* _gamePhase = nullptr;
	TransitionData* _transitionData = nullptr;

	static const int DEFAULT_SCREEN_WIDTH = 1280;
	static const int DEFAULT_SCREEN_HEIGHT = 800;
};