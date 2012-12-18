#ifndef GAME_H
#define GAME_H

class Deck;
class CpuPlayer;
class Battle;
class GFX;

class Game
{
private:

	// Variables obtained from ini file

	int battleCardCount, winCount, loseCount, boosterCount, lowestCard, highestCard, startCardCount, winCardCount, loseCardCount;

	// Variables for all the component of the game

	Deck		player, cpu;
	CpuPlayer	ai;
	Battle		battle;
	GFX			gfx;

	// Menu variables

	int		cardsInBattleDeck;
	bool	howToPlay;

	// Battle variables

	bool	inBattle, resized;
	int		roundState, winner, playerCard, cpuCard;

public:

	// Menu

	bool EndGame();										// end game funcion
	void HowToPlay();									// shows how to play
	void StartGame();	
	void SelectCardInHand(int displayIndex);	
	void ShowCards();									// display every card in players hand and sets their display id

	// BattleManager
	
	void Award();										// decides who have won and manages adding/removing cards accordingly
	void ClearBattle();
	void EndBattle();
	void NextMove();									// decides how to move on
	void PlayBattle();
	void StartBattle(); 
	void SelectCardInBattle(int displayIndex, int owner);
	void ShowBattle();									// display the actual fight

	// General

	int	 CoinFlip();
	void Ready();										// called when every animation have been completed
	void WaitForSecond(int second);
	void Resize();
	Game();
	~Game();

};

#endif 