#ifndef VIEW_HEADER
#define VIEW_HEADER

#include "common.h"

void menuInit();
void screenDisplay();
void displayPlayerSelectionMenu();
void printDominoes(Domino* _dominoArray, int _arraySize);
void exitGame();
//Adicionar playerSelection
void invalidOption();
#endif