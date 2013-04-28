//Class for Defensive Shields
#include "stdafx.h"

#ifndef SHIELD_H
#define SHIELD_H
#include "Object.h"
#include "Destructible.h"

class Shield : public Object, public Destructible
{
	protected:
	public:
		Shield(HINSTANCE hInstance, int posX, int posY);
		~Shield();
};

#endif