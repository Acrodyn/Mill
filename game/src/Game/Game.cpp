#include "Game.h"
#include "System/Core.h"
#include "Board.h"
#include "Boards/ThreeBoard.h"
#include "UI/Button.h"
#include "UI/Label.h"
#include "System/ScreenRelatedObject.h"

Game::Game()
{
	_board = new ThreeBoard();
}

Game::~Game()
{
	delete _board;

	for (ScreenRelatedObject* screenObject : _screenObjects)
	{
		delete screenObject;
	}
}

void Game::InitPhase()
{
	_board->Init();

	Button* resetButton = new Button(0.15f, 0.15f, 200, 100);
	resetButton->AttachLabel(new Label(20, "Test"));
	_screenObjects.push_back(resetButton);
}

void Game::DestroyPhase()
{

}

void Game::LoopPhase()
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
