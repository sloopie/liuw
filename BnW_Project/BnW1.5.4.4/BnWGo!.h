//BnWGo!.h : this file must be included in BnWDisplay.h


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


struct Pl {
	char PN[50];
	int PS;
	int PO;
	int SP;
}P1, P2;

struct Cur {
	int X;
	int Y;
}Cu, PP;

struct QiP {
	int Q[WIDTH][HEIGHT];
	int S[WIDTH][HEIGHT];
}QP;

struct Dint {
	int X;
	int Y;
}NFound={-1,-1};

//Find Locate Function
//Tested OK!
int FindLeft(QiP QP,int P,Cur PP)
{
	int i=PP.X;i--;
	int j=PP.Y;
	while (i>=0)
	{
		if (QP.Q[i][j] == P)
		{
			return i;
		}
		if (QP.Q[i][j] == 0)
		{
			return -1;
		}
		i--;
	}
	return -1;
}

int FindRight(QiP QP,int P,Cur PP)
{
	int i=PP.X;i++;
	int j=PP.Y;
	while (i<WIDTH)
	{
		if (QP.Q[i][j] == P)
		{
			return i;
		}
		if (QP.Q[i][j] == 0)
		{
			return -1;
		}
		i++;
	}
	return -1;
}

int FindUp(QiP QP,int P,Cur PP)
{
	int i=PP.X;
	int j=PP.Y;j--;
	while (j>=0)
	{
		if (QP.Q[i][j] == P)
		{
			return j;
		}
		if (QP.Q[i][j] == 0)
		{
			return -1;
		}
		j--;
	}
	return -1;
}

int FindDown(QiP QP,int P,Cur PP)
{
	int i=PP.X;
	int j=PP.Y;j++;
	while (j<HEIGHT)
	{
		if (QP.Q[i][j] == P)
		{
			return j;
		}
		if (QP.Q[i][j] == 0)
		{
			return -1;
		}
		j++;
	}
	return -1;
}
//

//Find Double Axis
Dint FindLeftUp(QiP QP,int P,Cur PP)
{
	int i=PP.X;i--;
	int j=PP.Y;j--;
	Dint t;
	while (i>=0 && j>=0)
	{
		if (QP.Q[i][j] == P)
		{
			t.X=i;
			t.Y=j;
			return t;
		}
		if (QP.Q[i][j] == 0)
		{
			return NFound;
		}
		i--;
		j--;
	}
	return NFound;
}

Dint FindRightUp(QiP QP,int P,Cur PP)
{
	int i=PP.X;i++;
	int j=PP.Y;j--;
	Dint t;
	while (i<WIDTH && j>=0)
	{
		if (QP.Q[i][j] == P)
		{
			t.X=i;
			t.Y=j;
			return t;
		}
		if (QP.Q[i][j] == 0)
		{
			return NFound;
		}
		i++;
		j--;
	}
	return NFound;
}

Dint FindLeftDown(QiP QP,int P,Cur PP)
{
	int i=PP.X;i--;
	int j=PP.Y;j++;
	Dint t;
	while (i>=0 && j<HEIGHT)
	{
		if (QP.Q[i][j] == P)
		{
			t.X=i;
			t.Y=j;
			return t;
		}
		if (QP.Q[i][j] == 0)
		{
			return NFound;
		}
		i--;
		j++;
	}
	return NFound;
}

Dint FindRightDown(QiP QP,int P,Cur PP)
{
	int i=PP.X;i++;
	int j=PP.Y;j++;
	Dint t;
	while (i<WIDTH && j<HEIGHT)
	{
		if (QP.Q[i][j] == P)
		{
			t.X=i;
			t.Y=j;
			return t;
		}
		if (QP.Q[i][j] == 0)
		{
			return NFound;
		}
		i++;
		j++;
	}
	return NFound;
}
//

//Change Range Function
QiP ChgLeft(QiP QP,int P,Cur PP,int Lf)
{
	int i=PP.X;
	int j=PP.Y;
	QiP TM=QP;
	int k;
	if (P == -1) return QP;
	for (k=Lf;k<=i;k++)
	{
		TM.Q[k][j]=P;
	}
	return TM;
}

QiP ChgRight(QiP QP,int P,Cur PP,int Rf)
{
	int i=PP.X;
	int j=PP.Y;
	QiP TM=QP;
	int k;
	if (P == -1) return QP;
	for (k=i;k<=Rf;k++)
	{
		TM.Q[k][j]=P;
	}
	return TM;
}

QiP ChgUp(QiP QP,int P,Cur PP,int Uf)
{
	int i=PP.X;
	int j=PP.Y;
	QiP TM=QP;
	int k;
	if (P == -1) return QP;
	for (k=Uf;k<=j;k++)
	{
		TM.Q[i][k]=P;
	}
	return TM;
}

QiP ChgDown(QiP QP,int P,Cur PP,int Df)
{
	int i=PP.X;
	int j=PP.Y;
	QiP TM=QP;
	int k;
	if (P == -1) return QP;
	for (k=j;k<=Df;k++)
	{
		TM.Q[i][k]=P;
	}
	return TM;
}
//

//Change Range Function Double Axis
QiP ChgLeftUp(QiP QP,int P,Cur PP,Dint LUf)
{
	int i=PP.X;i--;
	int j=PP.Y;j--;
	QiP TM=QP;
	if (P == -1) return QP;
	while (i>=LUf.X && j >=LUf.Y)
	{
		TM.Q[i][j]=P;
		if (i<=0 || j<=0) return TM;
		i--;
		j--;
	}
	return TM;
}

QiP ChgLeftDown(QiP QP,int P,Cur PP,Dint LDf)
{
	int i=PP.X;i--;
	int j=PP.Y;j++;
	QiP TM=QP;
	if (P == -1) return QP;
	while (i>=LDf.X && j <=LDf.Y)
	{
		TM.Q[i][j]=P;
		if (i<=0 || j>=HEIGHT-1) return TM;
		i--;
		j++;
	}
	return TM;
}

QiP ChgRightUp(QiP QP,int P,Cur PP,Dint RUf)
{
	int i=PP.X;i++;
	int j=PP.Y;j--;
	QiP TM=QP;
	if (P == -1) return QP;
	while (i<=RUf.X && j >=RUf.Y)
	{
		TM.Q[i][j]=P;
		if (i>=WIDTH-1 || j<=0) return TM;
		i++;
		j--;
	}
	return TM;
}

QiP ChgRightDown(QiP QP,int P,Cur PP,Dint RDf)
{
	int i=PP.X;i++;
	int j=PP.Y;j++;
	QiP TM=QP;
	if (P == -1) return QP;
	while (i<=RDf.X && j <= RDf.Y)
	{
		TM.Q[i][j]=P;
		if (i>=WIDTH-1 || j>=HEIGHT-1) return TM;
		i++;
		j++;
	}
	return TM;
}

//

//Count Places
int CountP(QiP QP,int P)
{
	int i;
	int j;
	int k=0;
	QiP TM=QP;
	for (i=0;i<=19;i++)
	{
		for (j=0;j<=19;j++)
		{
			if (TM.Q[i][j] == P) {k++;}
		}
	}
	return k;
}



//All in One Process
QiP ProcQP(QiP QP,int P,Cur PP)
{
	int i=PP.X;
	int j=PP.Y;
	QiP TM=QP;
	
	//Left
	int FL=FindLeft(QP,P,PP);
	if (FL != -1)
	{
		TM = ChgLeft(TM,P,PP,FL);
	}


	//Right
	int FR=FindRight(QP,P,PP);
	if (FR != -1)
	{
		TM = ChgRight(TM,P,PP,FR);
	}

	//Up
	int FU=FindUp(QP,P,PP);
	if (FU != -1)
	{
		TM = ChgUp(TM,P,PP,FU);
	}

	//Down
	int FD=FindDown(QP,P,PP);
	if (FD != -1)
	{
		TM = ChgDown(TM,P,PP,FD);
	}

	//LeftUp
	Dint LUf=FindLeftUp(QP,P,PP);
	if (LUf.X != -1 && LUf.Y !=-1)
	{
		TM = ChgLeftUp(TM,P,PP,LUf);
	}

	//LeftDown
	Dint LDf=FindLeftDown(QP,P,PP);
	if (LDf.X != -1 && LDf.Y != -1)
	{
		TM = ChgLeftDown(TM,P,PP,LDf);
	}

	//RightUp
	Dint RUf=FindRightUp(QP,P,PP);
	if (RUf.X != -1 && RUf.Y != -1)
	{
		TM = ChgRightUp(TM,P,PP,RUf);
	}

	//RightDown
	Dint RDf=FindRightDown(QP,P,PP);
	if (RDf.X != -1 && RDf.Y != -1)
	{
		TM = ChgRightDown(TM,P,PP,RDf);
	}

	return TM;
}

//Vaildate Place to Put
bool CanPlace(QiP QP,int P,Cur PP)
{
	int i=PP.X;
	int j=PP.Y;
	
	if (QP.Q[i][j] != 0)
	{
		return false;
	}

	//Left
	int FL=FindLeft(QP,P,PP);
	if (FL != -1 && FL != (i-1))
	{
		return true;
	}

	//Right
	int FR=FindRight(QP,P,PP);
	if (FR != -1 && FR != (i+1))
	{
		return true;
	}

	//Up
	int FU=FindUp(QP,P,PP);
	if (FU != -1 && FU != (j-1))
	{
		return true;
	}

	//Down
	int FD=FindDown(QP,P,PP);
	if (FD != -1 && FD != (j+1))
	{
		return true;
	}
	
	//LeftUp
	Dint LUf=FindLeftUp(QP,P,PP);
	if ((LUf.X != -1 && LUf.Y != -1) && (LUf.X != (i-1) && LUf.Y != (j-1)))
	{
		return true;
	}

	//RightUp
	Dint RUf=FindRightUp(QP,P,PP);
	if ((RUf.X != -1 && RUf.Y != -1) && (RUf.X != (i+1) && RUf.Y != (j-1)))
	{
		return true;
	}

	//LeftDown
	Dint LDf=FindLeftDown(QP,P,PP);
	if ((LDf.X != -1 && LDf.Y != -1) && (LDf.X != (i-1) && LDf.Y != (j+1)))
	{
		return true;
	}

	//RightDown
	Dint RDf=FindRightDown(QP,P,PP);
	if ((RDf.X != -1 && RDf.Y != -1) && (RDf.X != (i+1) && RDf.Y != (j+1)))
	{
		return true;
	}

return false;
}

//Count Place
int CountPlace(QiP QP)
{
	int i,j;
	int k=0;
	P1.PO=0;
	P2.PO=0;
	for (j=0;j<HEIGHT;j++)
	{
		for (i=0;i<WIDTH;i++)
		{
			if (QP.Q[i][j] == 1)
			{
				P1.PO++;
			}
			if (QP.Q[i][j] == 2)
			{
				P2.PO++;
			}
			if (QP.Q[i][j] == 0)
			{
				k++;
			}
		}
	}
	return k;
}

bool HavePlace(QiP QP,int NP)
{
	Cur TS;
	for (TS.X=0;TS.X<WIDTH;TS.X++)
	{
		for (TS.Y=0;TS.Y<HEIGHT;TS.Y++)
		{
			if (CanPlace(QP,NP,TS) == true)
			{
				return true;
			}
		}
	}
	return false;
}
