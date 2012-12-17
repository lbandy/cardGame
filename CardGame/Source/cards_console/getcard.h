#ifndef GETCARD_H
#define GETCARD_H

class GetCard : public Deck
{

public:

	Card* GetCards();

	float GetAverage();

	Card* SelectStrongest();

	Card* SelectWeakest();

	Card* GetRandomCard(int size);

	GetCard();

	~GetCard();
};

#endif