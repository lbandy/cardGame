#include "headers.h"

/*
	MENU CLASS FUNCTIONS
*/

bool Game::EndGame()
{
	if(player.Size() <= loseCardCount)
	{
		gfx.InEnd(false);
		return true;
	}
	else if(player.Size() >= winCardCount)
	{
		gfx.InEnd(true);
		return true;
	}
	
	return false;
	// gfx-> display who have won and offers restarting opportunity
}

void Game::HowToPlay()
{
	// show pre-defined video how to play
}

void Game::StartGame()
{
	// creation of the player deck
	player.Clear();
	player.GenerateDeck(lowestCard,highestCard,startCardCount,false);

	for (int i=0;i<player.Size();i++)
	{
		player.CardPointerByDef(i)->Sprite((gfx.GetImage(player.CardPointerByDef(i)->GetPower())));
	}
	Game::ShowCards();
}

void Game::SelectCardInHand(int displayIndex)
{
	if (cardsInBattleDeck == battleCardCount) return;

	if (player.StateByID(displayIndex) == 'p')
	{
		player.State(displayIndex,'s');

		gfx.SelectCardToBattleDeck(displayIndex, cardsInBattleDeck, battleCardCount);

		cardsInBattleDeck++;
	}
}

void Game::ShowCards()
{
	if (EndGame()) return;

	player.Reset();
	gfx.InHand();
	gfx.ClearDisplaybuffer();
	gfx.CanInteract(true);

	cardsInBattleDeck = 0;
	inBattle = false;

	for (int i = 0; i < player.Size(); i++)
	{
		player.Index(i, gfx.DisplayCard(player.CardPointerByDef(i)->Sprite(), 1, i, player.Size()));
	}
}