#include "headers.h"

	// returns the power of the card
	int Card::GetPower()
	{
		return power;
	}

	sf::Sprite* Card::Sprite()
	{
		return &sprite;
	}

	void Card::Sprite(sf::Image* img)
	{
		sprite.SetImage(*img);
	}

	Card::Card(int p)
	{
		power = p;
	}

	Card::~Card()
	{

	}
