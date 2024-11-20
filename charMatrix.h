#ifndef CHAR_MATRIX_H
#define CHAR_MATRIX_H

typedef struct charM CharM;

CharM* newCM(const int height, const int width);

void deleteCM(CharM** apCharM);

void setE(const int h, const int w, CharM *const pCharM, const char c);

void displayE(const int h, const int w, const CharM *const pCharM);

int height(const CharM *const pCharM);
int width(const CharM *const pCharM);
char** charMatrix(const CharM *const pCharM);

#endif

