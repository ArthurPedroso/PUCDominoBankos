#include"OGLManager.h"

//basico para debugar por terminal
#include <stdio.h>
#include <stdlib.h>
//incluir antes de glh e glfw3
#include<GL/glew.h>
//GLFW ajuda muito na hora de mostrar uma janelona da massa
#include<GLFW/glfw3.h>
//Lib de math 3d
//#include<glm/glm.hpp>
#include<cglm/mat4.h>
#include<cglm/vec3.h>
#include<cglm/cam.h>
#include<cglm/affine.h>
//#include<cglm/vec3.h>
//Lib de transformacao de matriz
//#include <glm/gtc/matrix_transform.hpp>
//#include<cglm/ma
//Time para ser passado como uniform para glsl
#include <time.h>

#include"CppFiles/shader.h" //usado para carregar shaders

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
void sendTriangleGeometryToOpenGL()
{
	static const GLfloat triangleGeometryBufferData[] = 
	{
   	-1.0f, -1.0f, 0.0f,
   	1.0f, -1.0f, 0.0f,
   	0.0f,  1.0f, 0.0f,
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleGeometryBufferData), triangleGeometryBufferData, GL_STATIC_DRAW);
}
void sendQuadGeometryToOpenGL()
{
	static const GLfloat quadGeometryBufferData[] = 
	{
   		-1.0f, -1.0f, 0.0f,
   		1.0f, -1.0f, 0.0f,
   		-1.0f,  1.0f, 0.0f,//end triangle 1
		-1.0f,  1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,//end triangle 2
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(quadGeometryBufferData), quadGeometryBufferData, GL_STATIC_DRAW);
}
void sendCubeGeometryToOpenGL()
{
	static const GLfloat cubeGeometryBufferData[] = 
	{
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeGeometryBufferData), cubeGeometryBufferData, GL_STATIC_DRAW); 	
}
GLuint getVertexBuffer()
{	
	// This will identify our vertex buffer
	GLuint vertexBuffer;
	// Generate 1 buffer, put the resulting identifier in vertexBuffer
	glGenBuffers(1, &vertexBuffer);
	// The following commands will talk about our 'vertexBuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// Give our vertices to OpenGL.
	sendQuadGeometryToOpenGL();
	//sendTriangleGeometryToOpenGL();

	return vertexBuffer;
}
GLuint getUVBuffer()
{
	GLuint uvBuffer = 0;
	// Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
	//UV para um cubo
	/*
		-1.0f, -1.0f, 0.0f,
   		1.0f, -1.0f, 0.0f,
   		-1.0f,  1.0f, 0.0f,//end triangle 1
		-1.0f,  1.0f, 0.0f,
		1.0f,  -1.0f, 0.0f,
		1.0f,  1.0f, 0.0f,//end triangle 2
	*/
	static const GLfloat g_uv_buffer_data[] =
	{
    	0.0f, 0.0f,
		1.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 1.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,
	};

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	return uvBuffer;
}
GLuint getVertexColorBuffer()
{
	GLuint colorbuffer;

	// One color for each vertex. They were generated randomly.
	// cube vertex color
	static const GLfloat g_color_buffer_data[] = 
	{
    	0.583f,  0.771f,  0.014f,
    	0.609f,  0.115f,  0.436f,
    	0.327f,  0.483f,  0.844f,
    	0.822f,  0.569f,  0.201f,
    	0.435f,  0.602f,  0.223f,
    	0.310f,  0.747f,  0.185f,
    	0.597f,  0.770f,  0.761f,
    	0.559f,  0.436f,  0.730f,
    	0.359f,  0.583f,  0.152f,
    	0.483f,  0.596f,  0.789f,
    	0.559f,  0.861f,  0.639f,
    	0.195f,  0.548f,  0.859f,
    	0.014f,  0.184f,  0.576f,
    	0.771f,  0.328f,  0.970f,
    	0.406f,  0.615f,  0.116f,
    	0.676f,  0.977f,  0.133f,
    	0.971f,  0.572f,  0.833f,
    	0.140f,  0.616f,  0.489f,
    	0.997f,  0.513f,  0.064f,
    	0.945f,  0.719f,  0.592f,
    	0.543f,  0.021f,  0.978f,
    	0.279f,  0.317f,  0.505f,
    	0.167f,  0.620f,  0.077f,
    	0.347f,  0.857f,  0.137f,
    	0.055f,  0.953f,  0.042f,
    	0.714f,  0.505f,  0.345f,
    	0.783f,  0.290f,  0.734f,
    	0.722f,  0.645f,  0.174f,
    	0.302f,  0.455f,  0.848f,
    	0.225f,  0.587f,  0.040f,
    	0.517f,  0.713f,  0.338f,
    	0.053f,  0.959f,  0.120f,
    	0.393f,  0.621f,  0.362f,
    	0.673f,  0.211f,  0.457f,
    	0.820f,  0.883f,  0.371f,
    	0.982f,  0.099f,  0.879f
	};

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	return colorbuffer;
}
int createEmptyWindow(GLFWwindow** _outWindow)// 
{
	// Initialise GLFW
	glewExperimental = GL_TRUE; // Needed for core profile
	if( !glfwInit() )
	{
    	fprintf( stderr, "Failed to initialize GLFW\n" );
    	return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow( 1280, 960, "Domino Bankos", NULL, NULL);
	if( window == NULL )
	{
    	fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
    	glfwTerminate();
    	return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental=true; // Needed in core profile
	if (glewInit() != GLEW_OK) 
	{
    	fprintf(stderr, "Failed to initialize GLEW\n");
    	return -1;
	}
	*_outWindow = window;

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	//-----VAO-----//
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	//-----VAO-----// 
	return 0;
}

void handleShader(GLuint _shaderID, GLuint _textureID, GLuint _mvpHandler, 
				GLuint _textureHandler, GLuint _timeHandler, mat4 _mvp, float _currentTime)
{
	//Usar o shader especificado
	glUseProgram(_shaderID);
	//-----SET UNIFORM VALUES-----//
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(_mvpHandler, 1, GL_FALSE, &_mvp[0][0]);
	glUniform1f(_timeHandler, _currentTime);
	//-----SET UNIFORM VALUES-----//

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(_textureHandler, 0);

}
void drawObject(GLuint _vertexColorBuffer, GLuint _vertexBuffer, GLuint _uvBuffer,  mat4 _mvp)
{
	

	
    //-----1st attribute buffer : vertices-----//
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer
	(
   		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
   		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
    //-----1st attribute buffer : vertices-----//
	//-----2st attribute buffer : vertexcolor-----//
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexColorBuffer);
	glVertexAttribPointer
	(
   		1,                  // attribute. No particular reason for 1, but must match the layout in the shader.
   		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
    //-----2st attribute buffer : vertexcolor-----//
	//-----3st attribute buffer : UV-----//
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer
	(
   		2,                  // attribute. No particular reason for 2, but must match the layout in the shader.
   		2,                  // size: U+V
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
    //-----3st attribute buffer : UV-----//
	//DRAW CALL
	glDrawArrays(GL_TRIANGLES, 0, 36); // colocar quantidade de vertices
	//tem que ter um para cada atributo
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

}

int drawLoop(GLFWwindow* _window)
{
	GLuint programID = LoadShaders("Shaders/BasicVertex.glsl","Shaders/BasicFragment.glsl");

	//-----UNIFORM HANDLES-----//
	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MVPHandler = glGetUniformLocation(programID, "MVP");	
	//Time para shaders
	GLint TimeHandler = glGetUniformLocation(programID, "Time");
	//texture handler
	GLint TextureHandler = glGetUniformLocation(programID, "textureSampler");
	//-----UNIFORM HANDLES-----//

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//zoado do site glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);
	mat4 Projection; 
    glm_perspective (glm_rad(45.0f), 4.0f / 3.0f, 0.1f, 100.0f, Projection);
	// Or, for an ortho camera :
	//mat4 Projection = ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
    
    
    
	// Camera matrix
	mat4 View;
    glm_lookat
    (
        (vec3){0.0f,  8.0f,  -20.0f}, // Camera is at (x,y,z), in World Space
        (vec3){0.0f,  0.0f,  0.0f}, // and looks at the origin
        (vec3){0.0f,  1.0f,  0.0f},
        View // Head is up (set to 0,-1,0 to look upside-down)
    );
  
	// Model matrix : an identity matrix (model will be at the origin)
    
	mat4 Model;
    glm_mat4_copy(GLM_MAT4_IDENTITY, Model);
    glm_scale(Model, (vec3){2.0f,2.0f,2.0f});

	//
    //Model = 
	// Our ModelViewProjection : multiplication of our 3 matrices
	
    mat4 mvp; // Remember, matrix multiplication is the other way around
    glm_mat4_mul(Projection, View, mvp);
    glm_mat4_mul(mvp, Model, mvp); 

	mat4 mvp2;
	glm_mat4_mul(Projection, View, mvp2);
    glm_mat4_mul(mvp2, Model, mvp2); 
	glm_translate(mvp2, (vec3){3.0f,3.0f,0.0f});
	//-----VERTEX_BUFFER-----//
	GLuint vertexBuffer = getVertexBuffer();
	//-----VERTEX_BUFFER-----//

	//-----VERTEX_COLOR-----//
	GLuint vertexColorBuffer = getVertexColorBuffer();
	//-----VERTEX_COLOR-----//

	//-----LOAD_TEXTURE-----//
	GLuint textureID = loadBMPImage("Assets/uvtemplate.bmp");
	GLuint uvBuffer = getUVBuffer();
	//-----LOAD_TEXTURE-----//

	//Time var
	time_t initialTime = time(0);
	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	double lastTime = glfwGetTime();
 	int nbFrames = 0;
	do
	{
    	// Measure speed
		//Update time
    	double currentGlfwTime = glfwGetTime();
    	nbFrames++;
    	if ( currentGlfwTime - lastTime >= 1.0 )
		{ // If last prinf() was more than 1 sec ago
    	 	// printf and reset timer
    	    printf("%f ms/frame\n", 1000.0 / ((double)nbFrames));
    	    nbFrames = 0;
    	    lastTime += 1.0;
    	}


    	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//-----DRAW CALLS START-----//

		handleShader(programID, textureID, MVPHandler, TextureHandler, TimeHandler, mvp, (float)currentGlfwTime);
		drawObject(vertexColorBuffer, vertexBuffer, uvBuffer, mvp);

		handleShader(programID, textureID, MVPHandler, TextureHandler, TimeHandler, mvp2, (float)currentGlfwTime);
		drawObject(vertexColorBuffer, vertexBuffer, uvBuffer, mvp2);

		//-----DRAW CALLS END-----//

    	// Swap buffers
    	glfwSwapBuffers(_window);
    	glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey(_window, GLFW_KEY_ESCAPE ) != GLFW_PRESS && glfwWindowShouldClose(_window) == 0 );

	return 0;
}

int startRender()
{
	GLFWwindow* window;

	printf("\nCriando janela\n");
	if(createEmptyWindow(&window) == -1) return -1; //criacao de janela

	printf("\nesperando input de teclado\n");
	drawLoop(window);
	return 0;
}