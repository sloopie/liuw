/*GuseeNum -- A project aims at creating a engeering sample for beginners.

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
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.  */


//Custom header
#include "System.h"
#include "GuessNum.h"

//Custom functions
void            generate(void);
int             proc(void);
static void     print_header(void);
void            proc_start(void);
static void     print_help(void);
static void     print_version(void);
static void     automode(void);

int
main(int argc, char *argv[]) 
{
    int optc = 0;

    ProgName = argv[0];

    while ( (optc = getopt ( argc, argv, optString )) != -1)
    {
        switch ( optc )
        {
            case 'v':
                print_version();
                //exit( EXIT_SUCCESS );
                break;
            case 'h':
                print_help();
                //exit( EXIT_SUCCESS );
                break;
            case 'd':
                gDebug = 1;
                proc_start();
                //exit( EXIT_SUCCESS );
                break;
            default:
                print_help();
                //exit( EXIT_SUCCESS );
        }
    }
    if ( argc == 1 ) proc_start();
    exit( EXIT_SUCCESS );
}


void
generate(void)
{
    int i;
    srand ( (unsigned)time(NULL) );
    do{
        for ( i = 0; i < 4; i++ )  iNum[i] = rand() % 10;
    } while ( iNum[0]==iNum[1] || iNum[0]==iNum[2] || iNum[0]==iNum[3] || \
              iNum[1]==iNum[2] || iNum[1]==iNum[3] || \
              iNum[2]==iNum[3] \
            );
}

int
proc(void)
{
    int re;
    int i, j;
    int a = 0, b = 0;
    putchar('\n');
    fflush(stdin);
    scanf("%c%c%c%c*", &cIn[0], &cIn[1], &cIn[2], &cIn[3]);
    iCount++;
    if ( cIn[0]=='0' && cIn[1]=='0' && cIn[2]=='0' && cIn[3]=='0' ) return 2;
    for ( i = 0; i < 4; i++)
        for ( j = 0; j < 4; j++)
            if ( (cIn[i]-48) == iNum[j] )
            {
                if ( i == j ) a++;
                else b++;
            }
    printf("%dA%dB\n", a, b);
    if ( a == 4 ) return 3;
    return 1;
}

void
print_header(void)
{
    printf("\n\
Guess numbers, Enjoy!\n\
Author: swordfish.cn[AT]gmail.com\n\
Version: %s\n\
Finish time: 2007.6.17\n\
", VERSION);
    return;
}

void
proc_start(void)
{
    int re;
    char ch;
    print_header();
    do{
        iCount = 0;
        generate();
        if ( gDebug )
            printf("\nDebug mode is on: %d%d%d%d\n", iNum[0], iNum[1], iNum[2], iNum[3]);
        printf("\n\
Game started, please input 4 numbers.\n\
Input 0000 to exit current game.\n"
);
        while ( re = proc() )
        {
            if ( re == 2)
            {
                printf("You couldn't finish the game.\n");
                break;
            }
            if ( re == 3)
            {
                printf("You got them all! You have guessed %d time(s).\n", iCount);
                break;
                }
        }
        printf("Play one more time?(Y/N)");
        fflush (stdin);
        scanf("%c", &ch);
    }while ( toupper(ch) == 'Y' );
    printf("Game over, goodbye!\n");
    return;
}

static void
print_help(void)
{
    printf("Usage: %s [OPTION]...\n", ProgName);
    puts("");
    fputs("\
-v      display version and exit.\n\
-h      display this help and exit.\n\
-d      enable debugging mode.\n\
\n\
Pleas report bugs to swordfish.cn[AT]gmail.com\
", stdout);

}

static void
print_version(void)
{
    printf("\nGuessNum, Version %s .\n", VERSION);
    fputs("This software is free software, distributed under GPL. \nAbsolutely no warranty.\n", stdout);
}
