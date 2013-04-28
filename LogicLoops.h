#include "stdafx.h"

#ifndef LOGICLOOPS_H
#define LOGICLOOPS_H

#include "Player.h"
#include "Defender.h"
#include "Shot.h"

class LogicLoops
{
	protected:
		HBITMAP m_hBg;
		std::vector<Player> pNr;
		std::vector<Defender> Human;
		std::vector<Shot> Fired;
		RECT m_recWnd;
		int m_nbufferCounter;
		
	public:
		void M_MoveShots();
		bool M_bCollide(RECT ent1, RECT ent2);
		virtual void M_PaintObjects(HDC *BufferDC, HDC *TargetDC) = 0;
		bool M_bMovePlayer(HINSTANCE hInstance);
		void M_PaintBackground(HDC *BufferDC, HDC *TargetDC);
		virtual void M_AnimateObjects() = 0;
		void M_PaintToScreen(HDC *TargetDC, HDC *BufferDC, HBITMAP *BufferBMP);
		

};

#endif