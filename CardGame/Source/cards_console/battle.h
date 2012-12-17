#ifndef BATTLE_H
#define BATTLE_H

class Battle
{
private:
	int round;			// the current round
	bool playerStart;	// true if player is the next to start a round
	int playerWin;		// how many rounds the player have won
	int cpuWin;			// number of rounds the cpu have won
	int playerBooster, cpuBooster;

public:

	// Booster related functions
	int CpuBooster();	// get booster count
	int PlayerBooster();
	void CpuBooster(int cBoost);	// set booster count
	void PlayerBooster(int pBoost);
	void ResetBoosters(int boosterCount);
	
	// Fight related functions
	int Fight(int playerCard, int cpuCard, int playerBoost, int cpuBoost); // calculates the fight
	int GetRound();
	int GetWinner();	// sets the winner
	bool NextStart(); // who starts next
	void PlayerStartNextRound(bool start);	// set who starts next round

	// General functions
	void EndBattle();
	void PrepareBattle();
	void ResetBattle();

	Battle();
	~Battle();
};

#endif