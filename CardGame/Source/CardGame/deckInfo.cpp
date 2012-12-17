#include "headers.h"


/*
	INFO CLASS FUNCTIONS
*/

// returns size of the deck
int Deck::Size()
{
	return cardState.size();
}

// returns state of the card at the given index
char Deck::StateByDef(int index)
{
	return cardState.at(index);
}

// returns state of the card at the given display index
char Deck::StateByID(int index)
{
	for (int i=0;i<(int)cardState.size();i++)
	{
		if (displayIndex.at(i) == index) return cardState.at(i);
	}

	return -1;
}

// sets the state of the card at the given index
int Deck::State(int index, char state) 
{
	for (int i=0;i<(int)cardState.size();i++)
	{
		if (displayIndex.at(i) == index) cardState.at(i) = state;
	}

	return index;
}

// sets displayIndex at the given index
void Deck::Index(int index, int displayID)
{
	displayIndex.at(index) = displayID;
}

// returns displayIndex
int Deck::Index(int index)
{
	return displayIndex.at(index);
}

// returns the Card pointer display by the given index
Card* Deck::CardPointerByDef(int index)
{
	return pile.at(index);
}

// returns the Card pointer display by the given displayIndex
Card* Deck::CardPointerByID(int index)
{
	for (int i=0;i<(int)cardState.size();i++)
	{
		if (displayIndex.at(i) == index) return pile.at(i);
	}
}

