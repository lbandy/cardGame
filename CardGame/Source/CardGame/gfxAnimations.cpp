#include "headers.h"

void GFX::BoosterPositions(float boosterX, float boosterY, int owner, int boosterCount, int maxBoosterCount, float &x, float &y)
{		
		if (owner == 2)	boosterCount -= maxBoosterCount;

		int maxBoosterPerRow = resX / (spacingX + boosterX);

		int rowCount = boosterCount / maxBoosterPerRow;
		int columnCount = boosterCount - (rowCount * maxBoosterPerRow);

		int totalRows = (maxBoosterCount % maxBoosterPerRow == 0) ? maxBoosterCount / maxBoosterPerRow : (maxBoosterCount / maxBoosterPerRow) + 1;

		int currentBoostersPerRow = (rowCount+1) < totalRows ? maxBoosterPerRow : maxBoosterCount - (rowCount * maxBoosterPerRow);

		float padX = (paddingX - ((currentBoostersPerRow * boosterX) + (currentBoostersPerRow-1) * spacingX)) / 2;

		x = (owner == 1 ? (resX - paddingX) : 0)  + padX + (columnCount * spacingX) + (columnCount * boosterX);
		y = owner == 1 ? resY - (((rowCount+1) * spacingY * 2) + ((rowCount+1) * boosterY)) : ((rowCount+1) * spacingY * 2) + (rowCount * boosterY);
}

void GFX::CalculateRestingPlace(int owner, int cardCount, int maxCardCount, float cardX, float cardY, float &x, float &y)
{
	x = cardCount <= (maxCardCount / 2) ? (spacingX * cardCount) + ((cardCount - 1) * cardX) : resX - ((spacingX + cardX) * (cardCount - 2));
	y = (resY / 2) - (owner == 1 ? 0 + 15 : cardY - 15) ;
}

void GFX::HoverCard(bool hovered, float cardY, int owner, float &y)
{
	y = owner == 1 ? resY - cardY - (hovered ? spacingY * 3 : spacingY) : (hovered ? spacingY * 3 : spacingY);
}

void GFX::SelectCard(float cardX, float cardY, int owner, float &x, float &y)
{
	x = (resX / 2) - (cardX / 2);
	y = (resY / 2) - (owner == 1 ? 0 : cardY);
}

void GFX::SetPositions(bool inBattle, float cardX, float cardY, int owner, int cardCount, int maxCardCount, float &x, float &y)
{
	int maxCardPerRow = resX / (spacingX + cardX);

	int rowCount = cardCount / maxCardPerRow;
	int columnCount = cardCount - (rowCount * maxCardPerRow);

	int totalRows = (maxCardCount % maxCardPerRow == 0) ? maxCardCount / maxCardPerRow : (maxCardCount / maxCardPerRow) + 1;
	
	int currentCardsPerRow = (rowCount+1) < totalRows ? maxCardPerRow : maxCardCount - (rowCount * maxCardPerRow);
	
	paddingX = (resX - ((currentCardsPerRow * cardX) + (currentCardsPerRow-1) * spacingX)) / 2;

	x = paddingX + (columnCount * spacingX) + (columnCount * cardX);
	y = (inBattle && (owner == 1)) ? resY - (((rowCount+1) * spacingY) + ((rowCount+1) * cardY)) : ((rowCount+1) * spacingY) + (rowCount * cardY);
}