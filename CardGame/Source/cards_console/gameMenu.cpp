#include "stdafx.h"

/*
	MENU CLASS FUNCTIONS
*/

void Game::EndGame()
{
	if(player.Size() < loseCardCount)
	{

	}
	else if(player.Size() > winCardCount)
	{

	}
	
	// gfx-> display who have won and offers restarting opportunity
}
void Game::HowToPlay()
{
	// show pre-defined video how to play
}
void Game::StartGame()
{
	gfx.PrepareBoosters(boosterCount);
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
	EndGame();

	player.Reset();
	gfx.ClearDisplaybuffer();
	gfx.CanInteract(true);

	cardsInBattleDeck = 0;
	inBattle = false;

	for (int i=0;i<player.Size();i++)
	{
		player.Index(i,gfx.DisplayCard(player.CardPointerByDef(i)->Sprite(),1,i,player.Size()));
	}
}



