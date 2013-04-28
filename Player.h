#include "stdafx.h"
#ifndef PLAYER_H
#define PLAYER_H 

//Basic Class for Player Controls
class Player
{
public:
	int M_nGetKey(char key);
	int M_nGetPlayerID();
	int M_nGetLife();
	void M_nSetlife(int life);
	bool M_bSetScore(int points);
	int M_nGetScore();
	Player(int ID, int KeyLeft, int KeyRight, int KeyShoot, int KeyStart);
	~Player();

protected:
	int m_nPlayerID;
	int m_nLife;
	int m_nScore;
	int m_nKeyLeft;
	int m_nKeyRight;
	int m_nKeyShoot;
	int m_nKeyStart;
};

#endif