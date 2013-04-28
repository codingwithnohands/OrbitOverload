//Basic Class for Defender
#include "stdafx.h"

#ifndef ALIEN_H
#define ALIEN_H

#include "Destructible.h"
#include "Ship.h"

class Alien : public Destructible, public Ship
{
	protected:
	public:
		bool M_bMoveRow();
		Alien(HINSTANCE hInstance, RECT pos, int posX, int posY, int ID, int speed, int type);
		~Alien();
};

#endif