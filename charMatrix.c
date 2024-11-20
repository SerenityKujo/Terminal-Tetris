#include "charMatrix.h"

#include <stdlib.h>
#include <stdio.h>

struct charM
{
   int _height;
   int _width;

   char ** _charMatrix;
};

static char ** newCm(const int height, const int width)
{
   char ** newCharM;
if(!(newCharM= malloc((height)*sizeof(char*))))	return NULL;

	for(int l = 0; l < height; ++l)
	{
if(!(newCharM[l] = malloc((width)*sizeof(char))))
{
   for(--l; l >= 0; --l)
      free(newCharM[l]);
   free(newCharM);
   return NULL;
}
   }

   return newCharM;
}

static void deleteCm(char ** charMatrix, const int height)
{
if(charMatrix == NULL) return;

   for(int l = 0; l < height; ++l)
		free(charMatrix[l]);
	free(charMatrix);
}

CharM* newCM(const int height, const int width)
{

	CharM* pCharMC;
if(!(pCharMC = malloc(sizeof(CharM)))) return NULL;

   pCharMC->_height = height;
   pCharMC->_width = width;

if(!(pCharMC->_charMatrix = newCm(pCharMC->_height, pCharMC->_width)))
{
   free(pCharMC);
   return NULL;
}
	return pCharMC;
}

void deleteCM(CharM** apCharM)
{
if(!apCharM) return;

   deleteCm((*apCharM)->_charMatrix, (*apCharM)->_height);
	free(*apCharM);

   *apCharM = NULL;
}

void setE(const int h, const int w, CharM *const pCharM, const char c)
{
   pCharM->_charMatrix[h][w] = c;
}

void displayE(const int h, const int w, const CharM *const pCharM)
{
   printf("%c", pCharM->_charMatrix[h][w]);
}

int height(const CharM *const pCharM){return pCharM->_height;}
int width(const CharM *const pCharM){return pCharM->_width;}
char** charMatrix(const CharM *const pCharM){return pCharM->_charMatrix;}

