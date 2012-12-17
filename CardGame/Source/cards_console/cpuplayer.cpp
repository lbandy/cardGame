#include "stdafx.h"


int CpuPlayer::SelectDefense(int playerCard, int cpuCard, int playerBooster, int cpuBooster)
{
	// if the defensive card is weaker, but we can win with up to 3 boosters, use it
	if ((cpuCard <= playerCard) && (playerCard - cpuCard < 3) && (cpuBooster > ((playerCard - cpuCard) + 1)))
	{
		return playerCard - cpuCard + 1;
	}
	else
	{
		return 0;
	}
}

// select the strongest card for the cpu to attack
int CpuPlayer::SelectAttack(Deck* deck)
{
	return deck->GetStrongestCard();
}

// select the weakest card for the player to defend
int CpuPlayer::SelectTarget(Deck* deck)
{
	return deck->GetWeakestCard();
}

CpuPlayer::CpuPlayer()
{

}

CpuPlayer::~CpuPlayer()
{

}