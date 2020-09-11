#ifndef OGL_UTIL
#define OGL_UTIL

//incluir antes de glh e glfw3
#include <GL/glew.h>
#include<GLFW/glfw3.h>

/*
#define INPUT_KEY1_PRESSED 1
#define INPUT_KEY2_PRESSED 2
#define INPUT_KEY3_PRESSED 3
#define INPUT_KEY4_PRESSED 4
#define INPUT_KEY5_PRESSED 5
#define INPUT_KEY6_PRESSED 6
#define INPUT_KEY7_PRESSED 7
#define INPUT_KEY8_PRESSED 8
#define INPUT_KEY9_PRESSED 9
#define INPUT_NO_KEY_PRESSED 0
*/


#define INPUT_KEY0 0b0000000000000001
#define INPUT_KEY1 0b0000000000000010
#define INPUT_KEY2 0b0000000000000100
#define INPUT_KEY3 0b0000000000001000
#define INPUT_KEY4 0b0000000000010000
#define INPUT_KEY5 0b0000000000100000
#define INPUT_KEY6 0b0000000001000000
#define INPUT_KEY7 0b0000000010000000
#define INPUT_KEY8 0b0000000100000000
#define INPUT_KEY9 0b0000001000000000
#define INPUT_NO_KEY 0b0000000000000000

//Teclas apertadas neste frame apenas
typedef int OGLKeyPress;
//Teclas soltas neste frame apenas
typedef int OGLKeyRelease;
//Teclas ativas neste frame ou em outros
typedef int OGLKeyActive;

GLuint loadBMPImage(const char* _imagePath);
void updateAllKeyStates(GLFWwindow* _window);

int OGLGetKeyDown(int _keyID);
int OGLGetKey(int _keyID);
int OGLGetKeyUp(int _keyID);

#endif