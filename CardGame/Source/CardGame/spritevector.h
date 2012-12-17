#ifndef SPRITEVECTOR_H
#define SPRITEVECTOR_H

class SpriteVector
{
private:
	std::vector<int> vectIndex;
	std::vector<sf::Sprite*> vectSprite;
	std::vector<float> vectX;
	std::vector<float> vectY;
	std::vector<int> vectSteps;
	std::vector<int> vectOwner;
	std::vector<int> vectSelected;

public:

	int GetDisplayIndex(int index);
	int GetOwner(int index);
	int GetPosition(int index, float &x, float &y); // gets movement per frame
	int GetTargetPosition(int index, float &x, float &y);	// get targets position or movement
	int Selected(int index);	// returns if the card has been selected
	int Size();
	sf::Sprite* GetSprite(int index); // returns the sprite
	void Add(int index, sf::Sprite* spr, int owner); // adds a new entry
	void Clear();
	void SetPositionByIndex(int index, float x, float y, int speed, bool fixed); // sets target position and speed by display index
	void SetPositionByDef(int index, float x, float y, int speed); // sets target position and speed by default index
	void SetOwner(int index, int owner);
	void Selected(int index, int change);
	void PutToEnd(int index);
	void WaitForSeconds(int index, int speed);
	SpriteVector();
	~SpriteVector();
};

#endif;