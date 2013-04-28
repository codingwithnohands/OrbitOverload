#include "Game.h"

Game::Game(HINSTANCE hInstance, RECT m_grWnd, unsigned int score, unsigned int Players)
{
	this->m_recWnd = m_grWnd;
	this->m_recWnd.top += 80;
	this->M_nbufferCounter = 5;
	this->m_nMax = score;
	this->m_nTurn = 1;
	this->m_hBg = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BG), IMAGE_BITMAP, 0, 0, 0);
	this->m_hHUD[0] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_HUD_C), IMAGE_BITMAP, 0, 0, 0);
	this->m_hHUD[1] = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_HUD), IMAGE_BITMAP, 0, 0, 0);
	this->M_InitGame(hInstance, this->m_nTurn);
	this->m_nMDirection = 1;

		Player p_X(1, 0x41, 0x44, VK_SPACE, VK_F1);
		this->pNr.push_back(p_X);
	if(Players == 2)
	{
		Player p_X(2, VK_LEFT, VK_RIGHT, VK_UP, VK_F2);
		this->pNr.push_back(p_X);
	}
	
	for(std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
	{
		Defender def(hInstance, this->m_recWnd, 5, c->M_nGetPlayerID(), c->M_nGetPlayerID());
		this->Human.push_back(def);
	}

	

	for(int i = 0;i<3;i++)
	{
		for(int x = 0; x<13;x++)
		{
			for(int y = 0; y<5;y++)
			{
				Shield barricade(hInstance, ( (this->m_recWnd.right/4) * (i+1) ) + ( ((x+1)*8) - ( (13*8)/2 ) ), (this->m_recWnd.bottom - 120) + ( ((y+1)*8) - ((5*8)/2) ) );
				if(x == 0 && y == 0)
				{
					this->Shields[i].top = barricade.M_bGetRect().top;
					this->Shields[i].left = barricade.M_bGetRect().left;
				}
				else if(x == 12 && y == 4)
				{
					this->Shields[i].bottom = barricade.M_bGetRect().bottom;
					this->Shields[i].right = barricade.M_bGetRect().right;
				}
				this->Barr.push_back(barricade);
			}
		}
		
	}

}

void Game::M_InitGame(HINSTANCE hInstance, int turn)
{
	this->g_bMove = false;
	this->g_cDirection = true;
	float speed = (float)1.0 + (float)(turn * 0.5);
	for (int y=0; y < 1; y++)
	{
		for(int i=0; i < 11; i++)
		{
			Alien EnemyInstance(hInstance, this->m_recWnd, i, y, rand(), (int)speed, 2);
			this->Enemy.push_back(EnemyInstance);
		}
	}
	for (int y=1; y < 3; y++)
	{
		for(int i=0; i < 11; i++)
		{
			Alien EnemyInstance(hInstance, this->m_recWnd, i, y, rand(), (int)speed, 3);
			this->Enemy.push_back(EnemyInstance);
		}
	}
	for (int y=3; y < 5; y++)
	{
		for(int i=0; i < 11; i++)
		{
			Alien EnemyInstance(hInstance, this->m_recWnd, i, y, rand(), (int)speed, 1);
			this->Enemy.push_back(EnemyInstance);
		}
	}
}

Game::~Game()
{

}

void Game::M_MoveAliens()
{
	if(Mother.size() != 0)
	{
		Mother.begin()->M_MoveHorizontal(this->m_nMDirection);
		if(Mother.begin()->M_bGetPosX() >= this->m_recWnd.right || Mother.begin()->M_bGetRect().right <= this->m_recWnd.left )
		{
			Mother.clear();
			this->m_nMDirection *= -1;
		}
	}
	if(this->g_bMove)
	{
		for(std::vector<Alien>::iterator a = this->Enemy.begin(); a != this->Enemy.end(); a++)
		{
			a->M_bMoveRow();
		}
		this->g_bMove = false;
	}
	if(this->g_cDirection)
	{
		for(std::vector<Alien>::iterator a = this->Enemy.begin(); a != this->Enemy.end(); a++)
		{
			a->M_MoveHorizontal(1);
		}
	}
	else
	{
		for(std::vector<Alien>::iterator a = this->Enemy.begin(); a != this->Enemy.end(); a++)
		{
			a->M_MoveHorizontal(-1);
		}
	}
	for(std::vector<Alien>::iterator a = this->Enemy.begin(); a != this->Enemy.end(); a++)
	{
		if(a->M_bGetPosX() <= this->m_recWnd.left)
		{
			this->g_bMove = true;
			this->g_cDirection = true;
			break;
		}
		else if(a->M_bGetRect().right >= this->m_recWnd.right)
		{
			this->g_bMove = true;
			this->g_cDirection = false;
			break;
		}
	}
}

void Game::M_GenerateMothership(HINSTANCE hInstance)
{
	if (Mother.size() == 0 && (rand() % 300) == 1)
	{
		int x;
		if(this->m_nMDirection == 1)x = this->m_recWnd.left - 50;
		else x = this->m_recWnd.right;
		Alien EnemyInstance(hInstance, this->m_recWnd, x, 0, rand(), this->m_nTurn, 4);
		this->Mother.push_back(EnemyInstance);
	}
}

void Game::M_ShootAliens(HINSTANCE hInstance)
{
	for(std::vector<Alien>::iterator a = this->Enemy.begin(); a != this->Enemy.end(); a++)
	{
		if(a->M_bCheckShot())
		{
			bool check = true;
			for(std::vector<Alien>::iterator c = a; c != this->Enemy.end(); c++)
			{
 				if(a->M_bGetPosX() == c->M_bGetPosX() && a->M_bGetPosY() != c->M_bGetPosY())
				{
					check = false;
					break;
				}
			}
			if(check && (rand()%320) == 1 )
			{
				this->Fired.push_back(a->M_bShoot(hInstance, a->M_bGetPosX(), a->M_bGetPosY(), false));
			}
		}
	}
}

void Game::M_EraseVolatiles()
{
	if(this->Boom.size() != 0)
	{
		std::vector<Explosion>::iterator b = this->Boom.begin();
		while(b != this->Boom.end())
		{
			if(b->M_bIsOver())b = this->Boom.erase(b); 
			else b++;
		}
	}
	if(this->Text.size() != 0)
	{
		std::vector<Popup>::iterator t = this->Text.begin();
		while(t != this->Text.end())
		{
			if(t->M_bIsOver())t = this->Text.erase(t); 
			else t++;
		}
	}
}

void Game::M_PaintObjects(HDC *BufferDC, HDC *TargetDC)
{
	//Print Defenders
	for(std::vector<Defender>::iterator p = this->Human.begin(); p != this->Human.end(); p++)
	{
		p->M_bPrint(*BufferDC, *TargetDC);
	}
	//Print Shields
	for(std::vector<Shield>::iterator w = this->Barr.begin(); w != this->Barr.end(); w++)
	{
		w->M_bPrint(*BufferDC, *TargetDC);
	}
	//Print Aliens
	for(std::vector<Alien>::iterator a = this->Enemy.begin(); a != this->Enemy.end(); a++)
	{
		a->M_bPrint(*BufferDC, *TargetDC);
	}
	if(Mother.size()!= 0)Mother.begin()->M_bPrint(*BufferDC, *TargetDC);
	//Print Shots
	for(std::vector<Shot>::iterator s = this->Fired.begin(); s != this->Fired.end(); s++)
	{
		s->M_bPrint(*BufferDC, *TargetDC);
	}
	//Print Explosions
	this->M_EraseVolatiles();
	for(std::vector<Explosion>::iterator b = this->Boom.begin(); b != this->Boom.end(); b++)
	{
		b->M_bPrint(*BufferDC, *TargetDC);
	}
	
}

void Game::M_ShipCollision(HINSTANCE hInstance)
{
	std::vector<Alien>::iterator a = this->Enemy.begin();
	while(a != this->Enemy.end())
	{
		//Check for Shield Collide
		bool bShieldCollide = false;
		if(this->M_bCollide(a->M_bGetRect(),this->Shields[0]) || this->M_bCollide(a->M_bGetRect(),this->Shields[1]) || this->M_bCollide(a->M_bGetRect(),this->Shields[2]) )
		{
			std::vector<Shield>::iterator w = this->Barr.begin();
			while(w != Barr.end())
			{
				if(this->M_bCollide(a->M_bGetRect(),w->M_bGetRect()))
				{
					if(w->M_bHit())
					{
						w = this->Barr.erase(w);
						Explosion bam(hInstance, w->M_bGetPosX(), w->M_bGetPosY());
						this->Boom.push_back(bam);
					}
					if(a->M_bHit())
					{
						a = this->Enemy.erase(a);
						Explosion bam(hInstance, a->M_bGetPosX(), a->M_bGetPosY());
						this->Boom.push_back(bam);
						bShieldCollide = true;
					}
					break;
				}
				else
				w++;
			}
		}
		if(bShieldCollide)break;
		//Check for Defender Collide
		std::vector<Defender>::iterator p = this->Human.begin();
		while (p!= this->Human.end())
		{
			if(this->M_bCollide(a->M_bGetRect(),p->M_bGetRect()))
			{
				for (std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
				{
					if(c->M_nGetPlayerID() == p->M_nGetPlayerID())
					c->M_nSetlife(-1);
					Explosion bam(hInstance, p->M_bGetPosX(), p->M_bGetPosY());
					this->Boom.push_back(bam);
				}
				
				p = this->Human.erase(p);
				if(a->M_bHit())
				{
					a = this->Enemy.erase(a);
					bShieldCollide = true;
					Explosion bam(hInstance, a->M_bGetPosX(), a->M_bGetPosY());
					this->Boom.push_back(bam);
				}
				break;
			}
			else
			p++;
		}
		if(!bShieldCollide)a++;
	}
}

void Game::M_ShotCollision(HINSTANCE hInstance)
{
	std::vector<Shot>::iterator s = this->Fired.begin();
	while(s != this->Fired.end())
	{
		bool bShotErased = false;
		std::vector<Defender>::iterator p = this->Human.begin();
		while(p != this->Human.end() && this->Human.size() != 0)
		{
			bool bPlayerErased = false;
			//Check if Shot OOR -> Player
			if(p->M_nCheckID() == s->M_bCollide(this->m_recWnd))
			{
				s = this->Fired.erase(s);
				bShotErased=true;
				p->M_bReload(true);
				break;
			}
			std::vector<Alien>::iterator a = this->Enemy.begin();
			while(a != this->Enemy.end() && this->Enemy.size() != 0)
			{
				//Check for Shield Hit 1
				if(this->M_bCollide(s->M_bGetRect(),this->Shields[0]) || this->M_bCollide(s->M_bGetRect(),this->Shields[1]) || this->M_bCollide(s->M_bGetRect(),this->Shields[2]) )
				{
					std::vector<Shield>::iterator w = this->Barr.begin();
					while(w != Barr.end())
					{
						if(this->M_bCollide(s->M_bGetRect(), w->M_bGetRect()))
						{
							if(s->M_nCheckID() == a->M_nCheckID())
							{
								a->M_bReload(true);
							}
							else if(s->M_nCheckID() == 1 || s->M_nCheckID() == 2)
							{
								for(std::vector<Defender>::iterator p2 = this->Human.begin(); p2 != this->Human.end(); p2++)
								{
									if(s->M_nCheckID() == p2->M_nGetPlayerID())
									{
										p2->M_bReload(true);
										break;
									}
								}
							}
							s = this->Fired.erase(s);
							bShotErased=true;
							if(w->M_bHit())
							{
								w = this->Barr.erase(w);
								break;
							}
						}
						w++;
					}
					if(bShotErased)break;
				}
				//Mothership Hit
				if(this->Mother.size()!=0)
				{
					if(this->M_bCollide(s->M_bGetRect(),this->Mother.begin()->M_bGetRect()) && this->Mother.begin()->M_nCheckID() != s->M_nCheckID())
					{
						std::vector<Player>::iterator c = this->pNr.begin();
						while(c != this->pNr.end())
						{
               				if(c->M_nGetPlayerID() == s->M_nCheckID())
							{
   								break;	
							}
							c++;
						}
						for(std::vector<Defender>::iterator p2 = this->Human.begin(); p2 != this->Human.end(); p2++)
						{
							if(c->M_nGetPlayerID() == p2->M_nGetPlayerID())
							{
								p2->M_bReload(true);
								break;
							}
						}
						if(this->Mother.begin()->M_bHit())
						{
							c->M_bSetScore(this->Mother.begin()->M_nDestroy());
							Popup plopp(this->Mother.begin()->M_bGetPosX(), this->Mother.begin()->M_bGetPosY(), this->Mother.begin()->M_nDestroy());
							this->Text.push_back(plopp);
							Explosion bam(hInstance, this->Mother.begin()->M_bGetPosX(), this->Mother.begin()->M_bGetPosY());
							this->Boom.push_back(bam);
							
							this->Mother.erase(this->Mother.begin());
						}
						s = this->Fired.erase(s);
						bShotErased=true;
						break;
					}
				}
				//Check if Shot OOR -> Alien
				if(a->M_nCheckID() == s->M_bCollide(this->m_recWnd))
				{
					s = this->Fired.erase(s);
					bShotErased=true;
					a->M_bReload(true);
					break;
				}
				//Check for Player Hit -> Alien(alive)
				else if(this->M_bCollide(s->M_bGetRect(),p->M_bGetRect()) && p->M_nCheckID() != s->M_nCheckID() && a->M_nCheckID() == s->M_nCheckID())
				{
					s = this->Fired.erase(s);
					bShotErased=true;
					a->M_bReload(true);
					for (std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
					{
						if(c->M_nGetPlayerID() == p->M_nGetPlayerID())
						c->M_nSetlife(-1);
					}
					Explosion bam(hInstance, p->M_bGetPosX(), p->M_bGetPosY());
					this->Boom.push_back(bam);
					p = this->Human.erase(p);
					bPlayerErased=true;
					break;
				}
				//Check for Player Hit -> Alien(dead)
				else if(this->M_bCollide(s->M_bGetRect(),p->M_bGetRect()) && s->M_nCheckID() != 1 && s->M_nCheckID() != 2)
				{
					s = this->Fired.erase(s);
					bShotErased=true;
					for (std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
					{
						if(c->M_nGetPlayerID() == p->M_nGetPlayerID())
						c->M_nSetlife(-1);
					}
					Explosion bam(hInstance, p->M_bGetPosX(), p->M_bGetPosY());
					this->Boom.push_back(bam);
					p = this->Human.erase(p);
					bPlayerErased=true;
					break;
				}
				//Check for Alien Hit
				else if(this->M_bCollide(s->M_bGetRect(),a->M_bGetRect()) && a->M_nCheckID() != s->M_nCheckID())
				{
 					std::vector<Player>::iterator c = this->pNr.begin();
					while(c != this->pNr.end())
					{
               			if(c->M_nGetPlayerID() == s->M_nCheckID())
						{
   							break;	
						}
						c++;
					}
					for(std::vector<Defender>::iterator p2 = this->Human.begin(); p2 != this->Human.end(); p2++)
					{
						if(c->M_nGetPlayerID() == p2->M_nGetPlayerID())
						{
							p2->M_bReload(true);
							break;
						}
					}
					if(a->M_bHit())
					{
						c->M_bSetScore(a->M_nDestroy());
						Popup plopp(a->M_bGetPosX(), a->M_bGetPosY(), a->M_nDestroy());
						this->Text.push_back(plopp);
						Explosion bam(hInstance, a->M_bGetPosX(), a->M_bGetPosY());
						this->Boom.push_back(bam);
						a = this->Enemy.erase(a);
					}
					s = this->Fired.erase(s);
					bShotErased=true;
					break;
				}
				a++;
			}
			if(bShotErased || bPlayerErased)
			{
				break;
			}
			//Check if Shot OOR -> orphan
			if(!bShotErased && s->M_bCollide(this->m_recWnd) != -1 && s->M_nCheckID() != 1 && s->M_nCheckID() != 2)
			{
				s = this->Fired.erase(s);
				bShotErased=true;
				break;
			}
			p++;
		}
		if(!bShotErased)
		{
			s++;
		}
	}
}

void Game::M_AnimateObjects()
{
	if(this->m_nbufferCounter*0.2 == (int)(this->m_nbufferCounter*0.2))
	{
		for(std::vector<Alien>::iterator a = this->Enemy.begin(); a!= this->Enemy.end(); a++)
		{
			a->M_bSetFrame();
		}
		for(std::vector<Defender>::iterator p = this->Human.begin(); p!= this->Human.end(); p++)
		{
			p->M_bSetFrame();
		}
		if(!this->Mother.empty())this->Mother.begin()->M_bSetFrame();
	}
	if(this->m_nbufferCounter*0.5 == (int)(this->m_nbufferCounter*0.5))
	{
		for(std::vector<Popup>::iterator t = this->Text.begin(); t != this->Text.end(); t++)
		{
			t->M_bSetFrame();
		}
		for(std::vector<Explosion>::iterator b = this->Boom.begin(); b != this->Boom.end(); b++)
		{
			b->M_bSetFrame();
		}
	}
	if(this->m_nbufferCounter*0.1 == (int)(this->m_nbufferCounter*0.1))
	{
		for(std::vector<Shot>::iterator s = this->Fired.begin(); s != this->Fired.end(); s++)
		{
			s->M_bSetFrame();
		}
	}
	this->m_nbufferCounter = (this->m_nbufferCounter + 1)%11;
}

bool Game::M_bCheckForDeadPlayer()
{
	bool ship = true;
	for(std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
	{
		if(c->M_nGetLife() > 0)
		{
				ship=false;
		}
		else if(this->Human.size() == 0)
		{
			ship = true;
		}
		else
		{
			ship = false;
		}
	}
	return ship;
}

bool Game::M_bCheckForEnemySuccess()
{
	std::vector<Alien>::iterator a = this->Enemy.begin();
	while(a != this->Enemy.end())
	{
		if((a->M_bGetPosY() + a->M_nGetObjectHeight()) >= this->m_recWnd.bottom)
		{
			return true;
		}
		else a++;
	}
	return false;
}

bool Game::M_bCheckForPlayerSuccess()
{
	if(this->Enemy.begin() == this->Enemy.end())
	{
		return true;
	}
	return false;
}

void Game::M_PaintHUD(HDC *BufferDC, HDC *TargetDC)
{
	HDC VisualDC = CreateCompatibleDC(*TargetDC);
	int i = 0;
	if(this->pNr.size() == 2) i = 1;
	SelectObject(VisualDC, this->m_hHUD[i]);
	TransparentBlt(*BufferDC, 0, 0, this->m_recWnd.right, 80, VisualDC, 0, 0, 900, 80, RGB(255,0,220));
	DeleteObject(VisualDC);
	HFONT myFont = CreateFont(18,10,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH, "Larabiefont Free");   
	SelectObject(*BufferDC, myFont);
	SetBkMode(*BufferDC, TRANSPARENT);
	SetTextColor(*BufferDC, RGB(0,0,0));
	int Players=1;
	std::ostringstream ss;
	std::string buff;
	ss << this->m_nMax;
	buff = "000000000";
	buff.replace(buff.end()-ss.str().length(),buff.end(),ss.str());
	TextOut(*BufferDC,((int)((this->m_recWnd.right)*0.5) - 45),0,"Highscore",9);
	TextOut(*BufferDC,((int)((this->m_recWnd.right)*0.5) - ((buff.length()*10)/2)),18,buff.c_str(),buff.length()); 
	for(std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
	{
		if(Players == 1)
		{
			LPCSTR Buffer;
			std::string s;
			std::stringstream out;

			out << "Player " << Players;
			s = out.str();
			Buffer = (LPCSTR)s.c_str();
			TextOut(*BufferDC,10,8,Buffer,s.length());

			out.str("");
			out.clear();
			s.clear();
			out << "Life " << c->M_nGetLife();
			s = out.str();
			Buffer = (LPCSTR)s.c_str();
			TextOut(*BufferDC,10,27,Buffer,s.length());
	
			out.str("");
			out.clear();
			s.clear();
			out << "Score " << c->M_nGetScore();
			s = out.str();
			Buffer = (LPCSTR)s.c_str();
			TextOut(*BufferDC,10,45,Buffer,s.length());
		}
		else if(Players == 2)
		{
			LPCSTR Buffer;
			std::string s;
			std::stringstream out;

			out << "Player " << Players;
			s = out.str();
			Buffer = (LPCSTR)s.c_str();
			TextOut(*BufferDC,this->m_recWnd.right - (((s.length())*10)+10),8,Buffer,s.length());

			out.str("");
			out.clear();
			s.clear();
			out << c->M_nGetLife() << " Life";
			s = out.str();
			Buffer = (LPCSTR)s.c_str();
			TextOut(*BufferDC,this->m_recWnd.right-(((s.length())*10)+10),27,Buffer,s.length());
	
			out.str("");
			out.clear();
			s.clear();
			out << c->M_nGetScore() << "  " << "Score";
			s = out.str();
			Buffer = (LPCSTR)s.c_str();
			TextOut(*BufferDC,this->m_recWnd.right-(((s.length())*10)+10),45,Buffer,s.length());
		}
		Players++;
	}
	//Print Points
	for(std::vector<Popup>::iterator t = this->Text.begin(); t != this->Text.end(); t++)
	{
		HFONT myFont2 = CreateFont(12,6,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH, "Larabiefont Free");   
		SelectObject(*BufferDC, myFont2);
		SetBkMode(*BufferDC, TRANSPARENT);
		SetTextColor(*BufferDC, RGB(255,255,255));
		std::ostringstream ss2;
		std::string buff2;
		ss2 << t->M_nGetPoints();
		buff2 = ss2.str();
		TextOut(*BufferDC,t->M_bGetPosX(),t->M_bGetPosY(),buff2.c_str(),buff2.length());
		DeleteObject(myFont2);
	}
	DeleteObject(myFont);
}

int Game::M_nGetScore(int player)
{
	if(player == 2)
	{
		if(this->pNr.size() ==2)
		{
		std::vector<Player>::iterator c = this->pNr.begin();
		c++;
		return c->M_nGetScore();
		}
		else return -1;
	}
	else
	{
		std::vector<Player>::iterator c = this->pNr.begin();
		return c->M_nGetScore();
	}
}

int Game::M_nGetTurn()
{
	this->m_nTurn++;
	return this->m_nTurn;
}