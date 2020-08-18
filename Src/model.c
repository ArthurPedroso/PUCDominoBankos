#include "model.h"
#include <stdlib.h>

Domino* shuffleDominos(Domino* _arrayDeDomino)
{
    return _arrayDeDomino;
}

Domino* createDominoArray()
{
    static Domino array[28];

    for(int i = 0; i < 28; i++)
    {
        array[i].posX = 0;
        array[i].posY = 0;
        array[i].rotation = DOMINO_UP;
        array[i].type = i;
    }
    
    return array;
}