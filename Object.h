#include "stdafx.h"
#ifndef OBJECT_H
#define OBJECT_H 


//Basic Class for IngameObjects
class Object
{
	protected:
		int m_nPosX;
		int m_nPosY;
		int m_nCurFrame;
		HBITMAP m_hFrame[8];
	public:
		bool M_bPrint(HDC BufferDC, HDC TargetDC);
		void M_bSetFrame();
		RECT M_bGetRect();
		int M_nGetObjectHeight();
		int M_nGetObjectWidth();
		int M_bGetPosX();
		int M_bGetPosY();
		~Object();
};

#endif