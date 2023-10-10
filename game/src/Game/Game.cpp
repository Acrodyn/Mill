#include "Game.h"
#include "System/Core.h"
#include "Board.h"
#include "Boards/ThreeBoard.h"
#include "UI/Button.h"
#include "UI/Label.h"
#include "UI/RefreshedLabel.h"
#include "Player.h"
#include "System/ScreenRelatedObject.h"

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

	InitUI();
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

void Game::InitUI()
{
	Button* resetButton = new Button(0.08f, 0.95f, 150, 50);
	resetButton->AttachLabel(new Label(20, "Reset"));
	resetButton->RegisterOnRelease([&]() { Reset(); });
	_screenObjects.push_back(resetButton);

	Button* menuButton = new Button(0.92f, 0.95f, 150, 50);
	menuButton->AttachLabel(new Label(20, "Menu"));
	menuButton->RegisterOnRelease([&]() { ReturnToMenu(); });
	_screenObjects.push_back(menuButton);

	RefreshedLabel* firstRefreshLabel = new RefreshedLabel(0.15f, 0.5f);
	firstRefreshLabel->SetColor(RED);
	firstRefreshLabel->RegisterRefreshFunction([&]() { return std::to_string(_board->GetPlayer(1)->GetRemainingPieces()); });
	_screenObjects.push_back(firstRefreshLabel);

	RefreshedLabel* secondRefreshLabel = new RefreshedLabel(0.85f, 0.5f);
	secondRefreshLabel->SetColor(RED);
	secondRefreshLabel->RegisterRefreshFunction([&]() { return std::to_string(_board->GetPlayer(2)->GetRemainingPieces()); });
	_screenObjects.push_back(secondRefreshLabel);
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
