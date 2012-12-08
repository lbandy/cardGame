#include "card.h"
#include "stdafx.h"

	// returns the power of the card
	int Card::GetPower()
	{
		return power;
	}

	// returns the state of the card
	char Card::GetState(bool silent)
	{
		if (!silent)
		{
			switch(state)
			{
			case('s'):
				std::cout << "selectable";
				break;
			case('a'):
				std::cout << "active";
				break;
			case('u'):
				std::cout << "used";
				break;
			case('p'):
				std::cout << "in pile";
				break;
			}
		}
		return state;
	}

	// sets the state of the card
	void Card::SetState(char s, bool silent)
	{
		state = s;

		if (!silent)
		{
			std::cout << "Card with power " << power << " has ";
			switch(state)
			{
			case('s'):
				std::cout << "been selected.\n";
				break;
			case('a'):
				std::cout << "been activated.\n";
				break;
			case('u'):
				std::cout << "been used.\n";
				break;
			case('p'):
				std::cout << "returned to pile.\n";
				break;
			}
		}
	}

	Card::Card(int p)
	{
		power = p;
		state = 'p';
	}

	Card::Card()
	{
		power = 0;
		state = 'p';
	}

	Card::~Card()
	{

	}
