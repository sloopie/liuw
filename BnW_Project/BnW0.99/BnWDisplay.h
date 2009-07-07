//BnWDisplay.h : Display Library


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



void QPDraw(QiP QP)
{
	int i,j;
	for (j=0;j<20;j++)
	{
		for (i=0;i<20;i++)
		{
			cout << QP.Q[i][j] << " ";
		}
		cout << j << endl;
	}

	for (i=0;i<20;i++)
	{
		if (i<10)
		{
			cout << i << " ";
		}
		else
		{
			cout << i;
		}
	}
	cout << endl;
}

void InfDraw(Pl P1, Pl P2, int NP,int EP)
{
	cout << endl;
	cout << "Now Player " << NP << " Turn , Empty Places: " << EP << endl;
	cout << "Player 1:" << P1.PN << " ,Step: " << P1.PS << " ,Now own " << P1.PO << " Places." << "Special Point: " << P1.SP << " ." << endl;
	cout << "Player 2:" << P2.PN << " ,Step: " << P2.PS << " ,Now own " << P2.PO << " Places." << "Special Point: " << P2.SP << " .";//<< endl;
}
void CurDraw(Cur Cu)
{
	gotoxy(Cu.X*2+1 , Cu.Y+1);
}

void DrawWinInf(Pl P1, Pl P2, int NP,int EP,int WP)
{
	if (WP == -1) return;
	int PP=0;
	
	if (NP == 1)
	{
		PP=2;
	}
	if (NP == 2)
	{
		PP=1;
	}

	if (WP == 1) 
	{
		cout << "Game End Due To: All places is Full!" << endl;
	}
	if (WP == 2)
	{
		cout << "Game End Due To: Player " << PP << " Have No Place to Put!" << endl;
	}
	if (WP == 3)
	{
		cout << "Game End Due To: Player " << PP << " Give Up!" << endl;
	}
	if (WP == 4)
	{
		cout << "Game End Due To: Both Player Agree To End Game in DRAW!" << endl;
	}
	if (WP == 5)
	{
		cout << "Game End Due To: Program ERROR!" << endl;
	}
	
	if (WP != 4 &&  NP != 3)
	{
	cout << "Player " << NP << " Win!" << endl;
	}
	if (NP == 3 || WP == 4)
	{
		cout << "DRAW Game!" << endl;
	}
	cout << "Player 1:" << P1.PN << " ,Step: " << P1.PS << " ,Own " << P1.PO << " Places." << endl;
	cout << "Player 2:" << P2.PN << " ,Step: " << P2.PS << " ,Own " << P2.PO << " Places." << endl;
	cout << "Press Any Key to Exit..." << endl;
}

