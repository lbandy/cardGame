#ifndef CPUPLAYER_H
#define CPUPLAYER_H

class CpuPlayer
{
public:

	int SelectDefense(int playerCard, int cpuCard, int playerBooster, int cpuBooster); // calculate if boosters are worth using or not
	int SelectAttack(Deck* deck);
	int SelectTarget(Deck* deck);

	CpuPlayer();
	~CpuPlayer();
};

#endif