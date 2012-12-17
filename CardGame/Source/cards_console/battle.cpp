#include "stdafx.h"


// Booster functions

int Battle::CpuBooster()
{
	return cpuBooster;
};
int Battle::PlayerBooster()
{
	return playerBooster;
};
void Battle::CpuBooster(int cBoost)
{
	cpuBooster -= cBoost;
};
void Battle::PlayerBooster(int pBoost)
{
	playerBooster -= pBoost;
};
void Battle::ResetBoosters(int boosterCount)
{
	playerBooster = boosterCount;
	cpuBooster = boosterCount;
}

// Fight related functions
int Battle::Fight(int playerCard, int cpuCard, int playerBoost, int cpuBoost)
{
	round++;

	if ((playerCard + playerBoost) > (cpuCard + cpuBoost))
	{
		playerWin++;
		return 1;
	}
	else if ((playerCard + playerBoost) < (cpuCard + cpuBoost))
	{
		cpuWin++;
		return 2;
	}
	else return 3;
}

int Battle::GetRound()
{
	return round;
}

int Battle::GetWinner()
{
	if (playerWin > cpuWin) return 1;
	else if (playerWin < cpuWin) return 2;
	else return 3;
}

bool Battle::NextStart()
{
	return playerStart;
}

void Battle::PlayerStartNextRound(bool start)
{
	playerStart = start;
}

// General functions
void Battle::EndBattle()
{
	round++;
}

void Battle::PrepareBattle()
{
	round = -1;
}

void Battle::ResetBattle()
{
	round = 0;
	playerStart = true;
	playerWin = 0;
	cpuWin = 0;
}

Battle::Battle()
{
	ResetBattle();
	PrepareBattle();
}

Battle::~Battle()
{

}