#include "headers.h"

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

	SwordPosition();
	SetButtonPositions();

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
			if (inBattle && canInteract && draggedBoosterIndex == -1 && (canPlayerHover || canCpuHover) && event.Type == sf::Event::MouseMoved)
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

			// if player clicked the mouse
			if ((event.Type == sf::Event::MouseButtonPressed) && (event.MouseButton.Button == sf::Mouse::Left))
			{
				int mousePosX = input.GetMouseX();
				int mousePosY = input.GetMouseY();

				if (inBattle)
				{
					if (canInteract)
					{
						// if mouse clicked on sword
						if(!canCpuHover && ! canPlayerHover && IsMouseOver(sword, mousePosX, mousePosY))
						{
							game->ShowBattle();
						}

						for (int i=0;i<boosters->Size();i++)
						{
							// if we are over a booster
							if (boosters->GetOwner(i) == 1 && IsMouseOver(boosters->GetSprite(i), mousePosX, mousePosY) && boosters->Selected(i) == 0)
							{
								//put it to the end so it will always be on top
								boosters->PutToEnd(i);
								draggedBoosterIndex = boosters->Size() - 1;
							}
						}

						 // we need to test based on drawing order, so we can always get the top card in case of overlap
						for (int i=(elements->Size()-1);i>=0;i--)
						{
							// if mouse is clicked on a card
							if(IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY))
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
						}
					}
				}
				// if we are in menu
				else if (inMenu)
				{
					if (IsMouseOver(startButton, mousePosX, mousePosY))
					{
						game->StartGame();
					}

					else if (IsMouseOver(howToPlayButton, mousePosX, mousePosY))
					{
						game->HowToPlay();
					}
				}
				// if we are in hand
				else if (inHand)
				{
					for (int i=(elements->Size()-1);i>=0;i--)
					{
						// add the card to battle deck
						if (IsMouseOver(elements->GetSprite(i), mousePosX, mousePosY) && elements->Selected(i) == 0)
						{
							game->SelectCardInHand(elements->GetDisplayIndex(i));
						}
					}
				}
				// if we are the endgame screen
				else if (inEnd)
				{
					if (IsMouseOver(youWin, mousePosX, mousePosY) || IsMouseOver(youLose, mousePosX, mousePosY))
					{
						InMenu();
					}
				}
			}

			if ((event.Type == sf::Event::MouseButtonReleased) && (event.MouseButton.Button == sf::Mouse::Left))
			{
				// booster drag & drop effect deactivated
				if (inBattle && (draggedBoosterIndex != -1))
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
			}
			
			// if the window is resized, we need to rearrange everything
			if (event.Type == sf::Event::Resized)
			{
				resX = App.GetWidth();
				resY = App.GetHeight();

				if (resX == 0 || resY == 0) break;

				if (table->GetSize().x < resX)
				{
					table->SetScaleX(table->GetScale().x * resX / table->GetSize().x);
				}
				
				if (table->GetSize().y < resY)
				{
					table->SetScaleY(table->GetScale().y * resY / table->GetSize().y);
				}

				SetButtonPositions();
				
				ResizeWindow();

				App.SetView(view = sf::View(sf::FloatRect(0,0,resX,resY)));
			}
		}


		// Event detection compete, display the screen

		App.Draw(*table);

			if (inBattle || inHand)
			{
				// moves the cards in motion
				for (int i=0;i<elements->Size();i++)
				{
					float x, y;

					if (elements->GetPosition(i, x, y) >= 0)
					{
						elements->GetSprite(i)->Move(x, y);
						moving = true;
					}

					// display every card in buffer
					App.Draw(*elements->GetSprite(i));
				}
			}
			else if (inMenu)
			{
				App.Draw(*startButton);
				App.Draw(*howToPlayButton);
			}
			else if (inEnd)
			{
				if (playerWin) App.Draw(*youWin);
				else App.Draw(*youLose);
			}

			if (inBattle)
			{
				// move dragged booster
				if (draggedBoosterIndex != -1)
				{
					GFX::MoveBooster(draggedBoosterIndex, input.GetMouseX() - 15, input.GetMouseY() - 15, 1);
				}

				// display boosters
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

				if (coin)
				{
					if (coinSprite->GetScale().x > 0.35f)
					{
						coinSprite->SetScaleX(coinSprite->GetScale().x - 0.005f);
						coinSprite->SetScaleY(coinSprite->GetScale().y - 0.005f);
						App.Draw(*coinSprite);

						moving = true;
					}
					else
					{
						coin = false;
						coinSprite->SetScaleX(1);
						coinSprite->SetScaleY(1);
					}

				}
			}


			App.Display();

			// checks if we need to move anything else, if not, send the ready signal
			if (lastMoved && !moving) game->Ready();
			lastMoved = moving;
	}
}

GFX::GFX()
{
	selectedCardCount = 0;
	spacingX = 10;
	spacingY = 10;
	inBattle = false;
	inHand = false;
	inMenu = false;
	inEnd = false;
	playerWin = false;
	coin = false;
	draggedBoosterIndex = -1;

	elements = new SpriteVector();

	boosters = new SpriteVector();

	cDAT assets;
	char* buffer;

	assets.Read("assets.dat");

	std::stringstream buff;

	for (int i=0;i<10;i++)
	{
		buff << "gfx/" << (i+1) << ".jpg";
		
		buffer = assets.GetFile(buff.str());

		if (buffer==NULL)
		{
			std::cout << "Critical error: assets.dat is not found!\n";
			system("pause");
			exit(-1);
		}

		images[i].LoadFromMemory(buffer, assets.GetFileSize(buff.str()));

		buff.str(std::string());
	}

	std::string imgNames[9] = {"gfx/stone.png", "gfx/sword.png", "gfx/background.jpg", "gfx/heads.png", "gfx/tails.png", "gfx/startButton.png", "gfx/howToPlayButton.png", "gfx/youWin.png", "gfx/youLose.png"};

	for (int i=0;i<9;i++)
	{
		buffer = assets.GetFile(imgNames[i]);

		bool error = false;
		switch(i)
		{
		case 0:
			if (!stoneImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 1:
			if (!swordImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 2:
			if (!tableImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 3:
			if (!headsImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 4:
			if (!tailsImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 5:
			if (!startImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 6:
			if (!howToPlayImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 7:
			if (!winImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		case 8:
			if (!loseImg.LoadFromMemory(buffer, assets.GetFileSize(imgNames[i]))) error = true;
			break;
		}
		if (error)
		{
			std::cout << "Critical error: assets.dat is not found!\n";
			system("pause");
			exit(-1);
		}
	}

	sword = new sf::Sprite(swordImg);
	table = new sf::Sprite(tableImg);
	heads = new sf::Sprite(headsImg);
	tails = new sf::Sprite(tailsImg);
	startButton = new sf::Sprite(startImg);
	howToPlayButton = new sf::Sprite(howToPlayImg);
	youWin = new sf::Sprite(winImg);
	youLose = new sf::Sprite(loseImg);
	coinSprite = heads;

	heads->SetCenter(heads->GetSize().x / 2,heads->GetSize().y / 2);
	tails->SetCenter(heads->GetSize().x / 2,heads->GetSize().y / 2);
}

GFX::~GFX()
{
	delete sword;
	delete heads;
	delete tails;
	delete table;
	delete startButton;
	delete howToPlayButton;
	delete youWin;
	delete youLose;
	delete elements;
	delete boosters;
}