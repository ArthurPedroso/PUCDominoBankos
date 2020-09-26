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

//Muda o texto do OpengGl
//É possivel mudar a posicao e o tamanho do texto alterando as outras variaveis do "textData" 
void changeOGLText(char* _newText)
{
    OGLTextData* textData;
    textData = s_getTextData();

    textData->textToDraw = _newText;
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
    else if(OGLGetKeyDown(INPUT_KEY_UP)) input = 10;
    else if(OGLGetKeyDown(INPUT_KEY_DOWN)) input = 11;
    else if(OGLGetKeyDown(INPUT_KEY_LEFT)) input = 12;
    else if(OGLGetKeyDown(INPUT_KEY_RIGHT)) input = 13;

    managePlayerChoice(input);//Passa para o coontroller o input atual do jogador
}
//Chamado antes da renderização do primeiro frame
//usar para inicialização
void OGLManagerFirstFrameCB()
{
    displayStartingMenu();
}
//-----------Head Funcs-----------//

//-----UI_TEXT-----//
//Menu Principal
void displayStartingMenu()
{
    //O 104 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[104]; 

    strcpy(strBuffer, "Bem vindo, vamos jogar domino!\n");
    strcat(strBuffer, "Selecione uma opcao:\n");
    strcat(strBuffer, "1- Novo jogo\n");
    strcat(strBuffer, "2- Salvar\n");
    strcat(strBuffer, "3- Carregar\n");
    strcat(strBuffer, "4- Sair\n");

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
    static char strBuffer[122]; 

    strcpy(strBuffer, "Turno do jogador 1\n");
    strcat(strBuffer, "1- Mostrar mao\n");
    strcat(strBuffer, "2- Esconder mao\n");
    strcat(strBuffer, "3- Compra peca\n");
    strcat(strBuffer, "4- Posicionar peca\n");
    strcat(strBuffer, "5- Voltar para o menu principal\n");

    changeOGLText(strBuffer);
}

//Menu de gameplay do jogador 2
void displayMainGameUIPlayer2Turn()
{
    //O 122 corresponde a quantidade total de caracteres, usar http://string-functions.com/length.aspx para descobrir o tamanho da string.
    //O static é necessário para que a memória alocada no ponteiro srtBuffer não seja desalocada automaticamente quando a funcão chegar no fim
    static char strBuffer[122]; 

    strcpy(strBuffer, "Turno do jogador 2\n");
    strcat(strBuffer, "1- Mostrar mao\n");
    strcat(strBuffer, "2- Esconder mao\n");
    strcat(strBuffer, "3- Compra peca\n");
    strcat(strBuffer, "4- Posicionar peca\n");
    strcat(strBuffer, "5- Voltar para o menu principal\n");

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
    strcat(strBuffer, "4- Voltar\n");

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
    strcat(strBuffer, "4- Voltar\n");

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
        setGObjectPosition(&oglDomino.left, (currentDomino.posX -0.25f) * 0.2f,(currentDomino.posY * 0.2f), -1.0f);
        setGObjectPosition(&oglDomino.right, (currentDomino.posX +0.25f) * 0.2f, (currentDomino.posY  * 0.2f), -1.0f); 

        oglDominos[dominoGObjectIndex] = oglDomino;
    }  
}

//Recebe um array de dominós e exibe seus equivalentes pelo OpenGL, exibindo apenas os dominos com o estado de "_stateFilter"
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
        oglDomino.colorID = currentDomino.playerColorID;
        oglDomino.visible = TRUE;        
        setDominoGOScale(&oglDomino, 0.4f, 0.4f, 0.4f);
        setDominoGOLocalPosition(&oglDomino, currentDomino.posX, currentDomino.posY * 1.3333333f, -1.0f);
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