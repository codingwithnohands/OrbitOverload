#include "Switch.h"

int Switch::M_nGetType()
{
	return this->m_nType;
}

Switch::Switch(HINSTANCE hInstance, RECT pos, int type)
{	
	this->m_nType = type;
	switch(this->m_nType)
	{
	case 1:
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_START), IMAGE_BITMAP, 0, 0, 0);
		break;
	case 2:
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_SCORE), IMAGE_BITMAP, 0, 0, 0);
		break;
	case 3:
		this->m_hFrame[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[2] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[3] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[4] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[5] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[6] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		this->m_hFrame[7] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BUTTON_EXIT), IMAGE_BITMAP, 0, 0, 0);
		break;
	}
	
	this->m_nCurFrame = 0;
	this->m_nPosX = ((pos.right/4)*type) - (this->M_nGetObjectWidth()/2);
	this->m_nPosY = pos.top + (((pos.bottom/5)*4) - (this->M_nGetObjectHeight()/2));
	
}

Switch::~Switch()
{

}