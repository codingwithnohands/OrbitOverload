#include "stdafx.h"
#ifndef MOVEABLE_H
#define MOVEABLE_H

#include "Object.h"
//Sub-Class for Objects that can move
class Moveable :public Object
{
	protected:
		int m_nSpeed;
	public:
		void M_MoveHorizontal(int mod);
		void M_MoveVertical();
		Moveable();
		~Moveable();
};

#endif