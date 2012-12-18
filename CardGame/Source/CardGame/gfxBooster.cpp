#include "headers.h"

// Booster related functions


int GFX::PutBoostersAway(int roundCount)
{
	int boosterCount = 0;
	for (int i = 0; i < boosters->Size(); i++)
	{
		if (boosters->Selected(i) == -1)
		{
			boosters->Selected(i,roundCount);
			boosterCount++;
		}
	}
	return boosterCount;
}

void GFX::ActivateBooster(int index, int cardNumber)
{
	int activeBoosters = 0;
	for (int i = 0; i < boosters->Size(); i++)
	{
		if (boosters->Selected(i) == -1) activeBoosters++;
	}

	boosters->Selected(index, -1);

	float x = elements->GetSprite(cardNumber)->GetPosition().x + (boosters->GetSprite(index)->GetSize().x * activeBoosters);
	float y = elements->GetSprite(cardNumber)->GetPosition().y + (boosters->GetOwner(index) == 1 ? elements->GetSprite(cardNumber)->GetSize().y : boosters->GetSprite(index)->GetSize().y * -1);

	boosters->SetPositionByIndex(boosters->GetDisplayIndex(index), x, y, 60, false);
}

void GFX::BoosterFollowCard(int index, int owner, int round)
{
	for (int i = 0; i < boosters->Size(); i++)
	{
		if (boosters->Selected(i) == round && boosters->GetOwner(i) == owner)
		{
			float x, y;
			int speed = elements->GetTargetPosition(elements->GetDisplayIndex(index), x, y);
			boosters->SetPositionByIndex(boosters->GetDisplayIndex(i), x, y, speed, true);
		}
	}
}

void GFX::MoveBooster(int index, float x, float y, int speed)
{
	boosters->SetPositionByDef(index, x, y, speed);
}

void GFX::MoveCpuBoost(int count, int displayIndex, int owner)
{
	int activeBoosters = 0;

	for(int j = 0; j < elements->Size(); j++)
	{
		if (elements->GetDisplayIndex(j) == displayIndex)
		{
			for (int i = 0; i < boosters->Size(); i++)
			{
				if (activeBoosters < count)
				{
					if (boosters->GetOwner(i) == owner && boosters->Selected(i) == 0)
					{
						GFX::ActivateBooster(i, j);
						activeBoosters++;
					}
				}
			}
		}
	}
	if (count != 0)	WaitForSecond(1);
	else WaitForSecond(0.1f);
}

void GFX::PrepareBoosters(int boosterCount)
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < boosterCount; j++)
		{
			sf::Sprite* sprite = new sf::Sprite(stoneImg); 
			boosters->Add(j + (i * boosterCount), sprite, i + 1);
		}
	}
}

void GFX::ResetBoosters(int boosterCount)
{
	for (int i = 0; i < boosterCount * 2; i++)
	{
		float x,y;

		boosters->Selected(i,0);
		boosters->GetSprite(i)->SetPosition(boosters->GetOwner(i) == 1 ? sf::Vector2f(resX + 50, resY + 50) : sf::Vector2f(-50,-50));

		GFX::BoosterPositions(boosters->GetSprite(i)->GetSize().x, boosters->GetSprite(i)->GetSize().y, boosters->GetOwner(i), boosters->GetDisplayIndex(i), boosterCount, x, y);
		boosters->SetPositionByIndex(boosters->GetDisplayIndex(i), x, y, 140, false);
	}
}