#include "stdafx.h"
#include "Object.h"
#include "resource.h"

bool Object::M_bPrint(HDC BufferDC, HDC TargetDC)
{
	HDC VisualDC = CreateCompatibleDC(TargetDC);
	SelectObject(VisualDC, this->m_hFrame[this->m_nCurFrame]);
	TransparentBlt(BufferDC,this->m_nPosX,this->m_nPosY, this->M_nGetObjectWidth(),this->M_nGetObjectHeight(),VisualDC,0,0,this->M_nGetObjectWidth(), this->M_nGetObjectHeight(), RGB(255,0,220));
	DeleteObject(VisualDC);
	return true;
}

RECT Object::M_bGetRect()
{
	RECT pos;
	pos.left = this->m_nPosX;
	pos.right = this->m_nPosX + this->M_nGetObjectWidth();
	pos.top = this->m_nPosY;
	pos.bottom = this->m_nPosY + this->M_nGetObjectHeight();
	return pos;
}

int Object::M_bGetPosX()
{
	return this->m_nPosX;
}

int Object::M_bGetPosY()
{
	return this->m_nPosY;
}

void Object::M_bSetFrame()
{
	this->m_nCurFrame = (this->m_nCurFrame + 1)%8;
}

int Object::M_nGetObjectHeight()
{
	BITMAP BitmapData;
	GetObject(this->m_hFrame[this->m_nCurFrame], sizeof(BitmapData), &BitmapData);
	return BitmapData.bmHeight;
}

int Object::M_nGetObjectWidth()
{
	BITMAP BitmapData;
	GetObject(this->m_hFrame[this->m_nCurFrame], sizeof(BitmapData), &BitmapData);
	return BitmapData.bmWidth;
}

Object::~Object()
{

}
