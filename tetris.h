#ifndef TETRIS_H
#define TETRIS_H

#include "playfield.h"
#include "tetromino.h"
#include "skins.h"

#include <stdbool.h>

void clear(Playfield *const pPlayfield, const char *const skins);

void dispGame(const Playfield *const pPlayfield, const Tetromino *const pCurrentTetromino, const Tetromino *const pNextTetromino, const char *const skins);

void action(Tetromino *const pTetromino, Playfield *const pPlayfield, const char *const skins);

#endif

