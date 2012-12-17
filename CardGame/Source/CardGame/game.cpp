#include "headers.h"

int Game::CoinFlip()
{
	int winner = rand() % 2 + 1;
//	gfx->CoinFlip(winner); // display an animation of flipping the coin. when finished, triggers next event
	roundState++;

	return winner;
}

void Game::Ready()
{
	if (inBattle)
	{
		if (battle.GetRound() == -1)
		{
			gfx.ClearDisplaybuffer();
			Game::StartBattle();
			gfx.CanInteract(true);
		}
		else if (battle.GetRound() == battleCardCount + 1)
		{
			gfx.CanInteract(false);
		}
		else
		{
			switch(roundState)
			{
			case 3:
				gfx.CanInteract(true);
				break;
			case 4:
				Game::PlayBattle();
				break;
			case 5:
				gfx.FlipCoin(winner == 1 ? true : false);
				roundState = 4;
				break;
			case 6:
				Game::WaitForSecond(1);
				break;
			case 7:
				Game::NextMove();
				break;
			case 8:
				gfx.EndOfRound();

				if (!battle.NextStart())
				{
					Game::SelectCardInBattle(ai.SelectTarget(&player), 1);
					Game::SelectCardInBattle(ai.SelectAttack(&cpu), 2);

					gfx.CanInteract(true);
					roundState = 0;
				}
				else
				{
					roundState = 0;
					gfx.CanInteract(true);
				}
			break;
			case 9:
				Game::WaitForSecond(1);
				break;
			case 10:
				Game::ClearBattle();
				break;
			case 11:
				Game::EndBattle();
				break;
			case 12:
				Game::Award();
				break;
			case 13:
				gfx.FlipCoin(winner == 1 ? true : false);
				roundState = 12;
				break;
			case 14:
				gfx.ClearTable();
				roundState++;
				break;
			case 15:
				Game::ShowCards();
				break;
			default:
				gfx.CanInteract(true);
				break;
			}
		}
	}
	else if (cardsInBattleDeck == battleCardCount)
	{
		battle.PrepareBattle();
		inBattle = true;
		gfx.ClearTable();
		gfx.CanInteract(false);
	}
	else
	{
		gfx.CanInteract(true);
	}
}

void Game::WaitForSecond(int second)
{
	gfx.WaitForSecond(second);
	roundState++;
}

Game::Game()
{
	// initalizing here...
	battleCardCount = GetPrivateProfileInt(L"INIT_SETTINGS", L"cardNumber", 4, L"./stats.ini");				// number of card a battle will be played
	startCardCount = GetPrivateProfileInt(L"INIT_SETTINGS", L"startCardCount", 5, L"./stats.ini");		// how many cards would we start with
	boosterCount = GetPrivateProfileInt(L"INIT_SETTINGS", L"boosters", 5, L"./stats.ini");					// how many boosters we get
	winCardCount = GetPrivateProfileInt(L"INIT_SETTINGS", L"winDeckSize", 8, L"./stats.ini");			// how many cards should we collect to win the game
	loseCardCount = GetPrivateProfileInt(L"INIT_SETTINGS", L"loseDeckSize", 3, L"./stats.ini");			// if we reach this amount of cards we lose
	lowestCard = GetPrivateProfileInt(L"INIT_SETTINGS", L"lowestCard", 1, L"./stats.ini");			// what could be lowest number on the cards
	highestCard = GetPrivateProfileInt(L"INIT_SETTINGS", L"highestCard", 10, L"./stats.ini");			// what could be highest number on the cards
	winCount = 0;
	loseCount = 0;

	// random seed
	srand((unsigned)time(NULL));

	gfx.PrepareBoosters(boosterCount);
	gfx.InMenu();

	gfx.Start(1024,768,this);
}

Game::~Game()
{

}