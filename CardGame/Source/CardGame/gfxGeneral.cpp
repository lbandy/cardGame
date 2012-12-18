#include "headers.h"

// General graphics functions

sf::Image* GFX::GetImage(int number)
{
	return &images[number-1];
}

bool GFX::IsMouseOver(sf::Sprite* sprite, int mousePosX, int mousePosY)
{
	sf::Vector2f spritePos	= sprite->GetPosition();
	sf::Vector2f spriteSize = sprite->GetSize();

	if ((mousePosX > spritePos.x && mousePosX < (spritePos.x + spriteSize.x)) && (mousePosY > spritePos.y && mousePosY < (spritePos.y + spriteSize.y)))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GFX::CanInteract(bool toggle)
{
	canInteract = toggle;
}

void GFX::ClearDisplaybuffer()
{
	inBattle = false;
	elements->Clear();
	index = 0;
}

void GFX::ClearTable()
{
	for (int i = 0; i < elements->Size(); i++)
	{
		elements->SetPositionByIndex(elements->GetDisplayIndex(i), resX / 2, (elements->GetOwner(i) == 1) ? resY + 200 : -200, 90, false);
	}

	for (int i = 0; i < boosters->Size(); i++)
	{
		boosters->SetPositionByDef(i, resX / 2, (boosters->GetOwner(i) == 1) ? resY + 200 : -200, 30);
	}
}

void GFX::EndOfRound()
{
	activePlayerCard	= -1;
	cardHovered			= false;
	canPlayerHover		= true;
	
	activeCpuCard		= -1;
	cardHovered			= false;
	canCpuHover			= true;
}

void GFX::FlipCoin(bool showHeads)
{
	coin						= true;

	if (showHeads) coinSprite	= heads;
	else coinSprite				= tails;
}

void GFX::InEnd(bool win)
{
	inBattle	= false;
	inHand		= false;
	inMenu		= false;
	inEnd		= true;
	playerWin	= win;
}

void GFX::InBattle()
{
	inBattle	= true;
	inHand		= false;
	inMenu		= false;
	inEnd		= false;
}

void GFX::InHand()
{
	inBattle	= false;
	inHand		= true;
	inMenu		= false;
	inEnd		= false;
}

void GFX::InMenu()
{
	inBattle	= false;
	inHand		= false;
	inMenu		= true;
	inEnd		= false;
}

void GFX::SetButtonPositions()
{
		startButton->SetPosition((resX - startButton->GetSize().x) / 2, (resY - startButton->GetSize().y) / 2 - (howToPlayButton->GetSize().y / 2));
		howToPlayButton->SetPosition((resX - howToPlayButton->GetSize().x) / 2, (resY - howToPlayButton->GetSize().y) / 2 + (howToPlayButton->GetSize().y / 2));
		
		youWin->SetPosition((resX - youWin->GetSize().x) / 2, (resY - youWin->GetSize().y) / 2);
		youLose->SetPosition((resX - youLose->GetSize().x) / 2, (resY - youLose->GetSize().y) / 2);

		heads->SetPosition(resX / 2, (resY + heads->GetSize().y) / 2);
		tails->SetPosition(resX / 2, (resY - tails->GetSize().y) / 2);
}

void GFX::StartBattle()
{
	InBattle();

	canInteract			= true;
	canPlayerHover		= true;
	canCpuHover			= true;
	cardHovered			= false;

	activePlayerCard	= -1;
	activeCpuCard		= -1;

	index				= 0;
}

void GFX::ResetCardPositions()
{
	for (int i = 0; i < elements->Size(); i++)
	{
		elements->Selected(i, 0);
	}

	for (int i = 0; i < boosters->Size(); i++)
	{
		boosters->Selected(i, 0);
	}

	GFX::ResizeWindow();
}

void GFX::ResizeWindow()
{
	GFX::CanInteract(false);

	int playerElementCountUsed	= 0;
	int cpuElementCountUsed		= 0;

	for (int i = 0; i < elements->Size(); i++)
	{
		float x, y;
		int owner = elements->GetOwner(i);

		// deal with cards still in start position
		if (elements->Selected(i) == 0)
		{
			GFX::SetPositions(inBattle, elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, owner, owner == 1 ? playerElementCountUsed : cpuElementCountUsed, inBattle ? elements->Size() / 2 : elements->Size(), x, y);
			elements->SetPositionByIndex(elements->GetDisplayIndex(i), x, y, 60, false);

			if (owner == 1)
			{
				playerElementCountUsed++;
			}
			else
			{
				cpuElementCountUsed++;
			}
		}
		else
		{
			bool gotPair = false;
			
				// checks for cards already battled
				for (int j = 0; j < elements->Size(); j++)
					{
						if (elements->GetOwner(j) == owner) continue;

						if (elements->Selected(i) == elements->Selected(j))
						{	
							int highestRoundCount = 0;
							for (int k = 0; k < elements->Size(); k++)
							{
								if (elements->Selected(k) > highestRoundCount) highestRoundCount = elements->Selected(k);
							}

							if (owner == 1)
							{
								// cards are selected but still waiting for sword signal
								if ((selectedCardCount == 2) && (elements->Selected(i) == highestRoundCount))
								{
									GFX::SelectCard(elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), x, y);
									elements->SetPositionByIndex(elements->GetDisplayIndex(i), x, y, 60, false);

									GFX::SelectCard(elements->GetSprite(j)->GetSize().x, elements->GetSprite(j)->GetSize().y, elements->GetOwner(j), x, y);
									elements->SetPositionByIndex(elements->GetDisplayIndex(j), x, y, 60, false);

									BoosterFollowCard(i, owner, -1);
									BoosterFollowCard(j, elements->GetOwner(j), -1);
								}
								else
								{
									GFX::PutCardsAway(elements->GetDisplayIndex(i), elements->GetDisplayIndex(j), elements->Selected(i), elements->Size() / 2);
								}
							}
							
							gotPair = true;
						}
					}

					// only one card is selected
					if (!gotPair)
					{
						GFX::SelectCard(elements->GetSprite(i)->GetSize().x, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), x, y);
						elements->SetPositionByIndex(elements->GetDisplayIndex(i), x, y, 60, false);
						
						BoosterFollowCard(i, owner, -1);
					}
		}
	}

	// handles boosters still in start position
	for (int i = 0; i < boosters->Size(); i++)
	{
		if (boosters->Selected(i) == 0)
		{
			float x, y;
			GFX::BoosterPositions(boosters->GetSprite(i)->GetSize().x, boosters->GetSprite(i)->GetSize().y, boosters->GetOwner(i), boosters->GetDisplayIndex(i), boosters->Size() / 2, x, y);
			boosters->SetPositionByIndex(boosters->GetDisplayIndex(i), x, y, 60, false);
		}
	}

	GFX::SwordPosition();
}

void GFX::SwordPosition()
{
	sword->SetPosition((resX - sword->GetSize().x) / 2, (resY - sword->GetSize().y) / 2);
}

void GFX::WaitForSecond(float second)
{
	elements->SetPositionByIndex(elements->GetDisplayIndex(0), elements->GetSprite(0)->GetPosition().x, elements->GetSprite(0)->GetPosition().y, second * 60, false);
}