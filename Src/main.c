#include"controller.h"

#include "dominoesList.h"
#include "model.h"
#include <stdio.h>
int main()
{
    LinkableDomino newLinkableDomino;
    LinkableDominoListItem* foundDomino;
    Domino domino;

    domino.state = STATE_DOMINOES_PILE;
    domino.posX = 0;
    domino.posY = 0;
    domino.rotation = DOMINO_ROTATION_0;
    domino.rightType = 0;
    domino.leftType = 0;
    domino.scale = 1.0f;
    domino.linkableDominoState = UNLINKABLE_DOMINO;
    domino.linkedDomino = NULL;
    domino.playerColorID = 0;

    newLinkableDomino.domino = &domino;

    startList();
    addItemToDominoList(&newLinkableDomino);
    addItemToDominoList(&newLinkableDomino);
    addItemToDominoList(&newLinkableDomino);

    foundDomino = getItemFromDominoList(1);
    (*foundDomino).index = 10;

    deleteList();

    foundDomino = getItemFromDominoList(1);
    printf("conteudo ponteiro cringe %d\n", (*foundDomino).index);
    return 0;
    //return startGame();    
}