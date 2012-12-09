#ifndef CPUPLAYER_H
#define CPUPLAYER_H

class CpuPlayer
{
private:
	float playerAverage;	// the average power of the players deck
	float cpuAverage;		// average power of computers deck

public:

	int SelectDefense(Card* attack, Card* defend, Deck* player, Deck* cpu);
	
	Card* SelectAttack(Deck* deck);

	Card* SelectTarget(Deck* deck);

	CpuPlayer();

	~CpuPlayer();
};

#endif