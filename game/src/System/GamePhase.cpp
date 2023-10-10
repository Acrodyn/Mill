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
	Init();
}

void GamePhase::End()
{
	Clean();
}

void GamePhase::Update()
{
	if (_phaseState == GamePhaseState::Ended)
	{
		return;
	}

	Loop();
	UpdateTransitions();
}

bool GamePhase::IsEnded()
{
	return _phaseState == GamePhaseState::Ended;
}

bool GamePhase::IsReset()
{
	return _phaseState == GamePhaseState::Reset;
} 

void GamePhase::Init()
{

}

void GamePhase::Clean()
{

}

void GamePhase::TransitionTo()
{
	if (_transitionAlpha <= 0.f)
	{
		_phaseState = GetLeadingState();
		_transitionAlpha = 0.f;
		return;
	}

	_transitionAlpha -= _transitionToSpeed * GetFrameTime();
}

void GamePhase::TransitionFrom()
{
	if (_transitionAlpha >= 1.f)
	{
		_phaseState = GetLeadingState();
		_transitionAlpha = 1.f;
		return;
	}

	_transitionAlpha += _transitionFromSpeed * GetFrameTime();
}

void GamePhase::UpdateTransitions()
{
	if (_phaseState != GamePhaseState::Running)
	{
		switch (_phaseState)
		{
		case GamePhaseState::Starting:
			TransitionTo();
			break;
		case GamePhaseState::Ending:
		case GamePhaseState::Reseting:
			TransitionFrom();
			break;
		default:
			break;
		}
	}

	if (_transitionAlpha > 0.f)
	{
		DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), Fade(BLACK, _transitionAlpha));
	}
}

GamePhaseState GamePhase::GetLeadingState()
{
	switch (_phaseState)
	{
	case GamePhaseState::Starting:
		return GamePhaseState::Running;
	case GamePhaseState::Ending:
		return GamePhaseState::Ended;
	case GamePhaseState::Reseting:
		return GamePhaseState::Reset;
	default:
		return GamePhaseState::Unset;
	}
}
