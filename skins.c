#include "skins.h"

#include <stdio.h>

bool setS
(
   char* const skins,
   const unsigned int skinNumber,
   const char* skinFile
)
{
   FILE* const pSkinFile = fopen(skinFile, "r");
if(pSkinFile == NULL)
   {
      printf("Could not open file. File name could be invalid");
      return false;
   }

//TODO CASE WHEN FILE INVALID

   fscanf(pSkinFile, "%c", &(skins[oLWall]));
   fscanf(pSkinFile, "%c", &(skins[iLWall]));
   fscanf(pSkinFile, "%c", &(skins[iRWall]));
   fscanf(pSkinFile, "%c", &(skins[oRWall]));
   fscanf(pSkinFile, "%c", &(skins[iGround]));
   fscanf(pSkinFile, "%c", &(skins[oGroundL]));
   fscanf(pSkinFile, "%c", &(skins[oGroundR]));
   fscanf(pSkinFile, "%c", &(skins[lBlank]));
   fscanf(pSkinFile, "%c", &(skins[rBlank]));
   fscanf(pSkinFile, "%c", &(skins[lBlock]));
   fscanf(pSkinFile, "%c", &(skins[rBlock]));

	fclose(pSkinFile);

   return true;
}

