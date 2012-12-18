#include "headers.h"

int SpriteVector::GetDisplayIndex(int index)
{
	return vectIndex.at(index);
}

int SpriteVector::GetOwner(int index)
{
	return vectOwner.at(index);
}

int SpriteVector::GetPosition(int index, float &x, float &y) // using the vector index, not the displayIndex
{
	x = vectX.at(index);
	y = vectY.at(index);
	
	vectSteps.at(index) -= 1;

	return vectSteps.at(index);
}

int SpriteVector::GetTargetPosition(int index, float &x, float &y)
{
	for (int i = 0; i < (int)vectX.size(); i++)
	{
		if (vectIndex.at(i) == index)
		{
			if (vectSteps.at(i) < 0)
			{
				x = vectSprite.at(i)->GetPosition().x;
				y = vectSprite.at(i)->GetPosition().x;
			}
			else
			{
				x = vectX.at(i);
				y = vectY.at(i);
			}
			return vectSteps.at(i);
		}
	}

	return -1;
}

int SpriteVector::Selected(int index)
{
	return vectSelected.at(index);
}

int SpriteVector::Size()
{
	return vectX.size();
}

sf::Sprite* SpriteVector::GetSprite(int index) // using the vector index, not the displayIndex
{
	return vectSprite.at(index);
}

void SpriteVector::Add(int index, sf::Sprite* spr, int owner)
{
	vectIndex.push_back(index);
	vectSprite.push_back(spr);
	vectX.push_back(0);
	vectY.push_back(0);
	vectSteps.push_back(0);
	vectOwner.push_back(owner);
	vectSelected.push_back(0);
}

void SpriteVector::Clear()
{
	vectIndex.clear();
	vectSprite.clear();
	vectX.clear();
	vectY.clear();
	vectSteps.clear();
	vectOwner.clear();
	vectSelected.clear();
}

void SpriteVector::SetPositionByIndex(int index, float x, float y, int speed, bool fixed)
{
	for (int i = 0; i < (int)vectX.size(); i++)
	{
		if (vectIndex.at(i) == index)
		{
			vectX.at(i) = fixed ? x : (x - vectSprite.at(i)->GetPosition().x) / (float)speed;
			vectY.at(i) = fixed ? y : (y - vectSprite.at(i)->GetPosition().y) / (float)speed;
			vectSteps.at(i) = speed;
			return;
		}
	}
}

void SpriteVector::SetPositionByDef(int index, float x, float y, int speed)
{
	vectX.at(index) = (x - vectSprite.at(index)->GetPosition().x) / (float)speed;
	vectY.at(index) = (y - vectSprite.at(index)->GetPosition().y) / (float)speed;
	vectSteps.at(index) = speed;
}

void SpriteVector::SetOwner(int index, int owner)
{
	vectOwner.at(index) = owner;
}

void SpriteVector::Selected(int index, int change)
{
	vectSelected.at(index) = change;
}

void SpriteVector::PutToEnd(int i)
{
	vectIndex.push_back(vectIndex.at(i));
	vectSprite.push_back(vectSprite.at(i));
	vectX.push_back(vectX.at(i));
	vectY.push_back(vectY.at(i));
	vectSteps.push_back(vectSteps.at(i));
	vectOwner.push_back(vectOwner.at(i));
	vectSelected.push_back(vectSelected.at(i));

	vectIndex.erase(vectIndex.begin()+i);
	vectSprite.erase(vectSprite.begin()+i);
	vectX.erase(vectX.begin()+i);
	vectY.erase(vectY.begin()+i);
	vectSteps.erase(vectSteps.begin()+i);
	vectOwner.erase(vectOwner.begin()+i);
	vectSelected.erase(vectSelected.begin()+i);
}

void SpriteVector::WaitForSeconds(int index, int speed)
{
	for (int i = 0; i < (int)vectX.size(); i++)
	{
		if (vectIndex.at(i) == index)
		{
			vectX.at(i) = 0;
			vectY.at(i) = 0;
			vectSteps.at(i) = speed;
		}
	}
}

SpriteVector::SpriteVector()
{

}

SpriteVector::~SpriteVector()
{
	SpriteVector::Clear();
}