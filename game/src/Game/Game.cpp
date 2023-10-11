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
	InitBoard();
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
	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), GRAYISH);
	_board->Update();

	for (ScreenRelatedObject* screenObject : _screenObjects)
	{
		screenObject->Update();
	}

	CheckForInput();
}

void Game::InitBoard()
{
	_board = new ThreeBoard();
	_board->Init();

	_board->GetPlayer(1)->SetColor(RED);
	_board->GetPlayer(2)->SetColor(WHITE);
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

	RefreshedLabel* firstRefreshLabel = new RefreshedLabel(0.15f, 0.5f, 50);
	firstRefreshLabel->SetColor(RED);
	firstRefreshLabel->RegisterRefreshFunction([&]() { return std::to_string(_board->GetPlayer(1)->GetRemainingPieces()); });
	_screenObjects.push_back(firstRefreshLabel);

	RefreshedLabel* secondRefreshLabel = new RefreshedLabel(0.85f, 0.5f, 50);
	secondRefreshLabel->SetColor(RED);
	secondRefreshLabel->RegisterRefreshFunction([&]() { return std::to_string(_board->GetPlayer(2)->GetRemainingPieces()); });
	_screenObjects.push_back(secondRefreshLabel);

	RefreshedLabel* firstActionLabel = new RefreshedLabel(0.15f, 0.70f, 25);
	firstActionLabel->SetColor(GREEN);
	firstActionLabel->RegisterRefreshFunction([&]() { return _board->GetPhaseDescriptionForPlayer(1); });
	_screenObjects.push_back(firstActionLabel);

	RefreshedLabel* secondActionLabel = new RefreshedLabel(0.85f, 0.7f, 25);
	secondActionLabel->SetColor(GREEN);
	secondActionLabel->RegisterRefreshFunction([&]() { return _board->GetPhaseDescriptionForPlayer(2); });
	_screenObjects.push_back(secondActionLabel);
}

void Game::CheckForInput()
{
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
	{
		_board->CheckForNodeInteraction();
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
