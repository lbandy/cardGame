#ifndef GAME_H
#define GAME_H

class Game
{
private:
	int battleCardCount;
	int winCount;
	int loseCount;
	int boosterCount;
	int lowestCard;
	int highestCard;
	int startCardCount;

	int winCardCount;
	int loseCardCount;

	Deck player;
	Deck cpu;
	CpuPlayer ai;
	Battle battle;
	GFX gfx;

	// menu variables
	int cardsInBattleDeck;

	// battle variables
	int roundState;
	bool inBattle;
	int winner;
	int playerCard;
	int cpuCard;

public:

	// Menu

	bool EndGame();	// end game funcion, not yet implemented
	void HowToPlay();	// show how to play, not yet implemented
	void StartGame();	
	void SelectCardInHand(int displayIndex);	
	void ShowCards(); // display every card in players hand and sets their display id

	// BattleManager
	
	void Award();	// decides who have won and manages adding/removing cards accordingly
	void ClearBattle();
	void EndBattle();
	void NextMove();	// decides how to move on
	void PlayBattle();
	void StartBattle(); 
	void SelectCardInBattle(int displayIndex, int owner);
	void ShowBattle();	// display the actual fight

	// General

	int CoinFlip();
	void Ready(); // called when every animation have been completed
	void WaitForSecond(int second);
	Game();
	~Game();

};

#endif 