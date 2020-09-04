#ifndef MODEL_HEADER
#define MODEL_HEADER

#define DOMINO_UP 0
#define DOMINO_RIGHT 90
#define DOMINO_DOWN 180
#define DOMINO_LEFT 270
#define GAME_DOMINOES_AMOUNT 28
#define HAND_DOMINOES_STARTING_AMOUNT 7
#define STATE_DOMINOES_PILE 0
#define STATE_PLAYER_ONE 1
#define STATE_PLAYER_TWO 2
#define STATE_GAME_TABLE 3


Domino* getGameDominoes();
void getPlayersHands(Domino* _dominoesPile);
void pickDominoeFromPile(Domino* _dominoesPile, int player);
void shuffleDominoesAndDisplay();
void modelInitialization();
void organizeDominoes();
void initializeDominoArray(Domino* _dominoArray); //temporario

#endif