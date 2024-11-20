#ifndef SKINS_H
#define SKINS_H

#include <stdbool.h>

enum
{
   oLWall, iLWall, iRWall, oRWall,
   iGround, oGroundL, oGroundR,
   lBlank, rBlank,
   lBlock, rBlock
};

bool setS
(
   char* const skins,
   const unsigned int skinNumber,
   const char* skinFile
);

#endif

