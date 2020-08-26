#ifndef MODEL_HEADER
#define MODEL_HEADER

#define DOMINO_UP 0
#define DOMINO_RIGHT 90
#define DOMINO_DOWN 180
#define DOMINO_LEFT 270
#define GAME_DOMINOES_AMOUNT 28

typedef struct 
{
    int posX;
    int posY;
    int rotation;
    int rightType;
    int leftType;
}Domino;

void shuffleDominoesAndDisplay();
void modelInitialization();
void organizeDominoes();

#endif