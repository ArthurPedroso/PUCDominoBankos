#include "view.h"
#include <stdio.h>


void printBoard()
{
    for(int linIndx = 0; linIndx < 10; linIndx++)
    {
        for(int colIndx = 0; colIndx < 10; colIndx++)
        {
        }        
        printf("\n");
    }
}

void helloWorld(char* _msg)
{
    printBoard(); 
}
