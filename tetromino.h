#ifndef TETROMINO_H
#define TETROMINO_H

#include "skins.h"
#include "playfield.h"

#include <stdbool.h>

typedef struct tetromino Tetromino;

typedef enum Name{I, O, T, S, Z, J, L} Name;

Tetromino* newT(const Name name, const char *const skins);

void deleteT(Tetromino** apTetromino);

bool insert(Tetromino *const pTetromino, const int col, const Playfield* const pPlayfield, const char *const skins);

void moveLeft(Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins);

void moveRight(Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins);

bool moveDownOrLock(Tetromino *const pTetromino, Playfield *const pPlayfield, const char *const skins);

void hardDrop(Tetromino *const pTetromino, Playfield *const pPlayfield, const char *const skins);

void rotate(Tetromino *const pTetromino, const Playfield *const pPlayfield, const char *const skins);

Name name(const Tetromino *const pTetromino);
int rotationAngle(const Tetromino *const pTetromino);
int x(const Tetromino *const pTetromino);
int y(const Tetromino *const pTetromino);
Playfield* tetromino(const Tetromino *const pTetromino);

#endif

