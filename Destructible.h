//Enhancing Class for Object Destruction
#include "stdafx.h"

#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H

class Destructible
{
	protected:
		int health;
		int m_nPoints;
	public:
		int M_nDestroy();
		bool M_bHit();
		~Destructible();
};

#endif