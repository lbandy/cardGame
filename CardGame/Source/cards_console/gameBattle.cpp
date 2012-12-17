#include "stdafx.h"


/*
	BATTLE CLASS FUNCTIONS
*/

void Game::Award()
{
	int winner = battle.GetWinner() == 3 ? CoinFlip() : battle.GetWinner();

	if (winner == 1)
	{
		int card = cpu.GetRandomCard();
		gfx.SelectCardToAward(cpu.Index(card));
		player.AddCard(cpu.CardPointerByDef(card),'p');
	}
	else
	{
		int card = player.GetRandomCard();
		gfx.SelectCardToAward(player.Index(card));
		player.RemoveCard(card);
	}
	roundState = 12;
}
void Game::ClearBattle()
{
	gfx.ResetCardPositions();
	roundState = 11;
}
void Game::NextMove()
{
	for (int i=0;i<player.Size();i++)
	{
		if (player.StateByDef(i) == 'a')
		{
			for (int j=0;j<cpu.Size();j++)
			{
				if (cpu.StateByDef(j) == 'a')
				{
					gfx.PutCardsAway(player.State(player.Index(i),'u'), cpu.State(cpu.Index(j),'u'), battle.GetRound(), battleCardCount);
				}
			}
		}
	}

	roundState = 8;

	if (battle.GetRound() == battleCardCount)
	{
		roundState = 9;
	}

}
void Game::PlayBattle()
{
	roundState = 6;
	gfx.PutBoostersAway(battle.GetRound());
	gfx.PlayBattle(player.Index(playerCard), cpu.Index(cpuCard), winner, battle.GetRound());
}
void Game::StartBattle()
{
	battle.ResetBattle();
	
	battle.ResetBoosters(boosterCount);
	gfx.ResetBoosters(boosterCount);
	gfx.StartBattle();
	
	roundState = 0;

	// displaying player deck
	int cardCount = 0;
	for (int i=0;i<player.Size();i++)
	{
		if (player.StateByDef(i) == 's')
		{
			player.Index(i,gfx.DisplayCard(player.CardPointerByDef(i)->Sprite(),1,cardCount,battleCardCount));
			cardCount++;
		}
		else
		{
			player.Index(i,0);
		}
	}

	cpu.Clear();

	// creating computer deck
	cpu.GenerateDeck(lowestCard,highestCard,battleCardCount,true);

	// displaying cpu deck
	for (int i=0;i<cpu.Size();i++)
	{
		cpu.CardPointerByDef(i)->Sprite((gfx.GetImage(cpu.CardPointerByDef(i)->GetPower())));
		cpu.State(i,'s');
		cpu.Index(i,gfx.DisplayCard(cpu.CardPointerByDef(i)->Sprite(),2,i,battleCardCount));
	}
}
void Game::SelectCardInBattle(int displayIndex, int owner)
{
	if (owner == 1 && roundState != 1)
	{
		if (player.StateByID(displayIndex) == 's')
		{
			player.State(displayIndex,'a');

			gfx.SelectCardToFight(displayIndex, battle.GetRound() + 1);

			roundState = (roundState == 2) ? 3 : 1;
		}
	}
	
	else if (owner == 2 && roundState != 2)
	{
		if (cpu.StateByID(displayIndex) == 's')
		{
			cpu.State(displayIndex,'a');

			gfx.SelectCardToFight(displayIndex, battle.GetRound() + 1);

			roundState = (roundState == 1) ? 3 : 2;
		}
	}
}
void Game::ShowBattle()
{
	gfx.CanInteract(false);
	roundState = 4;

	// search for the cards playing this round
	for (int i=0;i<player.Size();i++)
	{
		if (player.StateByDef(i) == 'a')
		{
			for (int j=0;j<cpu.Size();j++)
			{
				if (cpu.StateByDef(j) == 'a')
				{
					int playerBoost = gfx.PutBoostersAway(battle.GetRound() + 1);
					battle.PlayerBooster(playerBoost);

					int cpuBoost = ai.SelectDefense(player.CardPointerByDef(i)->GetPower(), cpu.CardPointerByDef(j)->GetPower(), battle.PlayerBooster(), battle.CpuBooster());

					battle.CpuBooster(cpuBoost);

					gfx.MoveCpuBoost(cpuBoost, cpu.Index(j));

					winner = battle.Fight(player.CardPointerByDef(i)->GetPower(), cpu.CardPointerByDef(j)->GetPower(), playerBoost, cpuBoost);

					if (winner == 3) winner = CoinFlip();
					
					battle.PlayerStartNextRound(winner == 1 ? true : false);

					playerCard = i;
					cpuCard = j;
				}
			}
		}
	}
}