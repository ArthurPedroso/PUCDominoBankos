#ifndef DOMINOES_LIST_HEADER
#define DOMINOES_LIST_HEADER

#include "common.h"

typedef struct DominoListItemTAG
{
    struct DominoListItemTAG* nextItem; 
    LinkableDomino* dominoStored;

    int index;
} LinkableDominoListItem;

void startList();
int getItemsCount();
void deleteList();
void addItemToDominoList(LinkableDomino* _domino);
LinkableDominoListItem* getItemFromDominoList(int _itemIndex);

#endif