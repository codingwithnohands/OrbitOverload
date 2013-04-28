
#include "LogicLoops.h"

bool LogicLoops::M_bMovePlayer(HINSTANCE hInstance)
{
	for(std::vector<Player>::iterator c = this->pNr.begin(); c != this->pNr.end(); c++)
	{
		bool bPauseCheck = false;
		if ((GetAsyncKeyState(c->M_nGetKey('p'))) && this->Human.size() < 2 && c->M_nGetLife() != 0)
		{
			if(this->Human.size() == 0)
			{
 			Defender def(hInstance, this->m_recWnd, 3, c->M_nGetPlayerID(), c->M_nGetPlayerID());
			this->Human.push_back(def);
			bPauseCheck = true;
			}
			else
			{
				for(std::vector<Defender>::iterator n = this->Human.begin();n != this->Human.end(); n++)
				{
					bool check = true;
					if(n->M_nGetPlayerID() == c->M_nGetPlayerID())
					{
						check = false;
					}
					if(check)
					{
						Defender def(hInstance, this->m_recWnd, 3, c->M_nGetPlayerID(), c->M_nGetPlayerID());
						this->Human.push_back(def);
						bPauseCheck = true;
					}
				}
			}
		}
		bool check = false;
		std::vector<Defender>::iterator p;
		for(std::vector<Defender>::iterator n = this->Human.begin();n != this->Human.end(); n++)
		{
			if(c->M_nGetPlayerID() == n->M_nGetPlayerID())
			{
				p = n; 
				check = false;
				break;
			}
			else check = true;
		}
		if(!check)
		{
			if ((GetAsyncKeyState(c->M_nGetKey('p')))&& c->M_nGetPlayerID() == p->M_nGetPlayerID() && !bPauseCheck)
			{
				return false;
			}
			if(this->Human.begin() != this->Human.end())
			{
				if(c->M_nGetPlayerID() == p->M_nGetPlayerID())
				{
					if (GetAsyncKeyState(c->M_nGetKey('l')) && p->M_bGetPosX() > this->m_recWnd.left)
					{
						p->M_MoveHorizontal(-1);
					}
					if (GetAsyncKeyState(c->M_nGetKey('r')) && p->M_bGetPosX() < this->m_recWnd.right-p->M_nGetObjectWidth())
					{
						p->M_MoveHorizontal(1);
					}
					if (GetAsyncKeyState(c->M_nGetKey('s')) && p->M_bCheckShot())
					{
						this->Fired.push_back(p->M_bShoot(hInstance, p->M_bGetPosX(), p->M_bGetPosY(), true));
					}
				}
			}
		}
		
	}
	if(this->pNr.size() == 1 && GetAsyncKeyState(VK_F2))
	{
		Player p_X(2, VK_LEFT, VK_RIGHT, VK_UP, VK_F2);
		this->pNr.push_back(p_X);
		Defender def(hInstance, this->m_recWnd, 3, 2, 2);
		this->Human.push_back(def);
	}
	return true;
}

void LogicLoops::M_PaintToScreen(HDC *TargetDC, HDC *BufferDC, HBITMAP *BufferBMP)
{
	BITMAP BitmapData;
	GetObject(*BufferBMP, sizeof(BitmapData), &BitmapData);
	BitBlt(*TargetDC, 0, 0, BitmapData.bmWidth, BitmapData.bmHeight, *BufferDC, 0, 0, SRCCOPY);
	Sleep(30);
}

void LogicLoops::M_PaintBackground(HDC *BufferDC, HDC *TargetDC)
{
	HDC VisualDC = CreateCompatibleDC(*TargetDC);
	SelectObject(VisualDC, this->m_hBg);
	BitBlt(*BufferDC, 0, 0, this->m_recWnd.right, this->m_recWnd.bottom, VisualDC, 0, 0, SRCCOPY);
	DeleteObject(VisualDC);
}

void LogicLoops::M_MoveShots()
{
	for(std::vector<Shot>::iterator s = this->Fired.begin(); s != this->Fired.end(); s++)
		{
			if(s->M_bGetPosY() >= this->m_recWnd.top && s->M_bGetPosY() <= this->m_recWnd.bottom)s->M_MoveVertical();
		}
}

bool LogicLoops::M_bCollide(RECT ent1, RECT ent2)
{
	if( 
		( 
		(ent1.bottom <=  ent2.bottom  && ent1.bottom >= ent2.top) 
		|| 
		(ent1.top <=  ent2.bottom  && ent1.top >= ent2.top) 
		) 
		&& 
		( 
		(ent1.right <=  ent2.right  && ent1.right >= ent2.left) 
		|| 
		(ent1.left <=  ent2.right  && ent1.left >= ent2.left) 
		) 
		)
	{
		return true;
	}
	return false;
}