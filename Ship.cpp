#include "Ship.h"

Shot Ship::M_bShoot(HINSTANCE hInstance, int posX, int posY, bool up)
{
	int SDir;
	if(up)SDir=0;
	else SDir=this->M_nGetObjectHeight();
	Shot madeShot(posX + (this->M_nGetObjectWidth()/2), posY + SDir, hInstance, this->m_nShipID, this->m_nType, up);
	this->m_bShot = false;
	return madeShot;
}

int Ship::M_nCheckID()
{
	return this->m_nShipID;
}

bool Ship::M_bCheckShot()
{
	return this->m_bShot;
}

void Ship::M_bReload(bool re)
{
	this->m_bShot= re;
}

Ship::~Ship()
{

}