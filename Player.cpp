#include "Player.h"

Player::Player(int ID, int KeyLeft, int KeyRight, int KeyShoot, int KeyStart)
{
	this->m_nPlayerID = ID;
	this->m_nLife = 3;
	this->m_nScore = 0;
	this->m_nKeyLeft = KeyLeft;
	this->m_nKeyRight = KeyRight;
	this->m_nKeyShoot = KeyShoot;
	this->m_nKeyStart = KeyStart;
}

Player::~Player()
{

}

int Player::M_nGetKey(char key)
{
	switch (key)
	{
	case 'l': return this->m_nKeyLeft;

	case 'r': return this->m_nKeyRight;

	case 's': return this->m_nKeyShoot;

	case 'p': return this->m_nKeyStart;

	default: return false;
	}
}

int Player::M_nGetPlayerID()
{
	return this->m_nPlayerID;
}

int Player::M_nGetLife()
{
	return this->m_nLife;
}

void Player::M_nSetlife(int life)
{
	this->m_nLife += life;
}

bool Player::M_bSetScore(int points)
{
	this->m_nScore = this->m_nScore + points;
	return true;
}

int Player::M_nGetScore()
{
	return this->m_nScore;
}
