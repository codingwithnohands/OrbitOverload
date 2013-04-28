#include "Shield.h"

Shield::Shield(HINSTANCE hInstance, int posX, int posY)
{
	this->m_nPosX = posX;
	this->m_nPosY = posY;
	for(int i = 0; i<9;i++)
	{
	this->m_hFrame[i]=(HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHIELD), IMAGE_BITMAP, 0, 0, 0);
	}
	this->m_nCurFrame = 0;
	this->health = 1;
}

Shield::~Shield()
{

}