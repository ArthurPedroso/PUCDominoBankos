
#include "OGLUtilities.h"
//basico para debugar por terminal
#include <stdio.h>
#include <stdlib.h>

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