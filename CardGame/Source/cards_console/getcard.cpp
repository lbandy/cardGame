#include "stdafx.h"


// returns the average of cards
float GetCard::GetAverage()
{
	return average;
}

// returns the strongest card in the deck
Card* GetCard::SelectStrongest()
{
	int strongest = 0;
	int strongestIndex;
	for (int i=0;i<currentCard;i++)
	{
		// if not available to play skip
		if ((pile[i]).GetState(true) != 's') continue;

		// if stronger, set it to strongest
		if ((pile[i]).GetPower() > strongest)
		{
			strongest = (pile[i]).GetPower();

			// store the correct index
			strongestIndex = i;
		}
	}

	// return the card
	return &pile[strongestIndex];
}

// returns the weakest card in deck
Card* GetCard::SelectWeakest()
{
	int weakest = 9999;
	int weakestIndex;
	for (int i=0;i<currentCard;i++)
	{
		if ((pile[i]).GetState(true) != 's') continue;

		if ((pile[i]).GetPower() < weakest)
		{
			weakest = (pile[i]).GetPower();
			weakestIndex = i;
		}
	}
	return &pile[weakestIndex];
}

// returns a random card from the deck we used in battle
Card* GetCard::GetRandomCard(int size)
{
	int* buffer = new int[size];
	int counter = 0;

	for (int i=0;i<currentCard;i++)
	{
		// skip the cards were not in battle
		if ((pile[i]).GetState(true) == 'p') continue;

		buffer[counter] = i;
		counter++;
	}

	counter = buffer[rand() % counter];
	delete[] buffer;

	return	&pile[counter];
}

GetCard::GetCard()
{

}

GetCard::~GetCard()
{

}