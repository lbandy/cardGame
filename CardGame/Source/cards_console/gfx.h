#ifndef GFX_H
#define GFX_H

class GFX
{
private:
	Game* game;
	SpriteVector* elements;
	sf::Image img, swordImg;
	sf::Image images[10];
	sf::Sprite* sword;
	SpriteVector* boosters;
	int index, resX, resY, activePlayerCard, activeCpuCard, spacingX, spacingY, draggedBoosterIndex, selectedCardCount;
	bool canInteract, canPlayerHover, canCpuHover, cardHovered, inBattle;
	float paddingX;

	//sf::Sprite* heads;
	//sf::Sprite* tails;
	//sf::Image headsImg;
	//sf::Image tailsImg;

public:

	// Main graphics core

	void Start(int resX, int resY, Game* gameInstance);
	GFX();
	~GFX();

	// General graphics related functions

	sf::Image* GetImage(int number);
	bool IsMouseOver(sf::Sprite* sprite, int mousePosX, int mousePosY);

	void CanInteract(bool toggle);
	void ClearDisplaybuffer();
	void ClearTable(); 
	void EndOfRound();
	void StartBattle();
	void ResetCardPositions();
	void ResizeWindow();
	void SwordPosition();
	void WaitForSecond(float second);
	void WinGame();
	void LoseGame();

	// Card related functions
	int DisplayCard(sf::Sprite* card, int owner, int cardCount, int maxCardCount); // adds a card to the display buffer
	void PlayBattle(int playerIndex, int cpuIndex, int winner, int round);
	void PutCardsAway(int playerIndex, int cpuIndex, int roundCount, int maxRoundCount); // puts the cards aside at the end of the round
	void SelectCardToAward(int index);
	void SelectCardToBattleDeck(int index, int cardCount, int maxCardCount); 
	void SelectCardToFight(int index, int cardCount);

	// Booster related functions

	int PutBoostersAway(int roundCount);
	void ActivateBooster(int index, int cardNumber);
	void BoosterFollowCard(int index, int owner, int round);	// sets a booster to follow a specific card
	void MoveBooster(int index, float x, float y, int speed);
	void MoveCpuBoost(int count, int displayIndex);
	void PrepareBoosters(int boosterCount);
	void ResetBoosters(int boosterCount);

	// Animation calculation functions

	void BoosterPositions(float boosterX, float boosterY, int owner, int boosterCount, int maxBoosterCount, float &x, float &y);	// sets starting position for cards
	void CalculateRestingPlace(int owner, int cardCount, int maxCardCount, float cardX, float cardY, float &x, float &y);	// calculates the card positions after a round
	void HoverCard(bool hovered, float cardY, int owner, float &y);
	void SelectCard(float cardX, float cardY, int owner, float &x, float &y);
	void SetPositions(bool inBattle, float cardX, float cardY, int owner, int cardCount, int maxCardCount, float &x, float &y); // sets starting position for cards
};

#endif