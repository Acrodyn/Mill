#include "GamePhase.h"
#include "raylib.h"
#include "ScreenRelatedObject.h"
#include "System/Core.h"

GamePhase::GamePhase(TransitionData** transitionData) : _transitionData(transitionData)
{

}

GamePhase::~GamePhase()
{
	for (ScreenRelatedObject* screenObject : _UIObjects)
	{
		delete screenObject;
	}

	_UIObjects.clear();
}

void GamePhase::Start()
{
	_phaseState = GamePhaseState::Starting;
	_transitionAlpha = 1.f;
	Init();
	InitUI();
}

void GamePhase::End()
{
	Destroy();
}

void GamePhase::Update()
{
	if (_phaseState == GamePhaseState::Ended)
	{
		return;
	}

	Loop();
	DrawUI();
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

void GamePhase::InitUI()
{

}

void GamePhase::Destroy()
{

}

void GamePhase::Reset()
{
	_phaseState = GamePhaseState::Starting;
	_transitionAlpha = 1.f;
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

void GamePhase::DrawUI()
{
	for (ScreenRelatedObject* screenObject : _UIObjects)
	{
		screenObject->Update();
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