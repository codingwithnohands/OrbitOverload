#include "shot.h"
#include "Defender.h"

int Shot::M_bCollide(bool bound)
{
	if(bound)
	{
		return -1;
	}
	return 0;
}

int Shot::M_bCollide(RECT m_grWnd)
{
	if(m_grWnd.bottom <= this->m_nPosY || this->m_nPosY <= m_grWnd.top)
	{
		return this->m_nShotID;
	}
	else return -1;
}

int Shot::M_nCheckID()
{
	return this->m_nShotID;
}

Shot::Shot(int posX,int posY, HINSTANCE hInstance, int nShotID, int type, bool up)
{
	float mult = 1;
	PlaySound(TEXT("Laser.wav"),NULL,SND_FILENAME | SND_ASYNC);
	this->m_nShotID = nShotID;
	this->m_nPosX= posX;
	this->m_nPosY= posY;
	this->m_nCurFrame = 0;
	this->m_nType = type;
	if(this->m_nType == 0)
	{
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_4_04), IMAGE_BITMAP, 0, 0, 0);
	}
	else if ( this->m_nType == 1)
	{
		mult = (float)0.8;
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_1_04), IMAGE_BITMAP, 0, 0, 0);
	}
	else if ( this->m_nType == 2)
	{
		mult = (float)0.5;
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_3_08), IMAGE_BITMAP, 0, 0, 0);
	}
	else if( this->m_nType == 3)
	{
		mult = (float)1.3;
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_01), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_02), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_03), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_04), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_05), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_06), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_07), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_SHOT_2_08), IMAGE_BITMAP, 0, 0, 0);
	}
	if(up)this->m_nSpeed = (int)(10* mult);
	else this->m_nSpeed = (int)(-10* mult);
	
}

Shot::~Shot()
{

}