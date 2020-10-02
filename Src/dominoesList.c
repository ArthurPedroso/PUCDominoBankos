#include "dominoesList.h"
#include <stdio.h>
#include <stdlib.h>


LinkableDominoListItem** s_getHeaderDominoItem()
{
    static LinkableDominoListItem* headerDominoItem;

    return &headerDominoItem;
}
int* s_getListCount()
{
    static int itemsCount;

    return &itemsCount;
}

//-----HEADER FUNCS-----//

int getItemsCount()
{
    return *s_getListCount();
}

void startList()
{
    (*s_getHeaderDominoItem()) = (LinkableDominoListItem*)malloc(sizeof(LinkableDominoListItem));
    LinkableDominoListItem* headerDomino = *s_getHeaderDominoItem();
    headerDomino->dominoStored = NULL;
    headerDomino->nextItem = NULL;
    headerDomino->index = 0;
}

void addItemToDominoList(LinkableDomino* _domino)
{
    LinkableDominoListItem* headerDomino = *s_getHeaderDominoItem();
    LinkableDominoListItem* currentDominoItem = headerDomino;
    LinkableDominoListItem* itemToAdd = (LinkableDominoListItem*)malloc(sizeof(LinkableDominoListItem));
    int index = 0;
    bool foundEndOfList = false;

    if(!headerDomino->dominoStored)
    {
        headerDomino->dominoStored = _domino;
        headerDomino->index = index;
        (*s_getListCount())++;
        return;
    }

    //-------------------//

    itemToAdd->dominoStored = _domino;    
    itemToAdd->nextItem = NULL;

    do
    {        
        index++;
        if(!currentDominoItem->nextItem)
        {            
            itemToAdd->index = index;
            currentDominoItem->nextItem = itemToAdd;
            foundEndOfList = true;
            (*s_getListCount())++;
        }
        else
            currentDominoItem = currentDominoItem->nextItem;
    } while (!foundEndOfList);   
}

LinkableDominoListItem* getItemFromDominoList(int _itemIndex)
{
    LinkableDominoListItem* currentListItem = *s_getHeaderDominoItem();

    for(int i = 0; i < _itemIndex; i++)
    {        
        //-----ENCONTRA PROXIMO ITEM NA LISTA-----//
        if(currentListItem->nextItem)
            currentListItem = currentListItem->nextItem;
        else
        {
            printf("!ERRO! esse item{%d} da lista nao existe\n", _itemIndex);
            return NULL;
        }
        //-----ENCONTRA PROXIMO ITEM NA LISTA-----//
    }

    if(!currentListItem->dominoStored)
    {
        printf("!ERRO! nao ha domino armazenado nesse item{%d} da lista\n", _itemIndex);
        currentListItem = NULL;
    }

    return currentListItem;
}

void deleteList()
{
    LinkableDominoListItem* currentItem;
    int itemsCount = getItemsCount();
    for(int i = (itemsCount - 1); i >= 0; i--)
    {
        currentItem = getItemFromDominoList(i);

        free(currentItem);
    }
}