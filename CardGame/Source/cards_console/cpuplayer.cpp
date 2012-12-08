#include "cpuplayer.h"
#include "stdafx.h"

// calculate if boosters are worth using or not
int CpuPlayer::SelectDefense(Card* attack, Card* defend)
{
	std::cout << "CPU is calculating boosters... (" << attack->GetPower() << " vs. " << defend->GetPower() << ")\n";
	// if the defensive card is weaker, but we can win with up to 3 boosters, use it
	if ((defend->GetPower() <= attack->GetPower()) && (attack->GetPower() - defend->GetPower() < 3) && (cpu->Booster(0) > ((attack->GetPower() - defend->GetPower()) + 1)))
	{
		int booster = attack->GetPower() - defend->GetPower() + 1;
		cpu->Booster(booster);
		return booster;
	}
	else
	{
		return 0;
	}
}

// select the strongest card for the cpu to attack
Card* CpuPlayer::SelectAttack()
{
	return cpu->SelectStrongest();
}

// select the weakest card for the player to defend
Card* CpuPlayer::SelectTarget()
{
	return player->SelectWeakest();
}

CpuPlayer::CpuPlayer(Deck* playerDeck, Deck* cpuDeck)
{
	player = playerDeck;
	cpu = cpuDeck;
}

CpuPlayer::CpuPlayer()
{

}

CpuPlayer::~CpuPlayer()
{

}