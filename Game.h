#include "stdafx.h"

#ifndef GAME_H
#define GAME_H

#include "Alien.h"
#include "Shield.h"
#include "LogicLoops.h"
#include "Explosion.h"
#include "Popup.h"

class Game : public LogicLoops
{
	protected:
		HBITMAP m_hHUD[2];
		RECT Shields[3];
		int m_nPoints;
		int m_nTurn;
		unsigned int m_nMax;
		bool g_bMove;
		bool g_cDirection;
		int m_nMDirection;
		std::string m_sBest;
		std::vector<Alien> Enemy;
		std::vector<Shield> Barr;
		std::vector<Alien> Mother;
		std::vector<Explosion> Boom;
		std::vector<Popup> Text;
		
	public:
		void M_MoveAliens();
		void M_InitGame(HINSTANCE hInstance, int turn);
		void M_ShootAliens(HINSTANCE hInstance);
		void M_PaintHUD(HDC *BufferDC, HDC *TargetDC);
		void M_PaintObjects(HDC *BufferDC, HDC *TargetDC);
		void M_GenerateMothership(HINSTANCE hInstance);
		void M_ShipCollision(HINSTANCE hInstance);
		void M_ShotCollision(HINSTANCE hInstance);
		void M_AnimateObjects();
		bool M_bCheckForDeadPlayer();
		bool M_bCheckForEnemySuccess();
		bool M_bCheckForPlayerSuccess();
		int M_nGetTurn();
		void M_EraseVolatiles();
		int M_nGetScore(int player);
		int M_nbufferCounter;
		Game(HINSTANCE hInstance, RECT m_grWnd, unsigned int score, unsigned int Players);
		~Game();
};

#endif