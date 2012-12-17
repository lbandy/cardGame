#include "headers.h"

// Card related functions

int GFX::DisplayCard(sf::Sprite* card, int owner, int cardCount, int maxCardCount)
{
	// set a unique display index to every card
	index++;

	float cardX = card->GetSize().x;
	float cardY = card->GetSize().y;

	float x, y;

	GFX::SetPositions(inBattle, cardX, cardY, owner, cardCount, maxCardCount, x, y);

	card->SetPosition(resX / 2.0f, owner == 1 ? resY + (cardY * (2 + cardCount)) :  (cardY * -2));

	elements->Add(index, card, owner);
	elements->SetPositionByIndex(index, x, y, 80 + (10 * cardCount), false);

	return index;
}

void GFX::PlayBattle(int playerIndex, int cpuIndex, int winner, int round)
{
	for (int i=0; i<elements->Size(); i++)
	{
		if (elements->GetDisplayIndex(i) == playerIndex)
		{
			elements->SetPositionByIndex(playerIndex, elements->GetSprite(i)->GetPosition().x, elements->GetSprite(i)->GetPosition().y - 15, 30, false);
			BoosterFollowCard(i, 1, round);
			if (winner == 1) elements->PutToEnd(i);
		}
		
		else if (elements->GetDisplayIndex(i) == cpuIndex)
		{
			elements->SetPositionByIndex(cpuIndex, elements->GetSprite(i)->GetPosition().x, elements->GetSprite(i)->GetPosition().y + 15, 30, false);
			BoosterFollowCard(i, 2, round);
			if (winner == 2) elements->PutToEnd(i);
		}
	}

	selectedCardCount = 0;
}

void GFX::PutCardsAway(int playerIndex, int cpuIndex, int roundCount, int maxRoundCount)
{
	for (int i=0; i<elements->Size(); i++)
	{
		if (elements->GetDisplayIndex(i) == playerIndex)
		{
			float x, y;
			GFX::CalculateRestingPlace(elements->GetOwner(i), roundCount, maxRoundCount, elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, x, y);
			elements->SetPositionByIndex(playerIndex, x, y, 60, false);

			BoosterFollowCard(i, 1, roundCount);
		}
		
		else if (elements->GetDisplayIndex(i) == cpuIndex)
		{
			float x, y;
			GFX::CalculateRestingPlace(elements->GetOwner(i), roundCount, maxRoundCount, elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, x, y);
			elements->SetPositionByIndex(cpuIndex, x, y, 60, false);

			BoosterFollowCard(i, 2, roundCount);
		}
	}
}

void GFX::SelectCardToAward(int index)
{
	for (int i=0; i<elements->Size(); i++)
	{
		if (elements->GetDisplayIndex(i) == index)
		{
			float x, y;
			elements->SetOwner(i, elements->GetOwner(i) == 1 ? 2 : 1);

			GFX::SelectCard(elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), x, y);
			elements->SetPositionByIndex(index, x, y, 60, false);
		}
	}
}

void GFX::SelectCardToBattleDeck(int index, int cardCount, int maxCardCount)
{
	for (int i=0; i<elements->Size(); i++)
	{
		if (elements->GetDisplayIndex(i) == index)
		{
			float x, y;
			GFX::SetPositions(true, elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), cardCount, maxCardCount, x, y);
			elements->SetPositionByIndex(index, x, y, 60, false);
			elements->Selected(i, cardCount);
		}
	}
}

void GFX::SelectCardToFight(int index, int cardCount)
{
	for (int i=0; i<elements->Size(); i++)
	{
		if (elements->GetDisplayIndex(i) == index)
		{
			float x, y;

			GFX::SelectCard(elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), x, y);
			elements->SetPositionByIndex(index, x, y, 60, false);
			elements->Selected(i, cardCount);
			selectedCardCount++;

			if (elements->GetOwner(i) == 1) 
			{
				canPlayerHover = false;
				activePlayerCard = i;
			}
			else
			{
				canCpuHover = false;
				activeCpuCard = -1;
			}
		}
	}
}
