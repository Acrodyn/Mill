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

protected:
	virtual void InitPhase();
	virtual void DestroyPhase();
	virtual void LoopPhase() = 0;

private:
	void TransitionTo();
	void TransitionFrom();
	void CheckForTransitions();

protected:
	GamePhaseState _phaseState = GamePhaseState::Unset;
	float _transitionAlpha = 0.f;
	float _transitionToSpeed = 1.f;
	float _transitionFromSpeed = 2.f;
};