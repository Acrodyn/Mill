#include "Menu.h"
#include "raylib.h"
#include "System/Core.h"
#include "Game/UI/Button.h"
#include "Game/UI/Label.h"
#include "Game/GameTransitionData.h"

Menu::Menu(TransitionData** transitionData) : GamePhase(transitionData)
{
	InitiateTransfer(GameType::ThreeManMorris);
	_fontSizeCurrent = _fontSizeStart;
}

Menu::~Menu()
{

}

void Menu::Loop()
{
	DrawRectangle(0, 0, Core::GetDisplayWidth(), Core::GetDisplayHeight(), DARKGRAY);
	AnimateTitle();
}

void Menu::InitUI()
{
	_titleLabel = new Label(0.48f, 0.3f, (int)_fontSizeStart, "MILLS");
	_titleLabel->SetColor(YELLOW);
	_UIObjects.push_back(_titleLabel);

	Button* threeMenGame = new Button(0.5f, 0.6f, 300, 80);
	threeMenGame->AttachLabel(new Label(20, "Three Men"));
	threeMenGame->RegisterOnRelease([&]() { InitiateTransfer(GameType::ThreeManMorris, false); });
	_UIObjects.push_back(threeMenGame);

	Button* nineMenGameWithFlying = new Button(0.5f, 0.75f, 300, 80);
	nineMenGameWithFlying->AttachLabel(new Label(20, "Nine Men With Flying"));
	nineMenGameWithFlying->RegisterOnRelease([&]() { InitiateTransfer(GameType::NineMenMorris, true); });
	_UIObjects.push_back(nineMenGameWithFlying);

	Button* nineMenGameWithoutFlying = new Button(0.5f, 0.9f, 300, 80);
	nineMenGameWithoutFlying->AttachLabel(new Label(20, "Nine Men Without Flying"));
	nineMenGameWithoutFlying->RegisterOnRelease([&]() { InitiateTransfer(GameType::NineMenMorris, false); });
	_UIObjects.push_back(nineMenGameWithoutFlying);
}

void Menu::InitiateTransfer(GameType gameType, bool hasFlying)
{
	if (*_transitionData != nullptr)
	{
		delete *_transitionData;
	}

	GameTransitionData* transferData = new GameTransitionData();
	transferData->GameType = gameType;
	transferData->HasFlight = hasFlying;
	(*_transitionData) = transferData;

	_phaseState = GamePhaseState::Ending;
}

void Menu::AnimateTitle()
{
	if (_isTitleGrowing)
	{
		_fontSizeCurrent += GetFrameTime() * _sizeChangeRate;

		if (_fontSizeCurrent >= _fontsizeEnd)
		{
			_isTitleGrowing = false;
		}
	}
	else
	{
		_fontSizeCurrent -= GetFrameTime() * _sizeChangeRate;

		if (_fontSizeCurrent <= _fontSizeStart)
		{
			_isTitleGrowing = true;
		}
	}

	_titleLabel->SetFontSize((int)_fontSizeCurrent);
}
