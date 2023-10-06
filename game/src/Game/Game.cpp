#include "Game.h"
#include "System/Core.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::InitPhase()
{

}

void Game::DestroyPhase()
{

}

void Game::LoopPhase()
{
	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), BLACK);
}
