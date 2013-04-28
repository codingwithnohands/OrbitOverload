#include "stdafx.h"


#ifndef DEFENDER_H
#define DEFENDER_H
//#include "Object.h"
#include "Destructible.h"
#include "Ship.h"
//Basic Class for Defender
class Defender : public Destructible, public Ship
{
	protected:
		int m_nPlayerID;
	public:
		bool M_bDestroy();
		int M_nGetPlayerID();
		Defender(HINSTANCE hInstance, RECT pos, int speed, int SID, int PID);
		~Defender();
};

#endif