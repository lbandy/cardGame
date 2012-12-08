#ifndef CARD_H
#define CARD_H

class Card
{
private:
	int power;
	char state;

public:

	int GetPower();

	char GetState(bool silent);

	void SetState(char s, bool silent);

	Card(int p);
	
	Card();

	~Card();

};

#endif