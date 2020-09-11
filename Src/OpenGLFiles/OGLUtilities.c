
#include "OGLUtilities.h"

//basico para debugar por terminal
#include <stdio.h>
#include <stdlib.h>

void updateActiveKeyState(int _keyID, OGLKeyPress* _outKeyPress, OGLKeyActive* _outKeyActive, OGLKeyRelease* _outKeyRelease)
{
	if(!(int)(_keyID & *_outKeyActive)) //se a tecla no ultimo frame estava em estado "neutro"
	{
		*_outKeyPress += _keyID; //a tecla agora está no estado "press"
		*_outKeyActive += _keyID; //a tecla agora está no estado "active"
		
		if((int)(_keyID & *_outKeyRelease)) //situacao rara, mas se a tecla no ultimo frame estava no estado "release", agora ela sai desse estado
		{
			*_outKeyRelease -= _keyID; //a tecla não está mais no estado "release"
		}
	}
	else if((int)(_keyID & *_outKeyPress)) //se a tecla no ultimo frame era considerada como press
	{
		*_outKeyPress -= _keyID; //a tecla não está mais no estado "press"
	}
}
void updateUnactiveKeyState(int _keyID, OGLKeyPress* _outKeyPress, OGLKeyActive* _outKeyActive, OGLKeyRelease* _outKeyRelease)
{
	if((int)(_keyID & *_outKeyActive)) //se a tecla no ultimo frame estava em estado "active"
	{
		*_outKeyRelease += _keyID; //a tecla agora está no estado "release"
		*_outKeyActive -= _keyID; //a tecla agora está no estado "unactive"

		if((int)(_keyID & *_outKeyPress)) //situacao rara, mas se a tecla no ultimo frame estava no estado "pressed", agora ela sai desse estado
		{
			*_outKeyPress -= _keyID; //a tecla não está mais no estado "release"
		}
	}
	else if((int)(_keyID & *_outKeyRelease)) //se a tecla no ultimo frame era considerada como release
	{
		*_outKeyRelease -= _keyID; //a tecla não está mais no estado "release"
	}
}


void s_getLastFrameKeysStates(OGLKeyPress** _outKeyPress, OGLKeyActive** _outKeyActive, OGLKeyRelease** _outKeyRelease)
{
	static OGLKeyPress keyPress = INPUT_NO_KEY; 
	static OGLKeyActive keyActive = INPUT_NO_KEY; 
	static OGLKeyRelease keyRelease = INPUT_NO_KEY; 

	*_outKeyPress = &keyPress;
	*_outKeyActive = &keyActive;
	*_outKeyRelease = &keyRelease;
}
//-----HEADER FUNCS-----//

GLuint loadBMPImage(const char* _imagePath)
{
	GLuint textureID;
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3(RGB)
	// Actual RGB data
	unsigned char * data;

	// Open the file
	FILE * file = fopen(_imagePath,"rb");
	if (!file) { printf("Image could not be opened\n"); return 0; }

	//check for header
	if (fread(header, 1, 54, file) !=54) // If not 54 bytes read : problem
	{		
    	printf("Not a correct BMP file\n");
    	return 0;
	}
	//check for BM in header
	if ( header[0]!='B' || header[1]!='M' )
	{
    	printf("Not a correct BMP file\n");
    	return 0;
	}

	// Read ints from the header byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize==0) imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0) dataPos=54; // The BMP header is done that way

	// Baseado nas informacoes adquiridas do header
	// agora é possivel alocar memoria para armazenar a imagem com base no "imageSize"
	// Create a buffer
	data = malloc(sizeof(unsigned char) * imageSize);

	// Read the actual data from the file into the buffer
	fread(data, 1, imageSize, file);

	//Everything is in memory now, the file can be closed
	fclose(file);


	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// When MAGnifying the image (no bigger mipmap available), use LINEAR filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// When MINifying the image, use a LINEAR blend of two mipmaps, each filtered LINEARLY too
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	// Generate mipmaps, by the way.
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}

void updateAllKeyStates(GLFWwindow* _window)
{
	OGLKeyPress* keyPress = NULL;
	OGLKeyActive* keyActive = NULL;
	OGLKeyRelease* keyRelease = NULL;

	s_getLastFrameKeysStates(&keyPress, &keyActive, &keyRelease);

	if(glfwGetKey(_window, GLFW_KEY_0)) 
		updateActiveKeyState(INPUT_KEY0, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY0, keyPress, keyActive, keyRelease);
		
	if(glfwGetKey(_window, GLFW_KEY_1))
		updateActiveKeyState(INPUT_KEY1, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY1, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_2))
		updateActiveKeyState(INPUT_KEY2, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY2, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_3))
		updateActiveKeyState(INPUT_KEY3, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY3, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_4))
		updateActiveKeyState(INPUT_KEY4, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY4, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_5))
		updateActiveKeyState(INPUT_KEY5, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY5, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_6))
		updateActiveKeyState(INPUT_KEY6, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY6, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_7))
		updateActiveKeyState(INPUT_KEY7, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY7, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_8))
		updateActiveKeyState(INPUT_KEY8, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY8, keyPress, keyActive, keyRelease);
		
	
	if(glfwGetKey(_window, GLFW_KEY_9))
		updateActiveKeyState(INPUT_KEY9, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY9, keyPress, keyActive, keyRelease);		
		
	
	if(glfwGetKey(_window, GLFW_KEY_UP))
		updateActiveKeyState(INPUT_KEY_UP, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY_UP, keyPress, keyActive, keyRelease);		
		
	
	if(glfwGetKey(_window, GLFW_KEY_DOWN))
		updateActiveKeyState(INPUT_KEY_DOWN, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY_DOWN, keyPress, keyActive, keyRelease);		
		
	
	if(glfwGetKey(_window, GLFW_KEY_LEFT))
		updateActiveKeyState(INPUT_KEY_LEFT, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY_LEFT, keyPress, keyActive, keyRelease);		
		
	
	if(glfwGetKey(_window, GLFW_KEY_RIGHT))
		updateActiveKeyState(INPUT_KEY_RIGHT, keyPress, keyActive, keyRelease);
	else
		updateUnactiveKeyState(INPUT_KEY_RIGHT, keyPress, keyActive, keyRelease);		
	
}

int OGLGetKeyDown(int _keyID)
{
	OGLKeyPress* keyPress = NULL;
	OGLKeyActive* keyActive = NULL;
	OGLKeyRelease* keyRelease = NULL;

	s_getLastFrameKeysStates(&keyPress, &keyActive, &keyRelease);

	return (int)(_keyID & *keyPress);
}
int OGLGetKey(int _keyID)
{
	OGLKeyPress* keyPress = NULL;
	OGLKeyActive* keyActive = NULL;
	OGLKeyRelease* keyRelease = NULL;

	s_getLastFrameKeysStates(&keyPress, &keyActive, &keyRelease);

	return (int)(_keyID & *keyActive);
}
int OGLGetKeyUp(int _keyID)
{
	OGLKeyPress* keyPress = NULL;
	OGLKeyActive* keyActive = NULL;
	OGLKeyRelease* keyRelease = NULL;

	s_getLastFrameKeysStates(&keyPress, &keyActive, &keyRelease);

	return (int)(_keyID & *keyRelease);
}