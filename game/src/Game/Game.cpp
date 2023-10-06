#include "Game.h"
#include "System/Core.h"
#include "Board.h"
#include "ThreeBoard.h"

Game::Game()
{
	_board = new ThreeBoard();
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
}
