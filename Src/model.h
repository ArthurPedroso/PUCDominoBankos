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
#define CYCLE_POSITION_FORWARD 0
#define CYCLE_POSITION_BACKWARDS 1
//-----DIRECAO DE MOVIMENTO-----//


//-----ESTADO DOMINO CONECTAVEL-----//
#define UNLINKABLE_DOMINO 0
#define LINKABLE_DOMINO_LEFT 1
#define LINKABLE_DOMINO_RIGHT 2
#define LINKABLE_DOMINO_LEFT_RIGHT 3
//-----ESTADO DOMINO CONECTAVEL-----//

#include "common.h"


Domino* s_getGameDominoes();

void displayPlayerHand(int _player);
void modelInitialization();
void resetDominoesState();
void assignPlayerStartingHand(int _player);
void changePlayerSelectedDomino(int _player);
void pickDominoeFromPile(int _playerState);
void movePlayerDomino(int _player);
void unselectPlayerDomino(int _player);
bool tryToSetSelectedDominoToTable();

//-----ETAPA1-----//
//void shuffleDominoesAndDisplay();
//void organizeDominoes();
//-----ETAPA1-----//

#endif