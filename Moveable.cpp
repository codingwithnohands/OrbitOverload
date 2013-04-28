#include "Moveable.h"

void Moveable::M_MoveHorizontal(int mod)
{
	mod = mod * this->m_nSpeed;

	this->m_nPosX = m_nPosX+mod;
}

void Moveable::M_MoveVertical()
{
	int mod = 1 * this->m_nSpeed;

	this->m_nPosY = m_nPosY-mod;
}

Moveable::Moveable()
{

}

Moveable::~Moveable()
{

}
