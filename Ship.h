#include "stdafx.h"

#ifndef SHIP_H
#define SHIP_H
#include "Shot.h"
#include "Moveable.h"
//Abstract Class for Ships
class Ship : public Moveable
{
	protected:
		int m_nType;//Player Type: 0, Alien Types : 1 normal, 2 fast Shooter, 3 slow shooter, 4 mothership
		bool m_bShot;
		int m_nShipID;
	public:
		Shot M_bShoot(HINSTANCE hInstance, int posX, int posY, bool up);
		bool M_bCheckShot();
		int M_nCheckID();
		void M_bReload(bool re);
		~Ship();
};

#endif