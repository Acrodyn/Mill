#pragma once

#include "System/SystemGlobals.h"

class GamePhase
{
public:
	GamePhase();
	virtual ~GamePhase();

	void Start();
	void End();
	void Update();
	bool IsEnded();
	bool IsReset();

protected:
	virtual void Init();
	virtual void Clean();
	virtual void Loop() = 0;

private:
	void TransitionTo();
	void TransitionFrom();
	void UpdateTransitions();
	GamePhaseState GetLeadingState();

protected:
	GamePhaseState _phaseState = GamePhaseState::Unset;
	float _transitionAlpha = 0.f;
	float _transitionToSpeed = 1.f;
	float _transitionFromSpeed = 2.f;
};