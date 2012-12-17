#include "headers.h"

/*
	GETCARD CLASS FUNCTIONS
*/


// returns the strongest card in the deck
int Deck::GetStrongestCard()
{
	int strongest = 0;
	int strongestIndex;
	for (int i=0;i<(int)cardState.size();i++)
	{
		// if not available to play skip
		if (cardState.at(i) != 's') continue;

		// if stronger, set it to strongest
		if (pile.at(i)->GetPower() > strongest)
		{
			strongest = pile.at(i)->GetPower();

			// store the correct index
			strongestIndex = i;
		}
	}

	// return the card
	return displayIndex.at(strongestIndex);
}

// returns the weakest card in deck
int Deck::GetWeakestCard()
{
	int weakest = 9999;
	int weakestIndex;
	for (int i=0;i<(int)cardState.size();i++)
	{
		if (cardState.at(i) != 's') continue;

		if (pile.at(i)->GetPower() < weakest)
		{
			weakest = pile.at(i)->GetPower();
			weakestIndex = i;
		}
	}
	return displayIndex.at(weakestIndex);
}

// returns the index of a random card from the deck we used in battle
int Deck::GetRandomCard()
{
	std::vector<int> buffer;

	for (int i=0;i<(int)cardState.size();i++)
	{
		// skip the cards were not in battle
		if (cardState.at(i) == 'p') continue;

		buffer.push_back(i);
	}

	return buffer[rand() % (int)buffer.size()];
}