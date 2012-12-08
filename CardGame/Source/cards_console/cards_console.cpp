// cards_console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// initalizing here...
	int cardNumber = 4;			// number of card a battle will be played
	int lowestCard = 1;			// what could be lowest number on the cards
	int highestCard = 10;		// what could be highest number on the cards
	int startCardCount = 5;		// how many cards whould we start with
	int maximumDeckSize = 20;	// maximum size of deck
	int winDeckSize = 8;		// how many cards should we collect to win the game
	int loseDeckSize = 3;		// if we reach this amount of cards we lose

	// random seed
	srand((unsigned)time(NULL));
 
	// creation of the player deck
	std::cout << "Creating player deck...\n";
	Deck* player = new Deck(maximumDeckSize);
	int deckSize = player->GenerateDeck(lowestCard,highestCard,startCardCount,false,true);

	// creation of the computer deck
	std::cout << "Creating cpu deck...\n";
	Deck* cpu = new Deck(maximumDeckSize);
	cpu->GenerateDeck(lowestCard,highestCard,cardNumber,true,true);

	// preparing the AI
	CpuPlayer* ai = new CpuPlayer(player, cpu);

	// preparing the battlefield
	Battle* battle = new Battle(ai, player, cpu, cardNumber);
	
	// while not reaching the deck size for win or lose play battles
	while(player->DeckSize() > loseDeckSize && player->DeckSize() < winDeckSize)
	{
		battle->StartBattle();
	}

	// after reaching either size announce the winner
	if (player->DeckSize() <= loseDeckSize)
	{
		std::cout << "CPU saved the day, thanks for playing!\n";
	}
	else
	{
		std::cout << "You have won! You are awesome!\n";
	}

	system("pause");
	return 0;
}