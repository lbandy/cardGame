#include "stdafx.h"

void GFX::Start(int inResX, int inResY, Game* gameInstance)
{
	game = gameInstance;

	resX = inResX;
	resY = inResY;

	sf::RenderWindow App(sf::VideoMode(resX,resY,32),"Card Game");

	App.SetFramerateLimit(60);

	sf::Event event;
	const sf::Input& input = App.GetInput();
	sf::View view(App.GetDefaultView());

	GFX::SwordPosition();

	game->StartGame();

	bool moving = false;
	bool lastMoved = false;

	while(App.IsOpened())
	{
		moving = false;

		while (App.GetEvent(event))
		{
			if (event.Type == sf::Event::Closed || (event.Type == sf::Event::KeyPressed && event.Key.Code == sf::Key::Escape))
			{
				App.Close();
			}

			// controls the hover over card effect
			if (draggedBoosterIndex == -1 && inBattle && canInteract && (canPlayerHover || canCpuHover) && event.Type == sf::Event::MouseMoved)
			{
				int mousePosX = event.MouseMove.X;
				int mousePosY = event.MouseMove.Y;

				// we need to test based on drawing order, so we can always get the top card in case of overlap
				for (int i=(elements->Size()-1);i>=0;i--)
				{
					if (elements->Selected(i) == 0)
					{
						// player cards
						if (canPlayerHover && elements->GetOwner(i) == 1)
						{
							// hover on
							if((!cardHovered && activePlayerCard == -1) && GFX::IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY))
							{
								activePlayerCard = elements->GetDisplayIndex(i);
								cardHovered = true;
								float y;
								GFX::HoverCard(true, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), y);
								elements->SetPositionByIndex(elements->GetDisplayIndex(i), elements->GetSprite(i)->GetPosition().x, y, 30, false);
							}
							// hover off
							else if((cardHovered && activePlayerCard == elements->GetDisplayIndex(i)) && !GFX::IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY))
							{
								activePlayerCard = -1;
								cardHovered = false;
								float y;
								GFX::HoverCard(false, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), y);
								elements->SetPositionByIndex(elements->GetDisplayIndex(i), elements->GetSprite(i)->GetPosition().x, y, 30, false);
							}
						}

						// cpu cards
						else if (canCpuHover && elements->GetOwner(i) == 2)
						{
							// hover on
							if((!cardHovered && activeCpuCard == -1) && GFX::IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY)) // if mouse is over a sprite
							{
								activeCpuCard = elements->GetDisplayIndex(i);
								cardHovered = true;
								float y;
								GFX::HoverCard(true, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), y);
								elements->SetPositionByIndex(elements->GetDisplayIndex(i), elements->GetSprite(i)->GetPosition().x, y, 30, false);
							}
							// hover off
							else if((cardHovered && activeCpuCard == elements->GetDisplayIndex(i)) && !GFX::IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY)) // if mouse is not over a sprite
							{
								activeCpuCard = -1;
								cardHovered = false;
								float y;
								GFX::HoverCard(false, elements->GetSprite(i)->GetSize().y, elements->GetOwner(i), y);
								elements->SetPositionByIndex(elements->GetDisplayIndex(i), elements->GetSprite(i)->GetPosition().x, y, 30, false);
							}
						}
					}
				}
			}

			// booster drag & drop effect activated
			if (inBattle && canInteract && (event.Type == sf::Event::MouseButtonPressed) && (event.MouseButton.Button == sf::Mouse::Left))
			{
				for (int i=0;i<boosters->Size();i++)
				{
					// if we are over a booster
					if (boosters->GetOwner(i) == 1 && IsMouseOver(boosters->GetSprite(i), input.GetMouseX(), input.GetMouseY()) && boosters->Selected(i) == 0)
					{
						//put it to the end so it will always be on top
						boosters->PutToEnd(i);
						draggedBoosterIndex = boosters->Size() - 1;
					}
				}
			}

			// booster drag & drop effect deactivated
			if (inBattle && (draggedBoosterIndex != -1) && (event.Type == sf::Event::MouseButtonReleased) && (event.MouseButton.Button == sf::Mouse::Left))
			{
				int mousePosX = input.GetMouseX();
				int mousePosY = input.GetMouseY();

				for (int i=(elements->Size()-1);i>=0;i--)
				{
					// check if we are over our card
					if((i == activePlayerCard) && GFX::IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY))
					{	
						// if so, activate the buffer
						GFX::ActivateBooster(draggedBoosterIndex, i);
						draggedBoosterIndex = -1;
					}
				}

				// if not, then put it back to the start positions
				if (draggedBoosterIndex != -1)
				{
					float x, y;
					GFX::BoosterPositions(boosters->GetSprite(draggedBoosterIndex)->GetSize().x, boosters->GetSprite(draggedBoosterIndex)->GetSize().y, boosters->GetOwner(draggedBoosterIndex), boosters->GetDisplayIndex(draggedBoosterIndex), boosters->Size() / 2, x, y);
					GFX::MoveBooster(draggedBoosterIndex, x, y, 60);
					draggedBoosterIndex = -1;
				}
			}

			// if the window is resized, we need to rearrange everything
			if (event.Type == sf::Event::Resized)
			{
				resX = App.GetWidth();
				resY = App.GetHeight();
				App.SetView(view = sf::View(sf::FloatRect(0,0,resX,resY)));
				GFX::ResizeWindow();
			}
		}

		// detects if we have clicked on something
		if (canInteract && draggedBoosterIndex == -1 && input.IsMouseButtonDown(sf::Mouse::Left))
		{
			int mousePosX = input.GetMouseX();
			int mousePosY = input.GetMouseY();

			 // if mouse clicked on sword
			if(inBattle && !canCpuHover && ! canPlayerHover && GFX::IsMouseOver(sword, mousePosX, mousePosY))
			{
				game->ShowBattle();
			}

			for (int i=(elements->Size()-1);i>=0;i--) // we need to test based on drawing order, so we can always get the top card in case of overlap
			{
				 // if mouse is clicked on a sprite
				if(GFX::IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY))
				{	
					// if we are in battle select the card as the one used in this round
					if (inBattle)
					{
						if  (elements->Selected(i) == 0)
						{
							if (elements->GetOwner(i) == 1 && canPlayerHover)
							{
								cardHovered = false;
								game->SelectCardInBattle(elements->GetDisplayIndex(i), 1);
							}
							else if (elements->GetOwner(i) == 2 && canCpuHover)
							{
								cardHovered = false;
								game->SelectCardInBattle(elements->GetDisplayIndex(i), 2);
							}
						}
					}
					// if we are not in battle, add the card to battle deck
					else if (elements->Selected(i) == 0)
					{
						game->SelectCardInHand(elements->GetDisplayIndex(i));
					}
				}
			}
		}

		// moves the cards in motion
		for (int i=0;i<elements->Size();i++)
		{
			float x, y;

			if (elements->GetPosition(i, x, y) >= 0)
			{
				elements->GetSprite(i)->Move(x, y);
				moving = true;
			}
		}

			// checks if we need to move anything else, if not, send the ready signal
			if (lastMoved && !moving) game->Ready();

			lastMoved = moving;

			App.Clear(sf::Color(200, 200, 200));
			
			// display every card in buffer
			for (int i=0;i<elements->Size();i++)
			{
				App.Draw(*elements->GetSprite(i));
			}

			// display boosters
			if (inBattle)
			{
				if (draggedBoosterIndex != -1)
				{
					GFX::MoveBooster(draggedBoosterIndex, input.GetMouseX() - 15, input.GetMouseY() - 15, 1);
				}

				for (int i=0;i<boosters->Size();i++)
				{
					float x, y;

					if (boosters->GetPosition(i, x, y) >= 0)
					{
						boosters->GetSprite(i)->Move(x, y);
					}

					App.Draw(*boosters->GetSprite(i));
				}

				// display sword if cards are selected
				if (selectedCardCount == 2)
				{
					App.Draw(*sword);
				}
			}

			App.Display();
	}
}
GFX::GFX()
{
	selectedCardCount = 0;
	spacingX = 10;
	spacingY = 10;
	inBattle = false;
	draggedBoosterIndex = -1;

	elements = new SpriteVector();

	boosters = new SpriteVector();

	std::stringstream buff;

	for (int i=0;i<10;i++)
	{
		buff << "gfx/" << (i+1) << ".jpg";
		std::cout << buff.str() << "\n";
		images[i].LoadFromFile(buff.str());
		buff.str(std::string());
	}

	img.LoadFromFile("gfx/stone.png");
	swordImg.LoadFromFile("gfx/sword.png");
	//headsImg.LoadFromFile("gfx/heads.png");
	//tailsImg.LoadFromFile("gfx/tails.png");

	sword = new sf::Sprite(swordImg);
	//heads = new sf::Sprite(headsImg);
	//tails = new sf::Sprite(tailsImg);
}
GFX::~GFX()
{
	delete sword;
	//delete heads;
	//delete tails;
	delete elements;
	delete boosters;
}