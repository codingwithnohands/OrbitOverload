#include "Alien.h"

Alien::Alien(HINSTANCE hInstance, RECT pos, int posX, int posY, int ID, int speed, int type)
{
	this->m_nShipID = ID;
	this->m_nType = type;
	this->m_nCurFrame = 0;
	if(this->m_nType == 1)
	{
		this->health = 1;
		this->m_nPoints = 10;
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_1_08), IMAGE_BITMAP, 0, 0, 0);
	}
	else if(this->m_nType == 2)
	{
		this->health = 2;
		this->m_nPoints = 20;
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_2_08), IMAGE_BITMAP, 0, 0, 0);
	}
	else if(this->m_nType == 3)
	{
		this->health = 1;
		this->m_nPoints = 15;
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_ALIEN_3_08), IMAGE_BITMAP, 0, 0, 0);
	}
	else if(this->m_nType == 4)
	{
		this->health = 1;
		this->m_nPoints = 100 - (rand()%51);
		speed *= 2;
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_MOTHER_08), IMAGE_BITMAP, 0, 0, 0);
	}

	if(this->m_nType == 4)
	{
		this->m_nPosX = posX;
		this->m_nPosY = pos.top;
	}
	else
	{
		this->m_nPosX = pos.left + 10 + ((this->M_nGetObjectWidth() + 10)* posX);
		this->m_nPosY = pos.top + 50 + ((this->M_nGetObjectHeight() + 10)* posY);
	}
	this->m_nSpeed = 0;
	this->m_nSpeed = this->m_nSpeed + speed;
	this->m_bShot = true;
}

Alien::~Alien()
{

}

bool Alien::M_bMoveRow()
{
	this->m_nPosY = this->m_nPosY + (this->M_nGetObjectHeight()/2) + 10;

	return true;
}