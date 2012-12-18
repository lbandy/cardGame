#include "headers.h"

int Game::CoinFlip()
{
	int winner = rand() % 2 + 1;
	roundState++;

	return winner;
}

void Game::Ready()
{
	if (resized)
	{
		gfx.ResizeWindow();
		resized = false;
		return;
	}

	if (inBattle)
	{
		if (battle.GetRound() == -1)
		{
			gfx.ClearDisplaybuffer();
			StartBattle();
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
				if (howToPlay)
				{
					for (int i = 0; i < player.Size(); i++)
					{
						if (player.StateByDef(i) == 'a')
						{
							for (int j = 0; j < cpu.Size(); j++)
							{
								if (cpu.StateByDef(j) == 'a')
								{
									int playerBoost = ai.SelectDefense(cpu.CardPointerByDef(j)->GetPower(), player.CardPointerByDef(i)->GetPower(), battle.CpuBooster(), battle.PlayerBooster());
									battle.PlayerBooster(playerBoost);

									gfx.MoveCpuBoost(playerBoost, player.Index(i), 1);
								}
							}
						}
					}

					ShowBattle();
					break;
				}
				gfx.CanInteract(true);
				break;
			case 4:
				PlayBattle();
				break;
			case 5:
				gfx.FlipCoin(winner == 1 ? true : false);
				roundState = 4;
				break;
			case 6:
				WaitForSecond(1);
				break;
			case 7:
				NextMove();
				break;
			case 8:
				gfx.EndOfRound();

				if (howToPlay)
				{
					WaitForSecond(2);
					roundState = 0;
					break;
				}

				if (!battle.NextStart())
				{
					WaitForSecond(2);

					SelectCardInBattle(ai.SelectTarget(&player), 1);
					SelectCardInBattle(ai.SelectAttack(&cpu), 2);

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
				WaitForSecond(1);
				break;
			case 10:
				ClearBattle();
				break;
			case 11:
				EndBattle();
				break;
			case 12:
				Award();
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
				howToPlay ? gfx.InMenu() : ShowCards();
				howToPlay = false;
				gfx.CanInteract(true);
				break;
			default:
				if (howToPlay)
				{
					gfx.CanInteract(false);

					SelectCardInBattle(ai.SelectTarget(&player), 1);
					SelectCardInBattle(ai.SelectAttack(&cpu), 2);

					break;
				}
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

void Game::Resize()
{
	resized = true;
}

Game::Game()
{
	// initalising here...
	battleCardCount		= GetPrivateProfileInt(L"INIT_SETTINGS", L"cardNumber", 4, L"./stats.ini");				// number of card a battle will be played
	startCardCount		= GetPrivateProfileInt(L"INIT_SETTINGS", L"startCardCount", 5, L"./stats.ini");			// how many cards would we start with
	boosterCount		= GetPrivateProfileInt(L"INIT_SETTINGS", L"boosters", 5, L"./stats.ini");				// how many boosters we get
	winCardCount		= GetPrivateProfileInt(L"INIT_SETTINGS", L"winDeckSize", 8, L"./stats.ini");			// how many cards should we collect to win the game
	loseCardCount		= GetPrivateProfileInt(L"INIT_SETTINGS", L"loseDeckSize", 3, L"./stats.ini");			// if we reach this amount of cards we lose
	//lowestCard		= GetPrivateProfileInt(L"INIT_SETTINGS", L"lowestCard", 1, L"./stats.ini");				// what could be lowest number on the cards
	//highestCard		= GetPrivateProfileInt(L"INIT_SETTINGS", L"highestCard", 10, L"./stats.ini");			// what could be highest number on the cards
	
	lowestCard			= 1;
	highestCard			= 10;
	winCount			= 0;
	loseCount			= 0;
	
	howToPlay			= false;
	resized				= false;

	// random seed
	srand((unsigned)time(NULL));

	gfx.PrepareBoosters(boosterCount);
	gfx.InMenu();

	gfx.Start(1024,768,this);
}

Game::~Game()
{

}