#include "headers.h"


int main()
{
	std::cout << "Welcome to the Card Game!\n\nHere is how to play...\n\nIn your hand, select four cards, they will be your cards used in battle.\n\n";
	std::cout << "When in battle, select a card for yourself and for your opponent as well.\nDrag and drop boosters on your cards to make them stronger.\n\n";
	std::cout << "When everything is set, click the Sword icon to start the actual round.\nThe card with higher attack defeates the other.\n\n";
	std::cout << "Whoever wins, starts the next round. Who wins more rounds wins the battle.\nIn case of a Draw, a coin will be flipped.\n\n";
	std::cout << "If you win a battle a card will be awarded. If you lose, one will be taken away.\n";
	std::cout << "Good luck and have fun!\n";

	Game* game = new Game();

	return 0;
}