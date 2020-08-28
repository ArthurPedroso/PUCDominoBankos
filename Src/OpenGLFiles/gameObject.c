#include "gameObject.h"
#include "OGLUtilities.h"

DominoGObject getEmptyDGObject(mat4 _startingMVP)
{
    DominoGObject newDomino;
    GObject newGObject;

    glm_mat4_copy(_startingMVP, newGObject.MVP);
    newGObject.UVBuffer = 0;
    newGObject.vertexBuffer = 0;
    newGObject.vertexColorBuffer = 0;
    newGObject.textureID = 0;

    newDomino.left = newGObject;
    newDomino.right = newGObject;
    newDomino.visible = false;

    return newDomino;
}

//-----HEADER FUNCS-----//


void initializeGameDominoesArray(DominoGObject* _array, int _arraySize, mat4 _startingMVP)
{
    DominoGObject* allGameDominoes = _array;
    DominoGObject emptyObj = getEmptyDGObject(_startingMVP);

    int columCount = 0;
    int lineCount = 0;

    GLuint dominoesTextures[7]; //preguica forte de fazer um loop com edicao da string do path
    dominoesTextures[0] = loadBMPImage("Assets/Dominoes/domino0.bmp");
    dominoesTextures[1] = loadBMPImage("Assets/Dominoes/domino1.bmp");
    dominoesTextures[2] = loadBMPImage("Assets/Dominoes/domino2.bmp");
    dominoesTextures[3] = loadBMPImage("Assets/Dominoes/domino3.bmp");
    dominoesTextures[4] = loadBMPImage("Assets/Dominoes/domino4.bmp");
    dominoesTextures[5] = loadBMPImage("Assets/Dominoes/domino5.bmp");
    dominoesTextures[6] = loadBMPImage("Assets/Dominoes/domino6.bmp");

    for(int i = 0; i < GAME_DOMINOES_AMOUNT; i++)
    {
        allGameDominoes[i] = emptyObj;

        allGameDominoes[i].right.textureID = dominoesTextures[columCount + lineCount];
        allGameDominoes[i].left.textureID = dominoesTextures[lineCount];

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

