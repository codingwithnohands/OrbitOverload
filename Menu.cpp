#include "Menu.h"

void Menu::M_PaintLogo(HDC *BufferDC, HDC *TargetDC)
{
	HDC VisualDC = CreateCompatibleDC(*TargetDC);
	BITMAP BitmapData;
	GetObject(this->m_hLogo, sizeof(BitmapData), &BitmapData);
	SelectObject(VisualDC, this->m_hLogo);
	TransparentBlt(*BufferDC, (int)((this->m_recWnd.right/2)-(BitmapData.bmWidth*0.5)), 100, (int)((this->m_recWnd.right/2)), (int)BitmapData.bmHeight, VisualDC, 0, 0,(int) BitmapData.bmWidth,(int)BitmapData.bmHeight, RGB(255,0,220));
	DeleteObject(VisualDC);
}

void Menu::M_PaintObjects(HDC *BufferDC, HDC *TargetDC)
{
	//Print Defenders
	for(std::vector<Defender>::iterator p = this->Human.begin(); p != this->Human.end(); p++)
	{
		p->M_bPrint(*BufferDC, *TargetDC);
	}
	//Print Shots
	for(std::vector<Shot>::iterator s = this->Fired.begin(); s != this->Fired.end(); s++)
	{
		s->M_bPrint(*BufferDC, *TargetDC);
	}
	//Print Objects
	for(std::vector<Switch>::iterator b = this->Button.begin(); b != this->Button.end(); b++)
	{
		b->M_bPrint(*BufferDC, *TargetDC);
	}
}

void Menu::M_LoadHighscore()
{
	FILE * Filename;
	fopen_s(&Filename, "Highscore.dat","rb");

	if(Filename==NULL)
	{
		for(int i = 0; i < 5; i++)
		{
			std::pair<unsigned int, std::string> entry;
			entry.first = 0;
			entry.second = "EMPTY";
			this->Highscore.insert(entry);
		}
	}
	else
	{
		int i = 0;
		while( i < 5)
		{
			std::pair<unsigned int, std::string> entry;
			fread (&entry.first, 1, sizeof(entry.first), Filename );
			fread (&entry.second, 1, sizeof(entry.second), Filename );
			this->Highscore.insert(entry);
			i++;
		}
		fclose (Filename);
	}
    
}

int Menu::M_bShotCollision()
{
	int value = 0;
	std::vector<Shot>::iterator s = this->Fired.begin();
	while(s != this->Fired.end())
	{
		bool bShotErased = false;
		std::vector<Defender>::iterator p = this->Human.begin();
		while(p != this->Human.end() && this->Human.size() != 0)
		{
			//Check if Shot OOR -> Player
			if(p->M_nCheckID() == s->M_bCollide(this->m_recWnd))
			{
				s = this->Fired.erase(s);
				bShotErased=true;
				p->M_bReload(true);
				break;
			}
			std::vector<Switch>::iterator a = this->Button.begin();
			while(a != this->Button.end())
			{
				//Check for Button Hit
				if(s->M_bCollide(this->M_bCollide(s->M_bGetRect(), a->M_bGetRect())))
				{
					for(std::vector<Defender>::iterator p2 = this->Human.begin(); p2 != this->Human.end(); p2++)
					{
						if(s->M_nCheckID() == p2->M_nCheckID())
						{
							p2->M_bReload(true);
							break;
						}
					}
					s = this->Fired.erase(s);
					return a->M_nGetType();
				}
				a++;
			}
			if(bShotErased)
			{
				break;
			}
			p++;
		}
		if(!bShotErased)
		{
			s++;
		}
	}
	return value;
}

void Menu::M_AnimateObjects()
{
	if(this->m_nbufferCounter*0.5 == (int)(this->m_nbufferCounter*0.5))
	{
		for(std::vector<Switch>::iterator b = this->Button.begin(); b!= this->Button.end(); b++)
		{
			b->M_bSetFrame();
		}
		for(std::vector<Defender>::iterator p = this->Human.begin(); p!= this->Human.end(); p++)
		{
			p->M_bSetFrame();
		}
	}
	if(this->m_nbufferCounter*0.2 == (int)(this->m_nbufferCounter*0.2))
	{
		for(std::vector<Shot>::iterator s = this->Fired.begin(); s != this->Fired.end(); s++)
		{
			s->M_bSetFrame();
		}
	}
	this->m_nbufferCounter = (this->m_nbufferCounter + 1)%21;
}

void Menu::M_SaveHighscore()
{
	FILE * Filename;
	fopen_s(&Filename, "Highscore.dat", "wb");

	assert(Filename != NULL);

	for(std::multimap<unsigned int, std::string, std::greater <unsigned int>>::iterator it_s = this->Highscore.begin(); it_s != this->Highscore.end(); it_s++)
	{
		fwrite (&it_s->first, 1, sizeof(it_s->first), Filename );
		fwrite (&it_s->second, 1, sizeof(it_s->second), Filename );
	}
    fclose (Filename);
}

int Menu::M_nGetBest()
{
	return this->Highscore.begin()->first;
}

RECT Menu::M_GetRect()
{
	return this->m_recWnd;
}

int Menu::M_nGetMenuState()
{
	return this->m_nMenuState;
}

int Menu::M_nGetPlayers()
{
	return this->pNr.size();
}

void Menu::M_nSetMenuState(int state)
{
	this->m_nMenuState = state;
}

bool Menu::M_bPaintHS(HDC *BufferDC)
{
	HFONT myFont = CreateFont(40,20,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH, "Larabiefont Free");   
	SelectObject(*BufferDC, myFont);
	SetBkMode(*BufferDC, TRANSPARENT);
	SetTextColor(*BufferDC, RGB(255,255,255));
	std::multimap<unsigned int, std::string, std::greater <unsigned int>>::iterator h = this->Highscore.begin();
	for(int i = 0; i<5; i++)
	{
		std::ostringstream ss;
		std::string buff;
		ss << h->first;
		std::string buff2 = ss.str();
		buff = "000000000";
		buff.replace(buff.end()-buff2.length(),buff.end(),buff2);
		TextOut(*BufferDC,((int)((this->m_recWnd.right)*0.5) - (int)((21*h->second.length())+40) ), 250 + i*40, h->second.c_str(),h->second.length());
		TextOut(*BufferDC,((int)((this->m_recWnd.right)*0.5) + 40 ), 250 + i*40, buff.c_str(),buff.length());
		h++;
	}
	
	DeleteObject(myFont);
	return true;
}

void Menu::M_ReceiveScore(int score1, int score2)
{
	this->scorebuffer[0] = score1;
	if(score2 != -1)this->scorebuffer[1]=score2;
}

bool Menu::M_bEnterScore()
{
	if(this->scorebuffer[0] == NULL && this->scorebuffer[1] == NULL)
	{
		return false;
	}
	if(this->m_sName.length() < 9)
	{
		if(HIWORD(GetKeyState(0x41))){this->m_sName.append("A"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x42))){this->m_sName.append("B"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x43))){this->m_sName.append("C"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x44))){this->m_sName.append("D"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x45))){this->m_sName.append("E"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x46))){this->m_sName.append("F"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x47))){this->m_sName.append("G"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x48))){this->m_sName.append("H"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x49))){this->m_sName.append("I"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x4A))){this->m_sName.append("J"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x4B))){this->m_sName.append("K"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x4C))){this->m_sName.append("L"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x4D))){this->m_sName.append("M"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x4E))){this->m_sName.append("N"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x4F))){this->m_sName.append("O"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x50))){this->m_sName.append("P"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x51))){this->m_sName.append("Q"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x52))){this->m_sName.append("R"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x53))){this->m_sName.append("S"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x54))){this->m_sName.append("T"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x55))){this->m_sName.append("U"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x56))){this->m_sName.append("V"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x57))){this->m_sName.append("W"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x58))){this->m_sName.append("X"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x59))){this->m_sName.append("Y"); Sleep(20);}
		else if(HIWORD(GetKeyState(0x5A))){this->m_sName.append("Z"); Sleep(20);}
	}
	if(HIWORD(GetKeyState(VK_BACK)) && this->m_sName.length() != 0){this->m_sName.erase(this->m_sName.length()-1);}
	else if(HIWORD(GetKeyState(VK_RETURN)))
	{
		if(this->scorebuffer[0] != NULL)
		{
			std::pair<unsigned int, std::string> entry;
			entry.first = this->scorebuffer[0];
			entry.second = this->m_sName;
			this->Highscore.insert(entry);
			this->scorebuffer[0] = NULL;
			this->m_sName.clear();
			if(this->Highscore.size() > 5)
			{
				std::multimap<unsigned int, std::string, std::greater <unsigned int>>::iterator it_s = this->Highscore.end();
				it_s--;
				this->Highscore.erase(it_s);
			}
			this->M_SaveHighscore();
		}
		else if(this->scorebuffer[1] != NULL)
		{
			std::pair<unsigned int, std::string> entry;
			entry.first = this->scorebuffer[1];
			entry.second = this->m_sName;
			this->Highscore.insert(entry);
			this->scorebuffer[1] = NULL;
			this->m_sName.clear();
			if(this->Highscore.size() > 5)
			{
				std::multimap<unsigned int, std::string, std::greater <unsigned int>>::iterator it_s = this->Highscore.end();
				it_s--;
				this->Highscore.erase(it_s);
			}
			this->M_SaveHighscore();
		}
	}
	Sleep(50);
	return true;
}

void Menu::M_PaintInput(HDC *BufferDC)
{
	HFONT myFont = CreateFont(40,20,0,0,FW_BOLD,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,CLEARTYPE_QUALITY, VARIABLE_PITCH, "Larabiefont Free");   
	SelectObject(*BufferDC, myFont);
	SetBkMode(*BufferDC, TRANSPARENT);
	SetTextColor(*BufferDC, RGB(255,255,255));
	
	std::ostringstream ss;
	std::string buff;
	std::string txt;
	if(this->scorebuffer[0] != NULL)txt = "Please Enter Your Name Player One";
	else if(this->scorebuffer[1] != NULL)txt = "Please Enter Your Name Player Two";
	ss << this->m_sName;
	buff = this->m_sName;
	TextOut(*BufferDC,((int)((this->m_recWnd.right)*0.5) - (int)((21*txt.length())/2) ), this->m_recWnd.bottom/2 - 20, txt.c_str(),txt.length());
	if(this->m_nbufferCounter*0.1 == (int)(this->m_nbufferCounter*0.1))
	{buff.append("|"); TextOut(*BufferDC,((int)((this->m_recWnd.right)*0.5) - (((buff.length()-1)*21)/2)), this->m_recWnd.bottom/2 + 30, buff.c_str(),buff.length());}
	else TextOut(*BufferDC,((int)((this->m_recWnd.right)*0.5) - (int)((buff.length()*21)/2)), this->m_recWnd.bottom/2 + 30, buff.c_str(),buff.length());
	
	DeleteObject(myFont);
}

Menu::Menu(HINSTANCE hInstance, RECT m_grWnd)
{
	this->m_nMenuState = 0; // States 0:Menu, 1:Paused, 2:Game, 3:Highscore, 31: Highscore Paused
	this->m_recWnd = m_grWnd;
	this->m_hBg = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_BG), IMAGE_BITMAP, 0, 0, 0);
	this->m_hLogo = (HBITMAP)LoadImage(hInstance, MAKEINTRESOURCE(IDB_LOGO), IMAGE_BITMAP, 0, 0, 0);
	this->m_nbufferCounter = 10;
	this->scorebuffer[0] = NULL;
	this->scorebuffer[1] = NULL;

	for (int i=1; i<= 3; i++)
	{
	Switch but(hInstance, this->m_recWnd, i);
	this->Button.push_back(but);
	}

    Player p_X(1, 0x41, 0x44, VK_SPACE, VK_F1);
	this->pNr.push_back(p_X);

	this->M_LoadHighscore();

	for(std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
	{
		Defender def(hInstance, this->m_recWnd, 5, rand(), c->M_nGetPlayerID());
		this->Human.push_back(def);
	}
	
}

Menu::~Menu()
{

}