#include "deck.h"
#include "stdafx.h"

// adds a card to our deck
int Deck::AddCard(Card card, bool silent)
{
	pile[currentCard] = card;

	// increases the actual deck size
	currentCard++;
	
	if(!silent)
	{
		std::cout << "Card added with power " << card.GetPower() << "\n";
	}

	// returns the deck size
	return currentCard;
}

// removes a card from our deck
void Deck::RemoveCard(Card card, bool silent)
{
	for (int i=0;i<currentCard;i++)
	{
		// search for the card to remove
		if (pile[i].GetPower() == card.GetPower())
		{
			if (!silent) std::cout << "Card with power " << pile[i].GetPower() << " has been removed from player deck.\n";

			// delete the card and decrease the deck size
			pile[i] = pile[currentCard-1];
			currentCard--;
		}
	}
}

// returns the deck as an array, currently not in use
Card* Deck::GetCards()
{
	return pile;
}

// generates the deck
int Deck::GenerateDeck(int lowest, int highest, int count, bool repeat, bool silent)
{
	// if error, warn the user not to mess with the numbers
	if ((lowest > highest) || (count > highest - lowest + 1))
	{
		std::cout << "The given range or count is not valid!\n";
		return 0;
	}

	// if cards with the same number are allowed in the deck
	if (repeat)
	{
		for (int i=0;i<count;i++)
		{
			// create a card randomly between the lowest and highest possibilities
			Card* card = new Card(rand() % (highest - lowest + 1) + lowest);	

			// if cpu, set all cards ready to battle
			if (silent)
			{
				card->SetState('s', true);
			}

			// add card to deck
			this->AddCard(*card, silent);
		}
	}
	else
	{
		// set the size of the array
		int current = highest - lowest;

		// create a temporary buffer for all numbers
		int* buffer = new int[current + 1];
		for (int i=0;i<=current;i++)
		{
			buffer[i] = lowest + i;
		}

		for (int i=0;i<count;i++)
		{
			// pick up a random number from the remaining items
			int selected = i < count - 1 ? rand() % current : 0;

			// create the card
			Card* card = new Card(buffer[selected]);	
			this->AddCard(*card, silent);

			// put the number out of options
			buffer[selected] = buffer[current];
			current--;
		}

		// free the allocated memory
		delete[] buffer;
	}
	return count;
}

// let the user choose cards to use in the next battle
void Deck::ShowHand(int maxCards)
{
	std::cout << "Select the cards you want to use in the next battle:\n";

	// show the whole deck
	for (int i=0;i<currentCard;i++)
	{
		std::cout << (i+1) << ". card, power is " << (pile[i]).GetPower() << "\n";
	}

	std::cout << "Enter the line number of the desired cards!\n";

	// repeat until hand is full
	for (int i=0;i<maxCards;i++)
	{
		int selected;
		std::cin >> selected;

		while (selected>currentCard)
		{
			std::cout << "Enter a valid line number!\n";
			std::cin >> selected;
		}

		// set the card state 'selected'
		(pile[selected - 1]).SetState('s', false);

		// calculates the average of selected cards
		average += pile[selected - 1].GetPower();
	}

	average /= (float)maxCards;
}

// select cards in battle
Card* Deck::BattleHand(int maxCards)
{
	int counter = 0;
	int* buffer = new int[maxCards];

	for (int i=0;i<currentCard;i++)
	{
		// if card is used or in pile don't show it
		if ((pile[i]).GetState(true) != 's') continue;

		buffer[counter] = i;
		counter++;

		// list the available cards
		std::cout << counter << ". card: " << (pile[i]).GetPower() << " [";
		(pile[i]).GetState(false);
		std::cout << "]\n";
	}

	int selected;
	std::cin >> selected;

	while (selected>counter)
	{
		std::cout << "Enter a valid line number!\n";
		std::cin >> selected;
	}

	// get the correct index of the card
	counter = buffer[selected - 1];

	// free memory
	delete[] buffer;

	// set the card 'active'
	pile[counter].SetState('a',true);

	// return the card
	return &pile[counter];
}

// change the amount of boosters available and returns the value
int Deck::Booster(int change)
{
	boosters -= change;
	return boosters;
}

// returns the average of cards
float Deck::GetAverage()
{
	return average;
}

// returns the strongest card in the deck
Card* Deck::SelectStrongest()
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
Card* Deck::SelectWeakest()
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
Card* Deck::GetRandomCard(int size)
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

// reset the deck to battle again
void Deck::Reset()
{
	boosters = 5;
	average = 0;
	for (int i=0;i<currentCard;i++)
	{
		// put back every card to pile
		(pile[i]).SetState('p',true);
	}
}

// clear the deck completely
void Deck::Clear()
{
	for (int i=0;i<currentCard;i++)
	{
		pile[i] = NULL;
	}
	currentCard = 0;
}

// returns the current size of the deck
int Deck::DeckSize()
{
	return currentCard;
}

Deck::Deck(int size)
{
	boosters = 5;
	maxSize = size;
	currentCard = 0;
	average = 0;
	pile = new Card[size];
}

Deck::Deck()
{
	currentCard = 0;
	boosters = 5;
	average = 0;
}

Deck::~Deck()
{

}