#ifndef CONTROLLER_HEADER
#define CONTROLLER_HEADER

typedef int uiInput; //apenas para lembrar que esse int representa o input do usuario

//inicializa as variaveis do controller
int startGame();
//Verifica em que o estado o jogo se encontra e utiliza uma função de gerenciamento de input adequada a esse estado
void managePlayerChoice(uiInput _playerInput);

#endif