#include "Game.h"
#include "System/Core.h"
#include "Board.h"
#include "Boards/ThreeBoard.h"
#include "UI/Button.h"
#include "UI/Label.h"

Game::Game()
{
	_board = new ThreeBoard();

	_button = new Button(0.15f, 0.15f, 200, 100);
	_button->SetColor(YELLOW);
	_button->AttachLabel(new Label(20, "Test"));
}

Game::~Game()
{
	delete _board;
}

void Game::InitPhase()
{
	_board->Init();
}

void Game::DestroyPhase()
{

}

void Game::LoopPhase()
{
	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), BLACK);
	_board->Update();

	_button->Update();
	CheckForInput();
}

void Game::CheckForInput()
{
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		_board->CheckForNodeClick();
	}
}
