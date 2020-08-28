#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "common.h"

void menuInit(int _displayInvalidOption);
void screenDisplay();
void screenDisplayOptions();
void printDominoes(Domino* _dominoArray, int _arraySize);
void exitGameText();
void invalidOption();
#endif