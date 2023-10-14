#include "Game.h"
#include "System/Core.h"
#include "Board.h"
#include "Boards/ThreeBoard.h"
#include "Boards/NineBoard.h"
#include "UI/Button.h"
#include "UI/Label.h"
#include "UI/RefreshedLabel.h"
#include "Player.h"
#include "System/ScreenRelatedObject.h"
#include "GameTransitionData.h"

Game::Game(TransitionData** transitionData) : GamePhase(transitionData)
{

}

Game::~Game()
{

}

void Game::Init()
{
	InitBoard();
}

void Game::Destroy()
{
	delete _board;
}

void Game::Loop()
{
	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), GRAYISH);
	_board->Update();
}

void Game::Reset()
{
	GamePhase::Reset();
	_board->Reset();
}

void Game::InitBoard()
{
	GameTransitionData* transitionData = static_cast<GameTransitionData*>(*_transitionData);

	if (transitionData == nullptr)
	{
		_board = new NineBoard();
		_board->SetupFlying(true);
	}
	else
	{
		switch (transitionData->GameType)
		{
		case GameType::ThreeManMorris:
			_board = new ThreeBoard();
			_board->SetupFlying(false);
			break;
		case GameType::NineMenMorris:
			_board = new NineBoard();
			_board->SetupFlying(transitionData->HasFlight);
			break;
		}
	}

	_board->Init();

	_board->GetPlayer(1)->SetColor(DARKGRAY);
	_board->GetPlayer(2)->SetColor(WHITE);
}

void Game::InitUI()
{
	Button* resetButton = new Button(0.08f, 0.95f, 150, 50);
	resetButton->AttachLabel(new Label(20, "Reset"));
	resetButton->RegisterOnRelease([&]() { ResetGame(); });
	_UIObjects.push_back(resetButton);

	Button* menuButton = new Button(0.92f, 0.95f, 150, 50);
	menuButton->AttachLabel(new Label(20, "Menu"));
	menuButton->RegisterOnRelease([&]() { ReturnToMenu(); });
	_UIObjects.push_back(menuButton);

	RefreshedLabel* firstRefreshLabel = new RefreshedLabel(0.1f, 0.5f, 50);
	firstRefreshLabel->SetColor(RED);
	firstRefreshLabel->RegisterRefreshFunction([&]() { return std::to_string(_board->GetPlayer(1)->GetRemainingPieces()); });
	_UIObjects.push_back(firstRefreshLabel);

	RefreshedLabel* secondRefreshLabel = new RefreshedLabel(0.9f, 0.5f, 50);
	secondRefreshLabel->SetColor(RED);
	secondRefreshLabel->RegisterRefreshFunction([&]() { return std::to_string(_board->GetPlayer(2)->GetRemainingPieces()); });
	_UIObjects.push_back(secondRefreshLabel);

	RefreshedLabel* firstActionLabel = new RefreshedLabel(0.1f, 0.70f, 25);
	firstActionLabel->SetColor(GREEN);
	firstActionLabel->RegisterRefreshFunction([&]() { return _board->GetPhaseDescriptionForPlayer(1); });
	_UIObjects.push_back(firstActionLabel);

	RefreshedLabel* secondActionLabel = new RefreshedLabel(0.9f, 0.7f, 25);
	secondActionLabel->SetColor(GREEN);
	secondActionLabel->RegisterRefreshFunction([&]() { return _board->GetPhaseDescriptionForPlayer(2); });
	_UIObjects.push_back(secondActionLabel);
}

void Game::ResetGame()
{
	_phaseState = GamePhaseState::Reseting;
}

void Game::ReturnToMenu()
{
	_phaseState = GamePhaseState::Ending;
}
