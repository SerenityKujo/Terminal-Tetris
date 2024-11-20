#include "playfield.h"

#include "skins.h"

Playfield* newP(const int numberLine, const int numberColumn)
{
   return newCM(numberLine, 2*numberColumn);
}

static void setBlank
(
   const int l,
   const int c,
   Playfield *const pPlayfield,
   const char *const skins
)
{
   setE(l, 2*c, pPlayfield, skins[lBlank]);
   setE(l, 2*c+1, pPlayfield, skins[rBlank]);
}

void setL(const int l, Playfield *const pPlayfield, const char *const skins)
{
   for(int c = 0; c < numberColumn(pPlayfield); ++c)
      setBlank(l, c, pPlayfield, skins);
}

void setP(Playfield *const pPlayfield, const char *const skins)
{
   for(int l = 0; l < numberLine(pPlayfield); ++l)
      setL(l, pPlayfield, skins);
}

void displayL(const int l, const Playfield *const pPlayfield)
{
   for(int c = 0; c < width(pPlayfield); ++c)
      displayE(l, c, pPlayfield);
}

int numberLine(const Playfield *const pPlayfield){return height(pPlayfield);}
int numberColumn(const Playfield *const pPlayfield){return width(pPlayfield)/2;}


