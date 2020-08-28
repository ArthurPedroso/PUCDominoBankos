#ifndef GAME_OBJECT_HEADER
#define GAME_OBJECT_HEADER

//basico para debugar por terminal
#include <stdio.h>
#include <stdlib.h>
//incluir antes de glh e glfw3
#include <GL/glew.h>
#include <cglm/mat4.h>

#define GAME_DOMINOES_AMOUNT 28

typedef struct 
{
    mat4 MVP;
    GLuint vertexColorBuffer;
    GLuint vertexBuffer;
    GLuint UVBuffer;
    GLuint textureID;
}GObject;

typedef struct 
{
    GObject right;
    GObject left;
    bool visible;
    //int leftType;
    //int rightType;
}DominoGObject;

void setGObjectPosition(GObject* _outObject, float _x,float _y,float _z);
void initializeGameDominoesArray(DominoGObject* _array, int _arraySize, mat4 _startingMVP);
//Com base no tipo do dominó retorna o indice dele com base em um array ordenado
int getDominoindexByType(int _leftType, int _rightType);

#endif