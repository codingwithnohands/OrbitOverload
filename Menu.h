#include "stdafx.h"

#ifndef MENU_H
#define MENU_H

#include "LogicLoops.h"
#include "Switch.h"
#include <functional>

class Menu : public LogicLoops
{
	protected:
		std::multimap<unsigned int, std::string, std::greater<unsigned int>> Highscore;
		std::vector<Switch> Button;
		int scorebuffer[2];
		std::string m_sName;
		int m_nMenuState;
		HBITMAP m_hLogo;
		
	public:
		void M_PaintLogo(HDC *BufferDC, HDC *TargetDC);
		void M_PaintObjects(HDC *BufferDC, HDC *TargetDC);
		void M_LoadHighscore();
		bool M_bPaintHS(HDC *BufferDC);
		void M_SaveHighscore();
		int M_nGetPlayers();
		int M_nGetBest();
		int M_bShotCollision();
		int M_nGetMenuState();
		void M_nSetMenuState(int state);
		void M_ReceiveScore(int score1, int score2);
		bool M_bEnterScore();
		void M_PaintInput(HDC *BufferDC);
		void M_AnimateObjects();
		RECT M_GetRect();
		Menu(HINSTANCE hInstance, RECT recWnd);
		~Menu();
};

#endif