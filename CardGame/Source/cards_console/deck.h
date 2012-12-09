#ifndef DECK_H
#define DECK_h

class Deck
{
private:
	int maxSize;		// sets the maximum size of the deck
	int currentCard;	// sets the actual size of the deck
	int boosters;		// sets the actual amount of boosters we have
	int maxBoosters;	// amount of maximum boosters per battle
	float average;		// holds the average power of our cards
	Card* pile;			// hold the pointers to our cards

public:
	
	int AddCard(Card card, bool silent);

	void RemoveCard(Card card, bool silent);

	Card* GetCards();

	int GenerateDeck(int lowest, int highest, int count, bool repeat, bool silent);

	void ShowHand(int maxCards);

	Card* BattleHand(int maxCards);

	int Booster(int change);

	int MaxBoosters();

	float GetAverage();

	Card* SelectStrongest();

	Card* SelectWeakest();

	Card* GetRandomCard(int size);

	void Reset();

	void Clear();

	int DeckSize();

	Deck(int size, int mBoosters);

	~Deck();
};

#endif