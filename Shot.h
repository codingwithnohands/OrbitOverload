#include "stdafx.h"
#ifndef SHOT_H
#define SHOT_H 

#include "Moveable.h"
//#include "Ship.h"
//Basic Class for Shots
class Shot : public Moveable
{
protected:
	int m_nType;
public:
	int M_bCollide(bool bound);
	int M_bCollide(RECT m_grWnd);
	int M_nCheckID();
	Shot(int posX,int posY, HINSTANCE hInstance, int nShotID, int type, bool up);
	~Shot();

protected:
	int m_nShotID;
};

#endif