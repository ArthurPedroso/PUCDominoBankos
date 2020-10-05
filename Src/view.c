#include "view.h"
#include "model.h"
#include "controller.h"
#include "OpenGLFiles/OGLManager.h"
#include "OpenGLFiles/OGLUtilities.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


void clearTerminal()
{
#ifdef OS_Windows
    system("cls");
#else
    printf("\033[H\033[J");
#endif
}

float* s_getDeltaTime()
{
    static float deltaTime = 0.0f;

    return &deltaTime;
}

//Muda o texto do OpengGl
//É possivel mudar a posicao e o tamanho do texto alterando as outras variaveis do "textData" 
void changeOGLText(char* _newText)
{
    OGLTextData* textData;
    textData = s_getTextData();

    textData->textToDraw = _newText;
}

void setOGLTextPosition(Vec2 _newPosition)
{
    OGLTextData* textData = s_getTextData();

    textData->xPos = _newPosition.posX;
    textData->yPos = _newPosition.posY;
}
//Chamado no inicio de cada frame
//A variavel _deltaTime traz o tempo que demorou para renderizar o ultimo frame
void OGLManagerUpdateCB(float _deltaTime)
{
    int input = -1; //atrivuição inicial neutra cujo valor nunca será utilizado pelo controlador

    if(OGLGetKeyDown(INPUT_KEY0)) input = 0;
    else if(OGLGetKeyDown(INPUT_KEY1)) input = 1;
    else if(OGLGetKeyDown(INPUT_KEY2)) input = 2;
    else if(OGLGetKeyDown(INPUT_KEY3)) input = 3;
    else if(OGLGetKeyDown(INPUT_KEY4)) input = 4;
    else if(OGLGetKeyDown(INPUT_KEY5)) input = 5;
    else if(OGLGetKeyDown(INPUT_KEY6)) input = 6;
    else if(OGLGetKeyDown(INPUT_KEY7)) input = 7;
    else if(OGLGetKeyDown(INPUT_KEY8)) input = 8;
    else if(OGLGetKeyDown(INPUT_KEY9)) input = 9;
    else if(OGLGetKey(INPUT_KEY_LEFT)) input = 12;
    else if(OGLGetKey(INPUT_KEY_RIGHT)) input = 13;

    *s_getDeltaTime() = _deltaTime;
    managePlayerChoice(input);//Passa para o coontroller o input atual do jogador
}
//Chamado antes da renderização do primeiro frame
//usar para inicialização
void OGLManagerFirstFrameCB()
{
    displayStartingMenu();
}
//-----------Head Funcs-----------//

//Reseta a posicao to texto para a poisicao padrao
void resetOGLTextPosition()
{
    setOGLTextPosition((Vec2){0.0f, 760.0f});
}
//retorna o delta time armazenado pelo view
float getDeltaTime()
{
    return *s_getDeltaTime();
}

//-----UI_TEXT-----//
//Menu Principal
void displayStartingMenu()
{
    //O 104 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[119]; 

    strcpy(strBuffer, "Bem vindo, vamos jogar domino!\n");
    strcat(strBuffer, "Selecione uma opcao:\n");
    strcat(strBuffer, "1- Novo jogo\n");
    strcat(strBuffer, "2- Salvar\n");
    strcat(strBuffer, "3- Carregar\n");
    strcat(strBuffer, "4- Como jogar\n");
    strcat(strBuffer, "5- Sair\n");

    changeOGLText(strBuffer);
}

//Menu de selecao de numero de jogadores
void displayPlayerSelectionMenu() //mostra a tela de seleção de jogadores
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[87]; 

    strcpy(strBuffer, "Quantos jogadores irão jogar?\n");
    strcat(strBuffer, "1- Jogar contra o AI\n");
    strcat(strBuffer, "2- Jogar com um amigo\n");
    strcat(strBuffer, "3- Voltar\n");

    changeOGLText(strBuffer);
}

void displayInstructionsMenu() //menu de instrucoes
{
    static char strBuffer[735]; 

    setOGLTextPosition((Vec2){0.0f, 682.0f});

    strcpy(strBuffer, "Regras\n");
    strcat(strBuffer, "1- Cada jogador recebe 7 pecas.\n");
    strcat(strBuffer, "2- Cada jogador podera comprar uma peca caso precise.\n");
    strcat(strBuffer, "3- Da-se inicio ao jogo o jogador que tirar a pedra “seis-seis”.\n");
    strcat(strBuffer, "4- O jogador deve posicionar a peca ao lado de outra que estara na mesa, tal que os pontos de um lado\n");
    strcat(strBuffer, "coincida com os pontos da outra peca.\n");
    strcat(strBuffer, "5- Caso nao haja pecas no monte o jogador devera passar o turno ao seguinte jogador.\n");
    strcat(strBuffer, "6- Quando joga-se sozinho, o jogador que ganhou a partida soma os pontos de todos os seus adversarios.\n");
    strcat(strBuffer, "7- Se o numero das extremidades saiu 7 vezes antes, a partida esta fechada, de modo que os  jogadores\n");
    strcat(strBuffer, "contarao  os  pontos  das  pedras  que  ficaram, sendo que o jogador com menos pontos vencem.\n");
    strcat(strBuffer, "--Aperte 1 para retornar ao menu inicial--\n");

    changeOGLText(strBuffer);
}

//Menu de atribuição de dominós
void displayStartDominosAssigmentMenu(int _cantStartGameWarning)
{
    //O 290 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[290]; 

    if(!_cantStartGameWarning) strcpy(strBuffer, "Distribuir dominós iniciais entre os jogadores:\n");
    else strcpy(strBuffer, "Só é possivel iniciar o jogo após a distribuição de domínos entre os jogadores:\n");
    strcat(strBuffer, "1- Iniciar jogo\n");
    strcat(strBuffer, "2- Distribuir para jogador 1\n");
    strcat(strBuffer, "3- Distribuir para jogador 2\n");
    strcat(strBuffer, "4- Visualizar dominós atribuidos para jogador 1\n");
    strcat(strBuffer, "5- Visualizar dominós atribuidos para jogador 2\n");
    strcat(strBuffer, "6- Ocultar dominós\n");
    strcat(strBuffer, "7- Voltar\n");

    changeOGLText(strBuffer);
}

//Menu de gameplay do jogador 1
void displayMainGameUIPlayer1Turn()
{
    //O 105 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[257]; 

    strcpy(strBuffer, "Turno do jogador 1\n");
    strcat(strBuffer, "1- Mostrar mao\n");
    strcat(strBuffer, "2- Esconder mao\n");
    strcat(strBuffer, "3- Compra peca\n");
    strcat(strBuffer, "4- Posicionar peca\n");
    strcat(strBuffer, "Seta Esquerda- Mover camera para a esquerda\n");
    strcat(strBuffer, "Seta Direita- Mover camera para a direita\n");
    strcat(strBuffer, "5- Pedir empate\n");
    strcat(strBuffer, "6- Voltar para o menu principal\n");

    changeOGLText(strBuffer);
}

//Menu de gameplay do jogador 2
void displayMainGameUIPlayer2Turn()
{
    //O 122 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[257]; 

    strcpy(strBuffer, "Turno do jogador 2\n");
    strcat(strBuffer, "1- Mostrar mao\n");
    strcat(strBuffer, "2- Esconder mao\n");
    strcat(strBuffer, "3- Compra peca\n");
    strcat(strBuffer, "4- Posicionar peca\n");
    strcat(strBuffer, "Seta Esquerda- Mover camera para a esquerda\n");
    strcat(strBuffer, "Seta Direita- Mover camera para a direita\n");
    strcat(strBuffer, "5- Pedir empate\n");
    strcat(strBuffer, "6- Voltar para o menu principal\n");

    changeOGLText(strBuffer);
}

//Menu de posicionamento de dominos do jogador 1
void displayPlaceDominoUIPlayer1Turn()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[150]; 

    strcpy(strBuffer, "Turno do jogador 1, posicionar dominó\n");
    strcat(strBuffer, "1- Confirmar posição\n");
    strcat(strBuffer, "2- Mudar peca\n");
    strcat(strBuffer, "3- Mudar posicao\n");
    strcat(strBuffer, "4- Mudar rotacao\n");
    strcat(strBuffer, "5- Voltar\n");

    changeOGLText(strBuffer);
}

//Menu de posicionamento de dominos do jogador 1
void displayPlaceDominoUIPlayer2Turn()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[150]; 

    strcpy(strBuffer, "Turno do jogador 2, posicionar dominó\n");
    strcat(strBuffer, "1- Confirmar posição\n");
    strcat(strBuffer, "2- Mudar peca\n");
    strcat(strBuffer, "3- Mudar posicao\n");
    strcat(strBuffer, "4- Mudar rotacao\n");
    strcat(strBuffer, "5- Voltar\n");

    changeOGLText(strBuffer);
}

//Menu de pedir empate
void displayAskForDrawScreen()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[38]; 

    strcpy(strBuffer, "1- Aceitar empate\n");
    strcat(strBuffer, "2- Recusar empate\n");

    changeOGLText(strBuffer);
}

//Menu de vitoria jogador 1
void displayPlayer1Victory()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[100]; 

    strcpy(strBuffer, "Jogador 1 e o vencedor!!!\n");
    strcat(strBuffer, "1- Sair do jogo\n");;

    changeOGLText(strBuffer);
}
//Menu de vitoria jogador 2
void displayPlayer2Victory()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[100]; 

    strcpy(strBuffer, "Jogador 2 e o vencedor!!!\n");
    strcat(strBuffer, "1- Sair do jogo\n");;

    changeOGLText(strBuffer);
}
/*
Old, only to organize dominoes
void screenDisplayOptions() //mostra as opcoes do jogador
{
    changeOGLText("\n1- Show Organized Dominoes\n2- Shuffle Dominoes\n3- Go Back");
}
*/
//-----UI_TEXT-----//

//Ativa o OpenGL e retorna qualquer codigo de erro
int screenDisplay() 
{
    return startRender(OGLManagerUpdateCB, OGLManagerFirstFrameCB);
}

//Recebe um array de dominós e exibe seus equivalentes pelo OpenGL
void printDominoes(Domino* _dominoArray, int _arraySize)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    for(int i = 0; i < _arraySize; i++)
    {
        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);

        oglDomino = oglDominos[dominoGObjectIndex]; //seleciona um dominó do opengl análogo ao domino do jogo
        oglDomino.colorID = currentDomino.playerColorID;
        oglDomino.visible = TRUE;
        oglDomino.currentRotation = currentDomino.rotation;      
        setGObjectPosition(&oglDomino.left, (currentDomino.position.posX -0.25f) * 0.2f,(currentDomino.position.posY * 0.2f), -1.0f);
        setGObjectPosition(&oglDomino.right, (currentDomino.position.posX +0.25f) * 0.2f, (currentDomino.position.posY  * 0.2f), -1.0f); 

        oglDominos[dominoGObjectIndex] = oglDomino;
    }  
}

//Recebe um array de dominós e exibe seus equivalentes pelo OpenGL, exibindo apenas os dominos com o estado de "_stateFilter"
void printDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter, Vec2 _offset)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    for(int i = 0; i < _arraySize; i++)
    {
        if(_dominoArray[i].state != _stateFilter) continue;

        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);
    
        oglDomino = oglDominos[dominoGObjectIndex]; //seleciona um dominó do opengl análogo ao domino do jogo
        oglDomino.colorID = currentDomino.playerColorID;
        oglDomino.visible = TRUE;  
        oglDomino.currentRotation = currentDomino.rotation;      
        setDominoGOScale(&oglDomino, currentDomino.scale, currentDomino.scale, currentDomino.scale);
        setDominoGOLocalPosition(&oglDomino, currentDomino.position.posX + _offset.posX, currentDomino.position.posY + _offset.posY, -1.0f);
        //setDominoGOPosition(&oglDomino, currentDomino.posX, currentDomino.posY, -1.0f);

        oglDominos[dominoGObjectIndex] = oglDomino;
    }  

}

//Esconde todos os dominos
void hideAllDominoes()
{
    DominoGObject* oglDominos = s_getDominoesGObjects();
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        oglDominos[i].visible = false;
    }
}

//esconde apenas os dominos com o estado de _stateFilter
void hideDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();
    
    for(int i = 0; i < _arraySize; i++)
    {
        if(_dominoArray[i].state != _stateFilter) continue;

        oglDominos[getDominoindexByType(_dominoArray[i].leftType, _dominoArray[i].rightType)].visible = FALSE;
    }
}

//avisa o opengl para finalizar suas operações
void exitGame()
{    
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    printf("Thank you for playing!\n");
    printf("\n");
    printf("Game made by:\n\nArthur Naves Pedroso\nCaio Henrique Portella\nLuiz Eduardo Ramirez\nMauricio Macedo Villarnobo\n\n");
    printf("=+=+=+=+=+=+=+=+=+=+=+=+=\n");
    *s_shouldExitGame() = true;
}


void invalidOption()
{
    printf("Invalid selection!\n");
}

/*
Printa os dominos em uma piramide

void printDominoes(Domino* _dominoArray, int _arraySize)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    int columCount= 0;
    int lineCount = 0;

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);

        oglDomino = oglDominos[dominoGObjectIndex];

        oglDomino.visible = TRUE;
        setGObjectPosition(&oglDomino.left, (columCount-0.25f) * 0.2f + (columCount * 0.05f - 0.8f),((-lineCount) * 0.2f) + 0.8f, -1.0f);
        setGObjectPosition(&oglDomino.right, (columCount+0.25f) * 0.2f + (columCount * 0.05f - 0.8f), ((-lineCount) * 0.2f) + 0.8f, -1.0f); 

        oglDominos[dominoGObjectIndex] = oglDomino;

        if(columCount >= 6 - lineCount)
        {
            columCount = 0;
            lineCount++;
        }
        else
        {
            columCount++;
        }
    }  
}
*/