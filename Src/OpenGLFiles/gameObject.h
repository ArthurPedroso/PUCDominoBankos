#ifndef GAME_OBJECT_HEADER
#define GAME_OBJECT_HEADER

//basico para debugar por terminal
#include <stdio.h>
#include <stdlib.h>
//incluir antes de glh e glfw3
#include <GL/glew.h>
#include <cglm/mat4.h>

typedef struct 
{
    GLuint vertexColorBuffer;
    GLuint vertexBuffer;
    GLuint UVBuffer;
    mat4
}DGObject;


#endif