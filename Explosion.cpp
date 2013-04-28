#include "Explosion.h"

Explosion::Explosion(HINSTANCE hInstance, int posX, int posY)
{
	PlaySound(TEXT("Explosion.wav"),NULL,SND_FILENAME | SND_ASYNC);
	this->m_nPosX= posX;
	this->m_nPosY= posY;
	this->m_bRunThrough = false;
	this->m_nCurFrame = 0;
	this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_01), IMAGE_BITMAP, 0, 0, 0);
	this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_02), IMAGE_BITMAP, 0, 0, 0);
	this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_03), IMAGE_BITMAP, 0, 0, 0);
	this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_04), IMAGE_BITMAP, 0, 0, 0);
	this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_05), IMAGE_BITMAP, 0, 0, 0);
	this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_06), IMAGE_BITMAP, 0, 0, 0);
	this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_07), IMAGE_BITMAP, 0, 0, 0);
	this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_EXPLOSION_08), IMAGE_BITMAP, 0, 0, 0);
}

Explosion::~Explosion()
{

}

bool Explosion::M_bIsOver()
{
	if(this->m_nCurFrame == 7 && !this->m_bRunThrough)
	this->m_bRunThrough = true;
	if(this->m_nCurFrame == 0 && this->m_bRunThrough)return true;
	return false;
}