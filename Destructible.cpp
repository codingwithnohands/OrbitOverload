#include "Destructible.h"

bool Destructible::M_bHit()
{
	this->health = health -1;
	if(health <= 0)return true;
	return false;
}

int Destructible::M_nDestroy()
{
	return this->m_nPoints;
}

Destructible::~Destructible()
{

}