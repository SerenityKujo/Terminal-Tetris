#ifndef PLAYFIELD_H
#define PLAYFIELD_H

#include "charMatrix.h"

typedef CharM Playfield;

#define deleteP deleteCM

Playfield* newP(const int numberLine, const int numberColumn);

void setL(const int l, Playfield *const pPlayfield, const char *const skins);

void setP(Playfield *const pPlayfield, const char *const skins);

void displayL(const int l, const Playfield *const pPlayfield);

int numberLine(const Playfield *const pPlayfield);
int numberColumn(const Playfield *const pPlayfield);

#endif

