#include "stdafx.h"

#ifndef POPUP_H
#define POPUP_H
#include "Object.h"

//Class for Point Popups
class Popup : public Object
{
	protected:
		int m_nPoints;
	public:
		bool M_bIsOver();
		int M_nGetPoints();
		Popup(int posX, int posY, int points);
		~Popup();

};

#endif