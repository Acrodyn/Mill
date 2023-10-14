#pragma once

#include "System/SystemGlobals.h"
#include <vector>

struct TransitionData;
class ScreenRelatedObject;

class GamePhase
{
public:
	GamePhase() = delete;
	GamePhase(TransitionData** transitionData = nullptr);
	virtual ~GamePhase();

	virtual void Reset();

	void Start();
	void End();
	void Update();
	bool IsEnded();
	bool IsReset();

protected:
	virtual void Init();
	virtual void InitUI();
	virtual void Destroy();
	virtual void Loop() = 0;

private:
	void TransitionTo();
	void TransitionFrom();
	void UpdateTransitions();
	void DrawUI();
	GamePhaseState GetLeadingState();

protected:
	GamePhaseState _phaseState = GamePhaseState::Unset;
	TransitionData** _transitionData = nullptr;
	float _transitionAlpha = 0.f;
	float _transitionToSpeed = 1.f;
	float _transitionFromSpeed = 2.f;

	std::vector<ScreenRelatedObject*> _UIObjects;
};