#include "gameObject.h"
#include "OGLUtilities.h"
#include <cglm/affine.h>

DominoGObject getEmptyDGObject(mat4 _startingMVP)
{
    DominoGObject newDomino;
    GObject newGObject;

    initializeGObject(&newGObject, _startingMVP);

    newDomino.left = newGObject;
    newDomino.right = newGObject;
    newDomino.visible = false;

    return newDomino;
}

//-----HEADER FUNCS-----//

int getDominoindexByType(int _leftType, int _rightType)
{
    //soma dos termos de uma pa: sn = n(a1 + an)/2
    //termo geral da pa da linha da lista de domino: an = a1 - (n - 1)
    //normalizar o tipo da direita: rightType - leftType
    return ((_leftType * (15 - _leftType))/2) + (_rightType - _leftType);
}
void initializeGObject(GObject* _outGObject, mat4 _startingMVP)
{
    GObject newGObject;

    glm_mat4_copy(_startingMVP, newGObject.MVP);
    newGObject.UVBuffer = 0;
    newGObject.vertexBuffer = 0;
    newGObject.vertexColorBuffer = 0;
    newGObject.textureID = 0;

    *_outGObject = newGObject;
}
void initializeGameDominoesArray(DominoGObject* _array, int _arraySize, mat4 _startingMVP)
{
    DominoGObject* allGameDominoes = _array;
    DominoGObject emptyObj = getEmptyDGObject(_startingMVP);

    int columCount = 0;
    int lineCount = 0;
    
    glm_translate_z(emptyObj.left.MVP, 1.0f);
    glm_translate_z(emptyObj.right.MVP, 1.0f);

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
        //allGameDominoes[i].rightType = columCount + lineCount;
        //allGameDominoes[i].leftType = lineCount;
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

void setGObjectPosition(GObject* _outObject, float _x,float _y,float _z)
{
    _outObject->MVP[3][0] = _x;
    _outObject->MVP[3][1] = _y;
    _outObject->MVP[3][2] = _z;
}