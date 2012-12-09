#ifndef BATTLE_H
#define BATTLE_H

class Battle
{
private:
	int round;			// the current round
	int cardNumber;		// the card number usable in battles
	bool playerStart;	// true if player is the next to start a round
	Card* playerCard;	// the active card played by the player
	Card* cpuCard;		// the active card played by the computer
	int attack;			// the players total power with boosters
	int defend;			// the cpus total power with boosters
	int playerWin;		// how many rounds the player have won
	int cpuWin;			// number of rounds the cpu have won

public:

	void SetPlayerCard(Card* player);
	void SetPlayerBoost(int playerBoost);

	void SetCpuCard(Card* cpu);
	void SetCpuBoost(int cpuBoost);

	void ResetBattle();

	void StartBattle(Deck* player, Deck* cpu, CpuPlayer* aiPlayer);

	int Fight();

	Battle(int rounds);

	~Battle();
};

#endif