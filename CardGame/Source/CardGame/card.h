#ifndef CARD_H
#define CARD_H

class Card
{
private:
	int			power;
	sf::Sprite	sprite;

public:

	int			GetPower();
	sf::Sprite*	Sprite();
	void		Sprite(sf::Image* img);
	Card(int p);
	~Card();
};

#endif