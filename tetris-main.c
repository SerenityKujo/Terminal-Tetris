#include "skins.h"
#include "playfield.h"
#include "tetromino.h"
#include "tetris.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
   char skins[rBlock+1];

   if(!setS(skins, rBlock+1, "skinfile.txt"))
{
   printf("Could not load skins.\n Exiting programme\n");
   return -1;
}

   Playfield* pPlayfield;
if(!(pPlayfield = newP(20,10)))
{
   printf("Allocation of the playfield failed.\n Exiting programme\n");
   return -2;
}

   setP(pPlayfield, skins);

   srand(time(NULL));

   Tetromino* pCurrentTetromino = newT(rand()%(L+1), skins);
   Tetromino* pNextTetromino = newT(rand()%(L+1), skins);

   clock_t then = clock();

   int xPrev = x(pCurrentTetromino);
   int yPrev = y(pCurrentTetromino);
   int rAPrev = rotationAngle(pCurrentTetromino);
   insert(pCurrentTetromino, 4-(name(pCurrentTetromino) == I), pPlayfield, skins);
   for(;;)
   {
      action(pCurrentTetromino, pPlayfield, skins);
      if(xPrev != x(pCurrentTetromino) || yPrev != y(pCurrentTetromino) ||
         rAPrev != rotationAngle(pCurrentTetromino))
      {
         clear(pPlayfield, skins);
         dispGame(pPlayfield, pCurrentTetromino, pNextTetromino, skins);
         xPrev = x(pCurrentTetromino);
         yPrev = y(pCurrentTetromino);
         rAPrev = rotationAngle(pCurrentTetromino);
      }
      if(clock() - then >= CLOCKS_PER_SEC/3)
      {
         if(!(moveDownOrLock(pCurrentTetromino, pPlayfield, skins)))
         {
            deleteT(&pCurrentTetromino);
            pCurrentTetromino = pNextTetromino;
            pNextTetromino = newT(rand()%(L+1), skins);
            if(!insert(pCurrentTetromino, 4-(name(pCurrentTetromino) == I), pPlayfield, skins))
            {
               dispGame(pPlayfield, pCurrentTetromino, pCurrentTetromino, skins);
               break;
            }
         }
         then = clock();
      }
   }
   deleteP(&pPlayfield);

   deleteT(&pCurrentTetromino);
   deleteT(&pNextTetromino);

   return 0;
}

