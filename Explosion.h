#include "stdafx.h"

#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "Object.h"

//Class for Buttons
class Explosion : public Object
{
	protected:
		bool m_bRunThrough;
	public:
		bool M_bIsOver();
		Explosion(HINSTANCE hInstance, int posX, int posY);
		~Explosion();

};

#endif