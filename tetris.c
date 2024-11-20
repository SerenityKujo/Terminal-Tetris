#include "tetris.h"

#include "utilities.h"

#include <stdlib.h>
#include <stdio.h>

static bool fullLine(const int l, const Playfield *const pPlayfield, const char *const skins)
{
   for(int c = 0; c < numberColumn(pPlayfield); ++c)
      if(charMatrix(pPlayfield)[l][2*c] == skins[lBlank])
         return false;
   return true;
}

static void clearLine(int l, Playfield *const pPlayfield, const char *const skins)
{
   for(; l >= 0; --l)
      for(int c = 0; c < 2*numberColumn(pPlayfield); ++c)
      {
         if(l > 0)
            charMatrix(pPlayfield)[l][c] = charMatrix(pPlayfield)[l-1][c];
         else
            setL(l, pPlayfield, skins);
      }
}

void clear(Playfield *const pPlayfield, const char *const skins)
{
   for(int l = height(pPlayfield) - 1; l >= 0; --l)
      if(fullLine(l, pPlayfield, skins))
      {
         clearLine(l, pPlayfield, skins);
         ++l;
      }
}

void dispGame(const Playfield *const pPlayfield, const Tetromino *const pCurrentTetromino, const Tetromino *const pNextTetromino, const char *const skins)
{
   system("clear");

   int lTetr = 0;
   for(int l = 0; l < height(pPlayfield) + 2; ++l)
	{
      //Left space
      if(l < height(pPlayfield) - 2)
      {
         for(int s = 0; s < (2*numberColumn(pPlayfield) + 47) / 2; ++s)
            printf(" ");
      }
      else if(l == height(pPlayfield) - 2)
      {
         int s;
         for(s = 0; s < (2*numberColumn(pPlayfield) + 47) / 4; ++s)
            printf(" ");
         printf("Next:");
         for(s += 5; s < (2*numberColumn(pPlayfield) + 47) / 2; ++s)
            printf(" ");
      }
      else if(l > height(pPlayfield) - 2)
      {
         if(lTetr < height(tetromino(pNextTetromino)))
         {
            int s;
            for(s = 0; s < (2*numberColumn(pPlayfield) + 47) / 4; ++s)
               printf(" ");
            displayL(lTetr, tetromino(pNextTetromino));
            for(s += 2*numberColumn(tetromino(pNextTetromino)); s < (2* numberColumn(pPlayfield) + 47) / 2; ++s)
               printf(" ");
            ++lTetr;
         }
         else
            for(int s = 0; s < (2*numberColumn(pPlayfield) + 47) / 2; ++s)
               printf(" ");
      }

      //Left wall
      if(l < height(pPlayfield) + 1)
      {
         printf("%c", skins[oLWall]);
         printf("%c", skins[iLWall]);
      }
      else
         printf("  ");

      //Playfield interior
      if(l < height(pPlayfield))
      {
         for(int c = 0; c < numberColumn(pPlayfield); ++c)
            if(y(pCurrentTetromino) <= l && l < y(pCurrentTetromino) + numberLine(tetromino(pCurrentTetromino))
            && x(pCurrentTetromino) <= c && c < x(pCurrentTetromino) + numberColumn(tetromino(pCurrentTetromino))
            && charMatrix(tetromino(pCurrentTetromino))[l-y(pCurrentTetromino)][2*(c-x(pCurrentTetromino))] != ' ')
            {
               printf("%c", charMatrix(tetromino(pCurrentTetromino))[l-y(pCurrentTetromino)][2*(c-x(pCurrentTetromino))]);//█
               printf("%c", charMatrix(tetromino(pCurrentTetromino))[l-y(pCurrentTetromino)][2*(c-x(pCurrentTetromino))+1]);//█
            }
            else
            {
               printf("%c", charMatrix(pPlayfield)[l][2*c]);
               printf("%c", charMatrix(pPlayfield)[l][2*c+1]);
            }
      }
      else if(l == height(pPlayfield))
         for(int c = 0; c < numberColumn(pPlayfield); ++c)
         {
            printf("%c", skins[iGround]);
            printf("%c", skins[iGround]);
         }
      else
         for(int c = 0; c < numberColumn(pPlayfield); ++c)
         {
               printf("%c", skins[oGroundL]);
               printf("%c", skins[oGroundR]);
         }

      //Right wall
      if(l < height(pPlayfield) + 1)
      {
         printf("%c", skins[iRWall]);
         printf("%c", skins[oRWall]);
      }

	printf("\n");
   }
}

void action(Tetromino *const pTetromino, Playfield *const pPlayfield, const char *const skins)
{
   if(kbhit())
   {
      char c = getch();
      if(c == ' ') hardDrop(pTetromino, pPlayfield, skins);
      else if(c  == '\033')
      {
         getch();
         switch(getch())
         {
            case 'A':
               rotate(pTetromino, pPlayfield, skins);
            break;

            case 'B':
               moveDownOrLock(pTetromino, pPlayfield, skins);
            break;

            case 'C':
               moveRight(pTetromino, pPlayfield, skins);
            break;

            case 'D':
               moveLeft(pTetromino, pPlayfield, skins);
            break;
         }
      }
   }
}

