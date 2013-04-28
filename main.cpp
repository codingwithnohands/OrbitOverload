#include "stdafx.h"
#include "Game.h"
#include "Menu.h"

MSG GameLoop(HINSTANCE hInstance, HWND hWnd)
{
	srand((unsigned int)time(NULL));
	RECT Window;
	GetClientRect(hWnd,&Window);
	HDC TargetDC = GetDC(hWnd);
	HDC BufferDC = CreateCompatibleDC(NULL);
	HBITMAP BufferBMP  = CreateCompatibleBitmap(TargetDC, Window.right, Window.bottom); 
	SelectObject(BufferDC, BufferBMP);
	Menu* Menu01 = new Menu(hInstance, Window);
	std::vector<Game> Running;
	std::vector<Game>::iterator g;
	bool running = true;
	AddFontResourceEx("larabiefont free.ttf",FR_PRIVATE,NULL);
	//mciSendString("open Bgm.mp3 alias MP3 wait", 0, 0, 0 );
	//mciSendString("play MP3 from 0 repeat", 0, 0, 0 );
	
	
	// Beginne die Main Game Loop - Endlosschleife, die nur durch WM_QUIT abgebrochen wird
	MSG msg;
	while (running)
	{   
		// Verarbeite Nachrichten, die möglicherweise
		// zwischenzeitlich empfangen wurden. Falls
		// WM_QUIT empfangen wird: Game Loop abbrechen
		while (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT) return msg; 
		}
		//Erstellen von Brushes
		

		//Menü
		if(Menu01->M_nGetMenuState() == 0 || Menu01->M_nGetMenuState() == 1 || Menu01->M_nGetMenuState() == 3 ||Menu01->M_nGetMenuState() == 31)
		{
			//animationsänderung
			Menu01->M_AnimateObjects();
			//Menü zeichnen
			Menu01->M_PaintBackground(&BufferDC, &TargetDC);
			
			//Menülogik
			if(!Menu01->M_bEnterScore())
			{
				Menu01->M_PaintLogo(&BufferDC, &TargetDC);
				Menu01->M_bMovePlayer(hInstance);
				Menu01->M_MoveShots();
				switch(Menu01->M_bShotCollision())
				{
				case 1:
					if(Menu01->M_nGetMenuState() == 0 && Running.empty())
					{
						Game Game01(hInstance, Window, Menu01->M_nGetBest(), Menu01->M_nGetPlayers());
						Running.push_back(Game01);
						Menu01->M_nSetMenuState(2);
					}
					else if(Menu01->M_nGetMenuState() == 1)
					{
						Menu01->M_nSetMenuState(2);
					}
					break;

				case 2:
					if(Menu01->M_nGetMenuState() == 0)
					{
						Menu01->M_nSetMenuState(3);
					}
					else if(Menu01->M_nGetMenuState() == 1)
					{
						Menu01->M_nSetMenuState(31);
					}
					else if(Menu01->M_nGetMenuState() == 3)
					{
						Menu01->M_nSetMenuState(0);
					}
					else if(Menu01->M_nGetMenuState() == 31)
					{
						Menu01->M_nSetMenuState(1);
					}
					break;

				case 3: 
					msg.message = WM_QUIT;
					//mciSendString("close MP3",0,0,0);
					return msg;

				}
				if(Menu01->M_nGetMenuState() == 3 || Menu01->M_nGetMenuState() == 31)
				{
					Menu01->M_bPaintHS(&BufferDC);
				}
				Menu01->M_PaintObjects(&BufferDC, &TargetDC);
			}
			else
			{
				Menu01->M_PaintInput(&BufferDC);
			}
			Menu01->M_PaintToScreen(&TargetDC, &BufferDC, &BufferBMP);
		}
		//Spiel
		else if(Menu01->M_nGetMenuState() == 2)
		{
			//animationsänderung
			Running.begin()->M_AnimateObjects();
			//Spiel Logik
			
			if(!Running.begin()->M_bMovePlayer(hInstance))Menu01->M_nSetMenuState(1);
			Running.begin()->M_GenerateMothership(hInstance);
			Running.begin()->M_MoveAliens();
			Running.begin()->M_ShootAliens(hInstance);
			Running.begin()->M_MoveShots();
			Running.begin()->M_ShotCollision(hInstance);
			Running.begin()->M_ShipCollision(hInstance);
			//Spiel Zeichnen
			Running.begin()->M_PaintBackground(&BufferDC, &TargetDC);
			Running.begin()->M_PaintHUD(&BufferDC, &TargetDC);
			Running.begin()->M_PaintObjects(&BufferDC, &TargetDC);
			Running.begin()->M_PaintToScreen(&TargetDC, &BufferDC, &BufferBMP);

			//Spiel End bedingungen
			if(Running.begin()->M_bCheckForPlayerSuccess())
			{
				Running.begin()->M_InitGame(hInstance, Running.begin()->M_nGetTurn());
			}
			if(Running.begin()->M_bCheckForDeadPlayer() || Running.begin()->M_bCheckForEnemySuccess())
			{
				Menu01->M_ReceiveScore(Running.begin()->M_nGetScore(1), Running.begin()->M_nGetScore(2));
				Running.clear();
				Menu01->M_nSetMenuState(3);	
			}
		}
		
	}
	msg.message = WM_QUIT;
	return msg;
}


// Diese Funktion fängt Window Messages (WM-Nachrichten) ab, damit wir sie
// nach eigenem Bedarf verarbeiten können. Nachrichten, auf die wir nicht mit
// eigenem Code reagieren wollen, leiten wir an DefWindowProc(...) weiter
LRESULT CALLBACK WindowProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	switch(message)
	{
		
	case WM_DESTROY:			// WM_DESTROY wird von Windows geschickt, bevor es unser Applikationsfenster "zerstört":
		/* TO DO: ... */		
		PostQuitMessage(0);     // Wir melden Windows, dass wir auf die Nachricht WM_DESTROY mit einer Terminierung reagiert haben
		break;	
	
	default:					// Jede andere Nachricht an DefWindowProc (default window message processing function) weiterreichen
		return DefWindowProc(hWnd,message,wParam,lParam);

	}

	return 0;
}


void RegisterWindowClass(HINSTANCE hInstance)
{
	// Eigene Fensterklasse (window class extended) anlegen:
	// wc dazu erst mit Nullen und dann mit eigenen Einstellungen füllen
	WNDCLASSEX wc;  
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;		// Umleiten der Nachrichtenverarbeitung auf Funktion WindowProc(...)
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
	wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPICON));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
	wc.lpszClassName = "Invaders1";
	RegisterClassEx(&wc);				// Fensterklasse registrieren
}


// Hauptprogramm: Initialisiert Hauptfenster und startet die Game Loop
int WINAPI wWinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,PWSTR lpCmdLine,int nShowCmd)
{
	// Fenster an Position (10,10) mit Größe 600 * 900 erstellen:
	RegisterWindowClass(hInstance);		// Fensterklasse registrieren
	HWND hWnd;							// Handle unseres Fensters
	hWnd=CreateWindowEx(NULL,"Invaders1","Orbit Overload",WS_SYSMENU,10,10,906,800,NULL,NULL,hInstance,NULL);
	// Sichtbarkeit des Fensters entsprechend Programmaufruf schalten!
	ShowWindow(hWnd,nShowCmd);			
	// Den Inhalt des Fensters (falls sichtbar) sicherheitshalber neu zeichnen lassen
	UpdateWindow(hWnd);					

	// Main Game Loop aufrufen
	MSG msg;						    // Datenstruktur für WM-Nachrichten
	msg = GameLoop(hInstance, hWnd);

	// Programm mit wParam der Quit-Nachricht beenden
	return msg.wParam;
}

