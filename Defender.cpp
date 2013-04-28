#include "Defender.h"

Defender::Defender(HINSTANCE hInstance, RECT pos, int speed, int SID, int PID)
{
	this->m_nType = 0;
	this->m_nShipID = SID;
	this->m_nPlayerID = PID;
	switch(this->m_nPlayerID)
	{
	case 1:
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DR_08), IMAGE_BITMAP, 0, 0, 0);
		break;
	case 2:
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_DB_08), IMAGE_BITMAP, 0, 0, 0);
		break;
	}
	this->m_nCurFrame = 0;
	this->m_nPosX = pos.right/2 - this->M_nGetObjectWidth()/2;
	this->m_nPosY = pos.bottom - (this->M_nGetObjectHeight() + 5);
	this->m_nSpeed = speed;
	this->m_bShot = true;
	this->health = 1;
}

Defender::~Defender()
{

}

int Defender::M_nGetPlayerID()
{
	return this->m_nPlayerID;
}