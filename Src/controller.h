#ifndef CONTROLLER_HEADER
#define CONTROLLER_HEADER

#define OPTION_1 1
#define OPTION_2 2
#define OPTION_3 3
#define OPTION_4 4
#define OPTION_5 5
#define OPTION_6 6

typedef int uiInput;

//inicializa as variaveis do controller
int startGame();
//Verifica em que o estado o jogo se encontra e utiliza uma função de gerenciamento de input adequada a esse estado
void managePlayerChoice(uiInput _playerInput);

#endif