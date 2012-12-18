#include "headers.h"


/*
	MANAGE CLASS FUNCTIONS
*/



// adds a card to our deck
void Deck::AddCard(Card* card, char state)
{
	pile.push_back(card);
	cardState.push_back(state);
	displayIndex.push_back((int)displayIndex.size());
}

// removes a card from our deck
void Deck::RemoveCard(int index)
{
	pile.erase(pile.begin() + index);
	cardState.erase(cardState.begin() + index);
	displayIndex.erase(displayIndex.begin() + index);
}

// generates the deck
void Deck::GenerateDeck(int lowest, int highest, int count, bool repeat)
{
	// if error, warn the user not to mess with the numbers
	if ((lowest > highest) || (count > highest - lowest + 1))
	{
		std::cout << "The given range or count is not valid!\n";
		return;
	}

	// if cards with the same number are allowed in the deck
	if (repeat)
	{
		for (int i = 0; i < count; i++)
		{
			// create a card randomly between the lowest and highest possibilities
			Card* card = new Card(rand() % (highest - lowest + 1) + lowest);	

			// add card to deck
			this->Deck::AddCard(card,'s');
		}
	}
	else
	{
		// set the size of the array
		int current = highest - lowest;

		// create a temporary buffer for all numbers
		std::vector<int> buffer;

		for (int i = 0; i <= current; i++)
		{
			buffer.push_back(lowest + i);
		}

		for (int i = 0; i < count; i++)
		{
			// pick up a random number from the remaining items
			int selected = i < count - 1 ? rand() % current : 0;

			// create the card
			Card* card = new Card(buffer.at(selected));	
			this->Deck::AddCard(card,'p');

			// put the number out of options
			buffer.erase(buffer.begin() + selected);

			current--;
		}

	}
}

// reset the deck to battle again
void Deck::Reset()
{
	for (int i = 0; i < (int)cardState.size(); i++)
	{
		// put back every card to pile
		cardState.at(i) = 'p';
	}
}

// clear the deck completely
void Deck::Clear()
{
	pile.clear();
	cardState.clear();
	displayIndex.clear();
}


