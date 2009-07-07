// BnWGo!.cpp : Entry point of the application
/*
Compiled with Dev-C++ 	4.9.9.2
Compiler Options: 		None
Linker Options:     	-lconio

*/

/*
   Copyright (C) 1992, 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002,
   2005, 2006 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/



//Custom Headers
#include "system.h"         //This file includes several system headers
#include "BnWGlobal.h"      //This file MUST go ahead of any user-define headers
#include "BnWGo!.h"         
#include "BnWDisplay.h"
#include "BnWSpecial.h"


QiP QPInit(QiP QP)
{
	int i,j;
	for (i=0; i<WIDTH; i++)
	{
		for (j=0;j<HEIGHT;j++)
		{
			QP.Q[i][j]=0;
		}
	}
	QP.Q[(int)WIDTH/2-1][(int)HEIGHT/2-1]=1;
	QP.Q[(int)WIDTH/2][(int)HEIGHT/2-1]=2;
	QP.Q[(int)WIDTH/2-1][(int)HEIGHT/2]=2;
	QP.Q[(int)WIDTH/2][(int)HEIGHT/2]=1;
	return QP;
}


int SwapUsr(int NP)
{
	if (NP == 1)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}


void VStep(int NP)
{
	if (NP == 1)
	{
		P1.PS++;
	}
	else
	{
		P2.PS++;
	}
}


int NoPlace(Pl P1, Pl P2, int EP)
{
	if (EP != 0) return -1;
	if (P1.PO > P2.PO)
	{
		return 1;
	}
	if (P2.PO > P1.PO)
	{
		return 2;
	}
	if (P1.PO == P2.PO)
	{
		return 3;
	}
	return -1;
}


void Win(Pl P1, Pl P2, int NP, int EP, int WP)
{
	if (NP == -1) return;
	if (NP == 1)
	{
		MessageBox(NULL,TEXT("Player 1 Win!"),TEXT("BnWGo!"),MB_OK+MB_ICONASTERISK);
	}
	if (NP == 2)
	{
		MessageBox(NULL,TEXT("Player 2 Win!"),TEXT("BnWGo!"),MB_OK+MB_ICONASTERISK);
	}
	if (NP == 3)
	{
		MessageBox(NULL,TEXT("DRAW Game!"),TEXT("BnWGo!"),MB_OK+MB_ICONASTERISK);
	}
	clrscr();
	DrawWinInf(P1,P2,NP,EP,WP);
}


int main(int argc, char* argv[])
{
	int nRetCode = 0;
	int NP=0;
    bool EndOfGame=false;
    char KP=' ';
	int EP;
	srand ( time(NULL) );


	P1.PO =0; P2.PO =0;
	P1.PS =0; P2.PO =0;
	Cu.X = (int)WIDTH/2-1; Cu.Y =(int)HEIGHT/2-1;

	cout << "Welcome to Black'n'White GO!" << endl;
	cout << "Enter Player1 Name: ";
	scanf ("%s", &P1.PN);
	cout << "Enter Player2 Name: ";
	scanf ("%s", &P2.PN);
	cout << endl;
	cout << "Game Start!" << endl;
	getch();
	clrscr();

	NP=1;
	QP=QPInit(QP);
	QP=InitForceSpecial(QP);
	EP=CountPlace(QP);
	QPDraw(QP);
	InfDraw(P1,P2,NP,EP);
	CurDraw(Cu);


	while (EndOfGame == false)
	{
		fflush ( stdin );
		KP=getch();

		if (KP == 'W' || KP == 'w') //Move Up
		{
			if (Cu.Y > 0)
			{
				Cu.Y--;
				CurDraw(Cu);
			}
			KP=' ';
		}

		if (KP == 'S' || KP == 's') //Move Down
		{
			if (Cu.Y < HEIGHT-1)
			{
				Cu.Y++;
				CurDraw(Cu);
			}
			KP=' ';
	    }

		if (KP == 'A' || KP == 'a') //Move Left
		{
			if (Cu.X > 0)
			{
				Cu.X--;
				CurDraw(Cu);
			}
			KP=' ';
		}

		if (KP == 'D' || KP == 'd') //Move Right
		{
			if (Cu.X < WIDTH-1)
			{
				Cu.X++;
				CurDraw(Cu);
			}
			KP=' ';
	   }

	   if (KP == 'Y' || KP == 'y') //Use Special Place
	   {
            if (QP.Q[Cu.X][Cu.Y] == 3) break;
			if (NP == 1 && P1.SP > 0)
			{
				P1.SP--;
				QP.Q[Cu.X][Cu.Y]=NP;
				QP = ProcQP(QP,NP,Cu);
				VStep(NP);
				
				//Special Function
				QP = ProcQuake(QP);
				
				if (QP.S[Cu.X][Cu.Y] == 3)
				{
                     QP.S[Cu.X][Cu.Y] = 0;
                     QP = Rev(QP);
                     MessageBox (NULL,TEXT("Reversed!"),TEXT("BnWGo!"),MB_OK+MB_ICONSTOP);
                }
                
                if (QP.S[Cu.X][Cu.Y] == 2)
                {
                      QP.S[Cu.X][Cu.Y] = 0;
                      QP = Bomb(QP,Cu);
                      MessageBox (NULL,TEXT("A Bomb has just occured!"),TEXT("BnWGo!"),MB_OK+MB_ICONSTOP);
                }
                //End Of Special Function

				EP=CountPlace(QP);
				if (EP <= 0)
				{
	   				//No Places
					EndOfGame = true;
					NP=NoPlace(P1,P2,EP);
					Win(P1,P2,NP,EP,1);
				}
				NP=SwapUsr(NP);
				if (HavePlace(QP,NP) == false && P1.SP <= 0)
				{
					//Current Player No Place
					EndOfGame = true;
					NP=SwapUsr(NP);
					Win(P1,P2,NP,EP,2);
				}
				clrscr();
				QPDraw(QP);
				InfDraw(P1,P2,NP,EP);
				CurDraw(Cu);
			}
			else if (NP == 2 && P2.SP > 0)
			{
				P2.SP--;
				QP.Q[Cu.X][Cu.Y]=NP;
				QP = ProcQP(QP,NP,Cu);
				VStep(NP);
				
				//Special Function
				QP = ProcQuake(QP);
							
				if (QP.S[Cu.X][Cu.Y] == 3)
				{
                     QP.S[Cu.X][Cu.Y] = 0;
                     QP = Rev(QP);
                     MessageBox (NULL,TEXT("Reversed!"),TEXT("BnWGo!"),MB_OK+MB_ICONSTOP);
                }
                
                if (QP.S[Cu.X][Cu.Y] == 2)
                {
                      QP.S[Cu.X][Cu.Y] = 0;
                      QP = Bomb(QP,Cu);
                      MessageBox (NULL,TEXT("A Bomb has just occured!"),TEXT("BnWGo!"),MB_OK+MB_ICONSTOP);
                }
                //End Of Special Function
                
				EP=CountPlace(QP);
				if (EP <= 0)
				{
	        		//No Places
					EndOfGame = true;
					NP=NoPlace(P1,P2,EP);
					Win(P1,P2,NP,EP,1);
				}
				NP=SwapUsr(NP);
				if (HavePlace(QP,NP) == false && P2.SP <=0)
				{
					//Current Player No Place
					EndOfGame = true;
					NP=SwapUsr(NP);
					Win(P1,P2,NP,EP,2);
				}
				clrscr();
				QPDraw(QP);
				InfDraw(P1,P2,NP,EP);
				CurDraw(Cu);
			}

			KP=' ';
		}

		if (KP == 'Q' || KP == 'q') //Place
		{
			if (CanPlace(QP,NP,Cu) == true)
			{
				//Special Process
				if (QP.S[Cu.X][Cu.Y] == 1)
				{
					QP.S[Cu.X][Cu.Y] = 0;
					if (NP == 1)
					{
						P1.SP++;
						MessageBox (NULL,TEXT("Player 1 Got A Special Point: Force Place."),TEXT("BnWGo!"),MB_OK+MB_ICONINFORMATION);
					}
					if (NP == 2)
					{
						P2.SP++;
						MessageBox (NULL,TEXT("Player 2 Got A Special Point: Force Place."),TEXT("BnWGo!"),MB_OK+MB_ICONINFORMATION);
					}
				}
				
				//Place
				QP.Q[Cu.X][Cu.Y]=NP;
				QP = ProcQP(QP,NP,Cu);
				VStep(NP);
				
				//Special Function
				QP = ProcQuake(QP);

				
				if (QP.S[Cu.X][Cu.Y] == 3)
				{
                     QP.S[Cu.X][Cu.Y] = 0;
                     QP = Rev(QP);
                     MessageBox (NULL,TEXT("Reversed!"),TEXT("BnWGo!"),MB_OK+MB_ICONSTOP);
                }
                
                if (QP.S[Cu.X][Cu.Y] == 2)
                {
                      QP.S[Cu.X][Cu.Y] = 0;
                      QP = Bomb(QP,Cu);
                      MessageBox (NULL,TEXT("A Bomb has just occured!"),TEXT("BnWGo!"),MB_OK+MB_ICONSTOP);
                }
	            // End Of Special Function
	            
				EP=CountPlace(QP);
				if (EP <= 0)
				{
					//No Places
					EndOfGame = true;
					NP=NoPlace(P1,P2,EP);
					Win(P1,P2,NP,EP,1);
				}
				NP=SwapUsr(NP);
				if (HavePlace(QP,NP) == false)
				{
					//Current Player No Place
					//Special Check
					if ((NP == 1 && P1.SP <=0) || (NP == 2 && P2.SP<=0))
					{
					EndOfGame = true;
					NP=SwapUsr(NP);
					Win(P1,P2,NP,EP,2);
					}
				}
				clrscr();
				QPDraw(QP);
				InfDraw(P1,P2,NP,EP);
				CurDraw(Cu);
			}
			KP=' ';
		}

		if (KP == 'O' || KP == 'o') //Give Up
		{
			if (NP == 1)
			{
				if (MessageBox(NULL,TEXT("Do Player 1 Confirm Give Up?"),TEXT("BnWGo!"),MB_OKCANCEL + MB_ICONQUESTION) == IDOK)
				{
					//Give Up Current Player
					EndOfGame = true;
					NP=SwapUsr(NP);
					EP=CountPlace(QP);
					Win(P1,P2,NP,EP,3);
				}
			}
			else
			{
				if (MessageBox(NULL,TEXT("Do Player 2 Confirm Give Up?"),TEXT("BnWGo!"),MB_OKCANCEL + MB_ICONQUESTION) == IDOK)
				{
					//Give Up Current Player
					EndOfGame = true;
					NP=SwapUsr(NP);
					EP=CountPlace(QP);
					Win(P1,P2,NP,EP,3);
				}
			}
		KP=' ';
		}

		if (KP == 'M' || KP == 'm')  //Queue Draw
		{
			if (NP == 1)
			{
				if (MessageBox(NULL,TEXT("Do Player 1 Want to Draw?"),TEXT("BnWGo!"),MB_OKCANCEL + MB_ICONQUESTION) == IDOK)
				{
					if (MessageBox(NULL,TEXT("Do Player 2 Agree to Draw?"),TEXT("BnWGo!"),MB_OKCANCEL + MB_ICONQUESTION) == IDOK)
					{
						EndOfGame = true;
						EP=CountPlace(QP);
						NP=3;
						Win(P1,P2,NP,EP,4);
					}
					else
					{
						MessageBox(NULL,TEXT("Player 2 Disagree to Draw,Game Continue."),TEXT("BnWGo!"),MB_OK + MB_ICONEXCLAMATION);
					}
				}
			}
			else
			{
				if (MessageBox(NULL,TEXT("Do Player 2 Want to Draw?"),TEXT("BnWGo!"),MB_OKCANCEL + MB_ICONQUESTION) == IDOK)
				{
					if (MessageBox(NULL,TEXT("Do Player 1 Agree to Draw?"),TEXT("BnWGo!"),MB_OKCANCEL + MB_ICONQUESTION) == IDOK)
					{
						EndOfGame = true;
						EP=CountPlace(QP);
						NP=3;
						Win(P1,P2,NP,EP,4);
					}
					else
					{
						MessageBox(NULL,TEXT("Player 1 Disagree to Draw,Game Continue."),TEXT("BnWGo!"),MB_OK + MB_ICONEXCLAMATION);
					}
				}
			}
			KP=' ';
		}

	}
	getch();
	return nRetCode;
}
