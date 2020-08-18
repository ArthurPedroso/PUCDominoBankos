#include "model.h"
#include <stdlib.h>
#include <time.h>

Domino* shuffleDominos(Domino* _arrayDeDomino)
{
    //pega caixa e guarda fora do array
    Domino temp;
    //seleciona lugar aleatório e troca de lugar
    for(int i = 0; i < sizeof(_arrayDeDomino)/sizeof(Domino); i++)
    {
        temp = _arrayDeDomino[i];
        _arrayDeDomino 
    }
    //por exemplo 1 no lugar no 5 e 5 no lugar do 1
    //de maneira aleatória e sem repetir
    
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