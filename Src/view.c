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
void changeOGLText(char* _newText)
{
    OGLTextData* textData;
    textData = s_getTextData();

    textData->textToDraw = _newText;
}
void OGLManagerUpdateCB(float _deltaTime)
{
    int input;

    if(OGLGetKeyDown(INPUT_KEY0)) input = 0;
    if(OGLGetKeyDown(INPUT_KEY1)) input = 1;
    if(OGLGetKeyDown(INPUT_KEY2)) input = 2;
    if(OGLGetKeyDown(INPUT_KEY3)) input = 3;
    if(OGLGetKeyDown(INPUT_KEY4)) input = 4;
    if(OGLGetKeyDown(INPUT_KEY5)) input = 5;
    if(OGLGetKeyDown(INPUT_KEY6)) input = 6;
    if(OGLGetKeyDown(INPUT_KEY7)) input = 7;
    if(OGLGetKeyDown(INPUT_KEY8)) input = 8;
    if(OGLGetKeyDown(INPUT_KEY9)) input = 9;

    managePlayerChoice(input);
}
void OGLManagerFirstFrameCB()
{
    displayStartingMenu();
}
//-----------Head Funcs-----------//

//-----UI_TEXT-----//
void displayStartingMenu() //inica e printa menu
{
    //O 104 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[104]; 

    strcpy(strBuffer, "Welcome! Let's play Domino!\n");
    strcat(strBuffer, "To get started, select an option:\n");
    strcat(strBuffer, "1- New Game\n");
    strcat(strBuffer, "2- Save\n");
    strcat(strBuffer, "3- Load\n");
    strcat(strBuffer, "4- Exit\n");

    changeOGLText(strBuffer);
}
/*
Old, only to organize dominoes
void screenDisplayOptions() //mostra as opcoes do jogador
{
    changeOGLText("\n1- Show Organized Dominoes\n2- Shuffle Dominoes\n3- Go Back");
}
*/
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
void displayMainGameUIPlayer1Turn()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[105]; 

    strcpy(strBuffer, "Turno do jogador 1\n");
    strcat(strBuffer, "1- Mostrar mao\n");
    strcat(strBuffer, "2- Esconder mao\n");
    strcat(strBuffer, "3- Compra peca\n");
    strcat(strBuffer, "4- Posicionar peca\n");
    strcat(strBuffer, "5- Voltar para o menu principal\n");

    changeOGLText(strBuffer);
}
void displayMainGameUIPlayer2Turn()
{
    //O 76 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[122]; 

    strcpy(strBuffer, "Turno do jogador 1\n");
    strcat(strBuffer, "1- Mostrar mao\n");
    strcat(strBuffer, "2- Esconder mao\n");
    strcat(strBuffer, "3- Compra peca\n");
    strcat(strBuffer, "4- Posicionar peca\n");
    strcat(strBuffer, "5- Voltar para o menu principal\n");

    changeOGLText(strBuffer);
}
//-----UI_TEXT-----//

int screenDisplay() //Ativa o OpenGL e retorna qualquer codigo de erro
{
    return startRender(OGLManagerUpdateCB, OGLManagerFirstFrameCB);
}

void printDominoes(Domino* _dominoArray, int _arraySize)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    for(int i = 0; i < _arraySize; i++)
    {
        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);

        oglDomino = oglDominos[dominoGObjectIndex]; //seleciona um dominó do opengl análogo ao domino do jogo

        oglDomino.visible = TRUE;
        setGObjectPosition(&oglDomino.left, (currentDomino.posX -0.25f) * 0.2f,(currentDomino.posY * 0.2f), -1.0f);
        setGObjectPosition(&oglDomino.right, (currentDomino.posX +0.25f) * 0.2f, (currentDomino.posY  * 0.2f), -1.0f); 

        oglDominos[dominoGObjectIndex] = oglDomino;
    }  
}

void printDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();

    for(int i = 0; i < _arraySize; i++)
    {
        if(_dominoArray[i].state != _stateFilter) continue;

        Domino currentDomino = _dominoArray[i];
        DominoGObject oglDomino;
        int dominoGObjectIndex = getDominoindexByType(currentDomino.leftType, currentDomino.rightType);

        oglDomino = oglDominos[dominoGObjectIndex]; //seleciona um dominó do opengl análogo ao domino do jogo

        oglDomino.visible = TRUE;        
        setDominoGOScale(&oglDomino, 0.4f, 0.4f, 0.4f);
        setDominoGOLocalPosition(&oglDomino, currentDomino.posX, currentDomino.posY, -1.0f);
        //setDominoGOPosition(&oglDomino, currentDomino.posX, currentDomino.posY, -1.0f);

        oglDominos[dominoGObjectIndex] = oglDomino;
    }  

}

void hideAllDominoes()
{
    DominoGObject* oglDominos = s_getDominoesGObjects();
    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        oglDominos[i].visible = false;
    }
}

void hideDominoesBasedOnState(Domino* _dominoArray, int _arraySize, int _stateFilter)
{
    DominoGObject* oglDominos = s_getDominoesGObjects();
    
    for(int i = 0; i < _arraySize; i++)
    {
        if(_dominoArray[i].state != _stateFilter) continue;

        oglDominos[getDominoindexByType(_dominoArray[i].leftType, _dominoArray[i].rightType)].visible = FALSE;
    }
}

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