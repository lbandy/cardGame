#ifndef BOOSTER_H
#define BOOSTER_H

class Booster
{
private:
	bool used;
	int owner;
	sf::Sprite sprite;

public:

	int Owner();

	void Owner(int own);

	bool Used();

	void Use(bool use);

	sf::Sprite* Sprite();

	Booster();

	~Booster();
};

#endif