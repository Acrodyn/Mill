#include "Game.h"
#include "System/Core.h"
#include "Board.h"
#include "Boards/ThreeBoard.h"
#include "UI/Button.h"
#include "UI/Label.h"
#include "System/ScreenRelatedObject.h"

#include <iostream>

Game::Game()
{
	
}

Game::~Game()
{

}

void Game::Init()
{
	_board = new ThreeBoard();
	_board->Init();

	Button* resetButton = new Button(0.15f, 0.9f, 150, 50);
	resetButton->AttachLabel(new Label(20, "Reset"));
	resetButton->RegisterOnClick([&]() { Reset(); });
	_screenObjects.push_back(resetButton);

	Button* menuButton = new Button(0.85f, 0.9f, 150, 50);
	menuButton->AttachLabel(new Label(20, "Menu"));
	menuButton->RegisterOnClick([&]() { ReturnToMenu(); });
	_screenObjects.push_back(menuButton);
}

void Game::Clean()
{
	delete _board;

	for (ScreenRelatedObject* screenObject : _screenObjects)
	{
		delete screenObject;
	}

	_screenObjects.clear();
}

void Game::Loop()
{
	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), BLACK);
	_board->Update();

	for (ScreenRelatedObject* screenObject : _screenObjects)
	{
		screenObject->Update();
	}

	CheckForInput();
}

void Game::CheckForInput()
{
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		_board->CheckForNodeClick();
	}
}

void Game::Reset()
{
	_phaseState = GamePhaseState::Reseting;
}

void Game::ReturnToMenu()
{
	_phaseState = GamePhaseState::Ending;
}
