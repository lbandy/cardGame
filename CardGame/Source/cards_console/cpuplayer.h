#ifndef CPUPLAYER_H
#define CPUPLAYER_H

class CpuPlayer
{
private:
	float playerAverage;	// the average power of the players deck
	float cpuAverage;		// average power of computers deck
	Deck* player;			
	Deck* cpu;

public:

	int SelectDefense(Card* attack, Card* defend);
	
	Card* SelectAttack();

	Card* SelectTarget();

	CpuPlayer(Deck* playerDeck, Deck* cpuDeck);

	CpuPlayer();

	~CpuPlayer();
};

#endif