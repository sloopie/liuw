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

QiP InitForceSpecial(QiP QP)
{
	int i=0;
	int j=0;
	for (i=0;i<20;i++)
	{
		for (j=0;j<20;j++)
		{
			QP.S[i][j]=GeneRnd(8);
		}
	}
	return QP;
}

int GeneRnd(int P)
{
	int tmp;
	tmp = rand() % 100;
	if ( tmp <= P )
	{
		return 1;
	}
	return 0;
}

