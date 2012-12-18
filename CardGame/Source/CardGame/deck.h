#ifndef DECK_H
#define DECK_h

class Card;

class Deck
{
private:
	std::vector<Card*>	pile;				// holds the pointers to our cards
	std::vector<char>	cardState;			// shows the state of our card
	std::vector<int>	displayIndex;		// holds the index of the sprite if displayed

public:
	
	// Info

	int		Size();								// returns size of the deck
	char	StateByDef(int index);				// returns state of the card at the given index
	char	StateByID(int index);				// returns state of the card at the given display index
	int		State(int index, char state);		// sets the state of the card at the given index
	int		Index(int index);					// returns displayIndex
	void	Index(int index, int displayID);	// sets displayIndex at the given index
	Card*	CardPointerByID(int index);			// returns the Card pointer display by the given displayIndex
	Card*	CardPointerByDef(int index);		// returns the Card pointer display by the given index

	//GetCard

	int GetStrongestCard();
	int GetWeakestCard();
	int GetRandomCard();

	// Manage	

	void AddCard(Card* card, char state);
	void RemoveCard(int index);
	void GenerateDeck(int lowest, int highest, int count, bool repeat);
	void Reset();
	void Clear();

	// General

	Deck();
	~Deck();
};

#endif