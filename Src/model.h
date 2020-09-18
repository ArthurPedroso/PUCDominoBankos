#ifndef MODEL_HEADER
#define MODEL_HEADER

//-----ROTACAO DO DOMINO-----//
#define DOMINO_ROTATION_0 0
#define DOMINO_ROTATION_90 90
#define DOMINO_ROTATION_180 180
#define DOMINO_ROTATION_270 270

//-----ESTADOS DO DOMINO-----//
#define STATE_DOMINOES_PILE 0
#define STATE_PLAYER_ONE 1
#define STATE_PLAYER_TWO 2
#define STATE_GAME_TABLE 3
#define STATE_GAME_MOVING 4
//-----ESTADOS DO DOMINO-----//

//-----DIRECAO DE MOVIMENTO-----//
#define MOVE_DOMINO_UP 0
#define MOVE_DOMINO_DOWN 1
#define MOVE_DOMINO_LEFT 2
#define MOVE_DOMINO_RIGHT 3
//-----DIRECAO DE MOVIMENTO-----//

#include "common.h"


Domino* s_getGameDominoes();

void displayPlayerHand(int _player);
void modelInitialization();
void resetDominoesState();
void assignPlayerStartingHand(int _player);
void changePlayerSelectedDomino(int _player);
void pickDominoeFromPile(int _playerState);
void movePlayerDomino(int _moveDirection, int _player);
void unselectPlayerDomino(int _player);

//-----ETAPA1-----//
//void shuffleDominoesAndDisplay();
//void organizeDominoes();
//-----ETAPA1-----//

#endif