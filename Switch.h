#include "stdafx.h"

#ifndef SWITCH_H
#define SWITCH_H
#include "Object.h"
//Class for Buttons
class Switch : public Object
{
	protected:
		int m_nType;
	public:
		int M_nGetType();
		Switch(HINSTANCE hInstance, RECT pos, int posX);
		~Switch();
		int M_nCheckID();
};

#endif