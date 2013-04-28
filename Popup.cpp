#include "Popup.h"

Popup::Popup(int posX, int posY, int points)
{
	this->m_nPosX= posX;
	this->m_nPosY= posY;
	this->m_nPoints = points;
	this->m_nCurFrame = 0;
}

Popup::~Popup()
{

}

int Popup::M_nGetPoints()
{
	return this->m_nPoints;
}

bool Popup::M_bIsOver()
{
	if(this->m_nCurFrame == 5)
	return true;
	else
	return false;
}