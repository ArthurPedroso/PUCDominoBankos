#ifndef MODEL_HEADER
#define MODEL_HEADER

#define DOMINO_UP 0
#define DOMINO_RIGHT 90
#define DOMINO_DOWN 180
#define DOMINO_LEFT 270


typedef struct 
{
    int posX;
    int posY;
    int rotation;
    int type;
}Domino;

Domino* createDominoArray();


#endif