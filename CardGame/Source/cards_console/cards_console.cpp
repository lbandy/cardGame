#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	// initalizing here...
	int cardNumber = GetPrivateProfileInt(L"INIT_SETTINGS", L"cardNumber", 4, L"./stats.ini");				// number of card a battle will be played
	int lowestCard = GetPrivateProfileInt(L"INIT_SETTINGS", L"lowestCard", 1, L"./stats.ini");;				// what could be lowest number on the cards
	int highestCard = GetPrivateProfileInt(L"INIT_SETTINGS", L"highestCard", 10, L"./stats.ini");;			// what could be highest number on the cards
	int startCardCount = GetPrivateProfileInt(L"INIT_SETTINGS", L"startCardCount", 5, L"./stats.ini");;		// how many cards whould we start with
	int maximumDeckSize = GetPrivateProfileInt(L"INIT_SETTINGS", L"maximumDeckSize", 20, L"./stats.ini");;	// maximum size of deck
	int boosters = GetPrivateProfileInt(L"INIT_SETTINGS", L"boosters", 5, L"./stats.ini");;					// how many boosters we get
	int winDeckSize = GetPrivateProfileInt(L"INIT_SETTINGS", L"winDeckSize", 8, L"./stats.ini");;			// how many cards should we collect to win the game
	int loseDeckSize = GetPrivateProfileInt(L"INIT_SETTINGS", L"loseDeckSize", 3, L"./stats.ini");;			// if we reach this amount of cards we lose
	
	// random seed
	srand((unsigned)time(NULL));
 
	// creation of the player deck
	std::cout << "Creating player deck...\n";
	Deck* player = new Deck(maximumDeckSize, boosters);
	int deckSize = player->GenerateDeck(lowestCard,highestCard,startCardCount,false,true);

	// creation of the computer deck
	std::cout << "Creating cpu deck...\n";
	Deck* cpu = new Deck(maximumDeckSize, boosters);
	cpu->GenerateDeck(lowestCard,highestCard,cardNumber,true,true);

	// preparing the AI
	CpuPlayer* ai = new CpuPlayer();

	// preparing the battlefield
	Battle* battle = new Battle(cardNumber);

	// while not reaching the deck size for win or lose play battles
	while(player->DeckSize() > loseDeckSize && player->DeckSize() < winDeckSize)
	{

		// select battle deck from pile
		player->ShowHand(cardNumber);

		// pause the game and clear the screen before next battle
		system("pause");
		system("cls");
	
		// reset battle attributes
		battle->ResetBattle();

		// start the battle
		battle->StartBattle(player, cpu, ai);

		// reset the player attributes
		player->Reset();

		// get a new deck to the computer
		cpu->Reset();
		cpu->Clear();
		cpu->GenerateDeck(lowestCard,highestCard,cardNumber,true,true);
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