#include "battle.h"
#include "stdafx.h"

// set the players card to use in this turn
void Battle::SetPlayerCard(Card* player)
{
	attack = player->GetPower();
	std::cout << "Selected player card power: " << attack << "\n";
	playerCard = player;
}

// set the boost to the player this turn
void Battle::SetPlayerBoost(int playerBoost)
{
	 attack += playerBoost;
	 std::cout << "Using " << playerBoost << " boosters for this round.\n";
}

// set the cpus card to use
void Battle::SetCpuCard(Card* cpu)
{
	defend = cpu->GetPower();
	std::cout << "Selected cpu card power: " << defend << "\n";
	cpuCard = cpu;
}

// set cpu boost
void Battle::SetCpuBoost(int cpuBoost)
{
	defend += cpuBoost;
	std::cout << "CPU is using " << cpuBoost << " boosters for this round.\n";
}

// calculate who have won this round
int Battle::Fight()
{
	if (attack > defend) return 1;		// player
	else if (attack < defend) return 2;	// cpu
	else return 3;						// tie
}

// reset the battle before a new one
void Battle::ResetBattle()
{
	round = 1;
	playerStart = true;
	playerWin = 0;
	cpuWin = 0;
}

// the battle process
void Battle::StartBattle(Deck* player, Deck* cpu, CpuPlayer* aiPlayer)
{
	int winner;
	
	while(round <= cardNumber)
	{
		// display round count
		std::cout << " ----- " << round << ". round ----- \n";

		// if player starts the round
		if (playerStart)
		{
			// showing player hand and selecting card
			std::cout << "Player cards:\n";
			this->SetPlayerCard(player->BattleHand(cardNumber));

			// showing cpu hand and selecting target
			std::cout << "Select target:\n";
			this->SetCpuCard(cpu->BattleHand(cardNumber));
		}
		else
		{
			// AI is selecting cards for cpu and player
			this->SetCpuCard(aiPlayer->SelectAttack(cpu));
			this->SetPlayerCard(aiPlayer->SelectTarget(player));
		}

		// boosting the card power if possible
		if (player->Booster(0) > 0)
		{
			std::cout << "Enter the amount of booster you would like to use (" << player->Booster(0) << "/" << player->MaxBoosters() << " available):\n";
			int booster;
			std::cin >> booster;
			while (booster > player->Booster(0) || booster < 0)
			{
				std::cout << "Enter a valid amount between 0 and " << player->Booster(0) << "\n";
				std::cin >> booster;
			}

			this->SetPlayerBoost(booster);
			player->Booster(booster);
		}

		// calculating cpu boost
		this->SetCpuBoost(aiPlayer->SelectDefense(playerCard, cpuCard, player, cpu));

		// calculating the outcome of the fight
		winner = Fight();
		
		if (winner == 3)
		{
			std::cout << "Tie! Flipping the coin...\n";
			winner = rand() % 2 + 1;
		}
		
		if (winner == 1)
		{
			std::cout << "Player wins this round.\n";
			playerWin++;
			playerStart = true;
		}
		else
		{
			std::cout << "CPU wins this round.\n";
			cpuWin++;
			playerStart = false;
		}
		
		// marking cards as used for this battle
		playerCard->SetState('u',true);
		cpuCard->SetState('u',true);
		round++;
		std::cout << "\n";
	}

	// the final winner is
	winner = playerWin > cpuWin ? 1 : 2;

	// if tie
	if (playerWin == cpuWin) 
	{
		std::cout << "The battle is a tie! Flipping the coin...\n";
		winner = rand() % 2 + 1;
	}
	if (winner == 1)
	{
		// giving a card from the cpu to the player as a reward
		Card* reward = cpu->GetRandomCard(cardNumber);
		std::cout << "Player wins this battle. The reward is a card with a power of " << reward->GetPower() << "!\n";
		player->AddCard(*reward, true);
	}
	else
	{
		// taking away a card from the player
		Card* lost = player->GetRandomCard(cardNumber);
		std::cout << "CPU wins this battle. Player loses a card with a power of " << lost->GetPower() << "!\n";
		player->RemoveCard(*lost, true);
	}
	std::cout << "\n";
}

Battle::Battle(int rounds)
{
	cardNumber = rounds;
	ResetBattle();
}

Battle::~Battle()
{

}