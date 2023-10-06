#include "GamePhase.h"
#include "raylib.h"
#include "System/Core.h"

GamePhase::GamePhase()
{

}

GamePhase::~GamePhase()
{

}

void GamePhase::Start()
{
	_phaseState = GamePhaseState::Starting;
	_transitionAlpha = 1.f;
	InitPhase();
}

void GamePhase::End()
{
	DestroyPhase();
}

void GamePhase::Update()
{
	if (_phaseState == GamePhaseState::Ended)
	{
		return;
	}

	LoopPhase();
	CheckForTransitions();
}

bool GamePhase::IsEnded()
{
	return _phaseState == GamePhaseState::Ended;
}

void GamePhase::InitPhase()
{

}

void GamePhase::DestroyPhase()
{

}

void GamePhase::TransitionTo()
{
	if (_transitionAlpha < 0.f)
	{
		_phaseState = GamePhaseState::Running;
		return;
	}

	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), Fade(BLACK, _transitionAlpha));
	_transitionAlpha -= _transitionToSpeed * GetFrameTime();
}

void GamePhase::TransitionFrom()
{
	if (_transitionAlpha > 1.f)
	{
		_phaseState = GamePhaseState::Ended;
		return;
	}

	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), Fade(BLACK, _transitionAlpha));
	_transitionAlpha += _transitionFromSpeed * GetFrameTime();
}

void GamePhase::CheckForTransitions()
{
	if (_phaseState != GamePhaseState::Running)
	{
		switch (_phaseState)
		{
		case GamePhaseState::Starting:
			TransitionTo();
			break;
		case GamePhaseState::Ending:
			TransitionFrom();
			break;
		default:
			break;
		}
	}
}