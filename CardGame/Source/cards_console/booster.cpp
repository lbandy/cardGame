#include "stdafx.h"

int Booster::Owner()
{
	return owner;
}

void Booster::Owner(int own)
{
	owner = own;
}

bool Booster::Used()
{
	return used;
}

void Booster::Use(bool use)
{
	used = use;
}

sf::Sprite* Booster::Sprite()
{
	return &sprite;
}

Booster::Booster()
{
	//sprite.SetImage(GetImage("gfx/stone.png"));
}

Booster::~Booster()
{

}