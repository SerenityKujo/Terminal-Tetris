#include "tetromino.h"
#include "playfield.h"

#include <stdlib.h>

struct tetromino
{
   Name _name;

   int _x;
   int _y;

   int _rotationAngle;

   Playfield* _tetromino;
};

static int dimension(const Name name)
{
   switch(name)
   {
      case I:
         return 4;
      case O:
         return 2;
      case T: case S: case Z: case J: case L:
         return 3;

      default:
         return -1;
   }
}

static void setBlankE(const int l, const int c, Tetromino *const pTetromino)
{
   setE(l, 2*c, pTetromino->_tetromino, ' ');
   setE(l, 2*c+1, pTetromino->_tetromino, ' ');
}

static void setBlankL(const int l, Tetromino *const pTetromino)
{
   for(int c = 0; c < numberColumn(pTetromino->_tetromino); ++c)
      setBlankE(l, c, pTetromino);
}

static void setBlockE(const int l, const int c, Tetromino *const pTetromino, const char *const skins)
{
   setE(l, 2*c, pTetromino->_tetromino, skins[lBlock]);
   setE(l, 2*c+1, pTetromino->_tetromino, skins[rBlock]);
}

static void setBlockL(const int l, Tetromino *const pTetromino, const char *const skins)
{
   for(int c = 0; c < numberColumn(pTetromino->_tetromino); ++c)
      setBlockE(l, c, pTetromino, skins);
}

static void setT(Tetromino* pTetromino, const char *const skins)
{
   switch(pTetromino->_name)
   {
      case I:
         setBlankL(0, pTetromino);
         setBlockL(1, pTetromino, skins);
         setBlankL(2, pTetromino);
         setBlankL(3, pTetromino);
      break;

      case O:
         setBlockL(0, pTetromino, skins);
         setBlockL(1, pTetromino, skins);
      break;

      case T:
         setBlankL(0, pTetromino);
         setBlockL(1, pTetromino, skins);

         setBlankE(2, 0, pTetromino);
         setBlockE(2, 1, pTetromino, skins);
         setBlankE(2, 2, pTetromino);
      break;

      case S:
         setBlankL(0, pTetromino);

         setBlankE(1, 0, pTetromino);
         setBlockE(1, 1, pTetromino, skins);
         setBlockE(1, 2, pTetromino, skins);

         setBlockE(2, 0, pTetromino, skins);
         setBlockE(2, 1, pTetromino, skins);
         setBlankE(2, 2, pTetromino);
      break;

      case Z:
         setBlankL(0, pTetromino);

         setBlockE(1, 0, pTetromino, skins);
         setBlockE(1, 1, pTetromino, skins);
         setBlankE(1, 2, pTetromino);

         setBlankE(2, 0, pTetromino);
         setBlockE(2, 1, pTetromino, skins);
         setBlockE(2, 2, pTetromino, skins);
      break;

      case J:
         setBlankL(0, pTetromino);
         setBlockL(1, pTetromino, skins);

         setBlankE(2, 0, pTetromino);
         setBlankE(2, 1, pTetromino);
         setBlockE(2, 2, pTetromino, skins);
      break;

      case L:
         setBlankL(0, pTetromino);
         setBlockL(1, pTetromino, skins);

         setBlockE(2, 0, pTetromino, skins);
         setBlankE(2, 1, pTetromino);
         setBlankE(2, 2, pTetromino);
      break;

      default:
         deleteT(&pTetromino);
   }
}

Tetromino* newT(const Name name, const char *const skins)
{
   Tetromino* pTetromino;
   if(!(pTetromino = malloc(sizeof(Tetromino))))
      return NULL;

   if(!(pTetromino->_tetromino = newP(dimension(name), dimension(name))))
   {
      free(pTetromino);
      return NULL;
   }

   pTetromino->_name = name;
   pTetromino->_rotationAngle = 0;

   setT(pTetromino, skins);

   return pTetromino;
}

void deleteT(Tetromino** apTetromino)
{
if(!apTetromino) return;

   deleteP(&((*apTetromino)->_tetromino));
   free(*apTetromino);

   apTetromino = NULL;
}

static bool iZoneClear(const Tetromino *const pTetromino, const int col, const Playfield *const pPlayfield, const char *const skins)
{
   int lT = 0+(pTetromino->_name != O);
   for(int l = 0; lT < numberLine(pTetromino->_tetromino); ++lT, ++l)
      for(int c = 0; c < numberColumn(pTetromino->_tetromino); ++c)
         if(charMatrix(pTetromino->_tetromino)[lT][2*c] != ' ')
            if(charMatrix(pPlayfield)[l][2*c+col] != skins[lBlank])
               return false;
   return true;
}

bool insert(Tetromino *const pTetromino, const int col, const Playfield* const pPlayfield, const char *const skins)
{
   pTetromino->_x = col;
   pTetromino->_y = -(pTetromino->_name != O);

   return iZoneClear(pTetromino, 2*col, pPlayfield, skins);
}

static int iLeftBlock(const Tetromino *const pTetromino, const int l)
{
   int c;
   for(
         c = 0;
         c != numberColumn(pTetromino->_tetromino) &&
         charMatrix(pTetromino->_tetromino)[l][2*c] == ' ';
         ++c
      );
   return c;
}

static bool canMoveLeft(const Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins)
{
   for(int l = 0; l < height(pTetromino->_tetromino); ++l)
   {
      int c = iLeftBlock(pTetromino, l);
      if(c == numberColumn(pTetromino->_tetromino)) continue;
      else if(2*(pTetromino->_x+c)-1 == -1) return false;
      else if(charMatrix(pPlayfield)[pTetromino->_y+l][2*(pTetromino->_x+c)-1] == skins[rBlock])
         return false;
   }
   return true;
}

void moveLeft(Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins)
{
   if(canMoveLeft(pTetromino, pPlayfield, skins))
      --pTetromino->_x;
}

static int iRightBlock(const Tetromino *const pTetromino, const int l)
{
   int c;
   for(
         c = numberColumn(pTetromino->_tetromino);
         c != 0 &&
         charMatrix(pTetromino->_tetromino)[l][2*c-1] == ' ';
         --c
      );
   return c;
}

static bool canMoveRight(const Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins)
{
   for(int l = 0; l < height(pTetromino->_tetromino); ++l)
   {
      int c = iRightBlock(pTetromino, l);
      if(c == 0) continue;
      else if(pTetromino->_x+c == numberColumn(pPlayfield)) return false;
      else if(charMatrix(pPlayfield)[pTetromino->_y+l][2*(pTetromino->_x+c)] == skins[lBlock])
         return false;
   }
   return true;
}

void moveRight(Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins)
{
   if(canMoveRight(pTetromino, pPlayfield, skins))
      ++pTetromino->_x;
}

static void lock(Tetromino *const pTetromino, Playfield *const pPlayfield)
{
   for(int l = 0; l < numberLine(pTetromino->_tetromino); ++l)
      for(int c = 0; c < 2*numberColumn(pTetromino->_tetromino); ++c)
         if(charMatrix(pTetromino->_tetromino)[l][c] != ' ')
            charMatrix(pPlayfield)[pTetromino->_y+l][2*pTetromino->_x+c] = charMatrix(pTetromino->_tetromino)[l][c];
}

static int iBottomBlock(const Tetromino *const pTetromino, const int c)
{
   int l;
   for(
         l = height(pTetromino->_tetromino)-1;
         l != -1 &&
         charMatrix(pTetromino->_tetromino)[l][2*c] == ' ';
         --l
      );
   return l;
}

static bool canMoveDown(const Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins)
{
   for(int c = 0; c < numberColumn(pTetromino->_tetromino); ++c)
   {
      int l = iBottomBlock(pTetromino, c);
      if(l == -1) continue;
      else if(pTetromino->_y+l+1 == numberLine(pPlayfield)) return false;
      else if(charMatrix(pPlayfield)[pTetromino->_y+l+1][2*(pTetromino->_x+c)] == skins[lBlock])
         return false;
   }
   return true;
}

bool moveDownOrLock(Tetromino *const pTetromino, Playfield *const pPlayfield, const char *const skins)
{
   if(canMoveDown(pTetromino, pPlayfield, skins))
   {
      ++pTetromino->_y;
      return true;
   }
   else
   {
      lock(pTetromino, pPlayfield);
      return false;
   }
}

void hardDrop(Tetromino *const pTetromino, Playfield *const pPlayfield, const char *const skins)
{
   int hardDropLine = numberLine(pPlayfield);

   for(int c = 0; c < numberColumn(pTetromino->_tetromino); ++c)
   {
      int iBBlock = iBottomBlock(pTetromino, c);
      if(iBBlock == -1) continue;
      int l;
      for(
            l = pTetromino->_y+iBBlock;
            l+1 != numberLine(pPlayfield) &&
            charMatrix(pPlayfield)[l+1][2*(pTetromino->_x+c)] != skins[lBlock];
            ++l
         );

      l -= iBBlock;
      if(l < hardDropLine)
         hardDropLine = l;
   }

   pTetromino->_y = hardDropLine;
}

static void rotateT(Tetromino *const pTetromino)
{
   CharM* tetrominoR = newCM(height(pTetromino->_tetromino), width(pTetromino->_tetromino));

   for(int l = 0; l < numberLine(pTetromino->_tetromino); ++l)
      for(int c = 0; c < numberColumn(pTetromino->_tetromino); ++c)
      {
         setE(c, 2*(dimension(pTetromino->_name)-1-l), tetrominoR, charMatrix(pTetromino->_tetromino)[l][2*c]);
         setE(c, 2*(dimension(pTetromino->_name)-1-l)+1, tetrominoR, charMatrix(pTetromino->_tetromino)[l][2*c+1]);
      }

   deleteCM(&pTetromino->_tetromino);
   pTetromino->_tetromino = tetrominoR;

   pTetromino->_rotationAngle = (pTetromino->_rotationAngle + 270) % 360;
}

static bool canRotate(const Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins)
{
   if(pTetromino->_y == -1 || pTetromino->_x <= -1 ||
   pTetromino->_x+numberColumn(pTetromino->_tetromino) > numberColumn(pPlayfield) || pTetromino->_y+height(pTetromino->_tetromino)-1 >= height(pPlayfield))
   return false;
   else
   {
      for(int l = 0; l < numberLine(pTetromino->_tetromino); ++l)
         for(int c = 0; c < numberColumn(pTetromino->_tetromino); ++c)
            if(charMatrix(pTetromino->_tetromino)[l][2*c] != ' ' &&
               charMatrix(pPlayfield)[pTetromino->_y+c][2*(pTetromino->_x+dimension(pTetromino->_name)-1-l)] != skins[lBlank])
               return false;
   return true;
   }
}

void rotate(Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins)
{
   if(canRotate(pTetromino, pPlayfield, skins))
      rotateT(pTetromino);
}

Name name(const Tetromino *const pTetromino){return pTetromino->_name;}
int rotationAngle(const Tetromino *const pTetromino){return pTetromino->_rotationAngle;}
int x(const Tetromino *const pTetromino){return pTetromino->_x;}
int y(const Tetromino *const pTetromino){return pTetromino->_y;}
Playfield* tetromino(const Tetromino *const pTetromino){return pTetromino->_tetromino;}

