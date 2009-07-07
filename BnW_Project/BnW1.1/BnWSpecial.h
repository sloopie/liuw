//BnWGo! Special Function Header

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

int GeneRnd(int P);
int Revi(int P);

QiP InitForceSpecial(QiP QP)
{
	int i=0;
	int j=0;
	for (i=0;i<WIDTH;i++)
	{
		for (j=0;j<HEIGHT;j++)
		{
            if (GeneRnd(SPEP) == 1)
            {
            	QP.S[i][j]=1;
            }
            if (GeneRnd(BOMBP) == 1)
            {
            	QP.S[i][j]=2;
            }
            if (GeneRnd(REVP) == 1)
            {
             	QP.S[i][j]=3;
            }
		}
	}
	return QP;
}

QiP ProcQuake(QiP QP)
{
    int i=0;
    int j=0;
    if (GeneRnd(QUAKEP) == 1)
    {
		for (i=0;i<WIDTH;i++)
		{
        	for (j=0;j<HEIGHT;j++)
            	{
                	if (QP.Q[i][j] != 0)
                    	{
                        	if (GeneRnd(QUAKEQ) == 1)
                            {
                            	QP.Q[i][j] = 0;
                        	}
                        }
                }
        }
    	MessageBox(NULL,TEXT("Quake Occured!"),TEXT("BnWGo!"),MB_ICONWARNING+MB_OK);
     }
     return QP;
}

QiP Rev(QiP QP)
{
    int i=0;
    int j=0;
    for (i=0;i<WIDTH;i++)
    {
        for (j=0;j<HEIGHT;j++)
        {
            if (QP.Q[i][j] != 0)
            {
               QP.Q[i][j]=Revi(QP.Q[i][j]);
            }
        }
    }
    return QP;
}

QiP Bomb(QiP QP,Cur PO)
{
    int X=PO.X;
    int Y=PO.Y;
    if (X > 1)
    {
           QP.Q[X-1][Y]=0;
    }
    if (X < WIDTH-1)
    {
           QP.Q[X+1][Y]=0;
    }
    if (Y > 1)
    {
           QP.Q[X][Y-1]=0;
    }
    if (Y < HEIGHT-1)
    {
           QP.Q[X][Y+1]=0;
    }
    if (X > 1 && Y > 1)
    {
           QP.Q[X-1][Y-1]=0;
    }
    if (X > 1 && Y < HEIGHT-1)
    {
           QP.Q[X-1][Y+1]=0;
    }
    if (X < WIDTH-1 && Y > 1)
    {
           QP.Q[X+1][Y-1]=0;
    }
    if (X < WIDTH-1 && Y < HEIGHT -1)
    {
           QP.Q[X+1][Y+1]=0;      
    }
    QP.Q[X][Y]=3;
    return QP;
}
                         
int GeneRnd(int P)
{
	int tmp;
	//_sleep(2);
	tmp = rand() % 100;
	if ( tmp <= P )
	{
		return 1;
	}
	return 0;
}

int Revi(int P)
{
    if (P == 1)
    {
          return 2;
    }
    else if (P == 2)
    {
          return 1;
    }
    else
    {
          return P;
    }
}
