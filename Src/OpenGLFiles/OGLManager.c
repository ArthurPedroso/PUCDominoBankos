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

#include "CppFiles/shader.h" //usado para carregar shaders]
#define GLT_IMPLEMENTATION
#include "CppFiles/gltext.h"
//#include "CppFiles/text2D.h"

#define WIDTH_PXLS 1280
#define HEIGTH_PXLS 960


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
	window = glfwCreateWindow( WIDTH_PXLS, HEIGTH_PXLS, "Domino Bankos", NULL, NULL);
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
				GLuint _textureHandler,  GLuint _timeHandler, GLuint _dominoColorIDHandler, mat4 _mvp, float _currentTime, int _dominoColorID)
{
	//Usar o shader especificado
	glUseProgram(_shaderID);
	//-----SET UNIFORM VALUES-----//
	// Send our transformation to the currently bound shader, in the "MVP" uniform
	// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
	glUniformMatrix4fv(_mvpHandler, 1, GL_FALSE, &_mvp[0][0]);
	glUniform1f(_timeHandler, _currentTime);
	glUniform1i(_dominoColorIDHandler, _dominoColorID);
	//-----SET UNIFORM VALUES-----//

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureID);

	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(_textureHandler, 0);

}
void drawObject(GLuint _vertexBuffer, GLuint _uvBuffer)
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
	//-----3st attribute buffer : UV-----//
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _uvBuffer);
	glVertexAttribPointer
	(
   		1,                  // attribute. No particular reason for 2, but must match the layout in the shader.
   		2,                  // size: U+V
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
    //-----3st attribute buffer : UV-----//
	//DRAW CALL
	glDrawArrays(GL_TRIANGLES, 0, 6); // colocar quantidade de vertices
	//tem que ter um para cada atributo
	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1); //removido vertex color
	glDisableVertexAttribArray(1);

}
void debugFPS(double* _outLastTime, int* _outNbFrames)
{
	double lastTime = *_outLastTime;
	int nbFrames = *_outNbFrames;
	// Measure speed
	//Update time
    double currentGlfwTime = glfwGetTime();
    nbFrames++;
    if (currentGlfwTime - lastTime >= 1.0)
	{ 
		// If last prinf() was more than 1 sec ago
    	// printf and reset timer
    	printf("%f ms/frame\n", 1000.0 / (double)(nbFrames));
    	nbFrames = 0;
    	lastTime += 1.0;
    }

	*_outLastTime = lastTime;
	*_outNbFrames = nbFrames;
}
/*
int getGameInput(GLFWwindow* _window)
{
	if(glfwGetKey(_window, GLFW_KEY_1)) return INPUT_KEY1_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_2)) return INPUT_KEY2_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_3)) return INPUT_KEY3_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_4)) return INPUT_KEY4_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_5)) return INPUT_KEY5_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_6)) return INPUT_KEY6_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_7)) return INPUT_KEY7_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_8)) return INPUT_KEY8_PRESSED;
	if(glfwGetKey(_window, GLFW_KEY_9)) return INPUT_KEY9_PRESSED;

	return INPUT_NO_KEY_PRESSED;
}
*/

void updateCamera()
{

}
int drawLoop(GLFWwindow* _window, CBRenderUpdate _updateCallBack, CBBeforeFirstFrame _firstFrameCallBack)
{

	GLuint programID = LoadShaders("Shaders/BasicVertex.glsl","Shaders/BasicFragment.glsl");

	//-----UNIFORM HANDLES-----//
	// Get a handle for our "MVP" uniform
	// Only during the initialisation
	GLuint MVPHandler = glGetUniformLocation(programID, "MVP");	
	//Time para shaders
	GLint TimeHandler = glGetUniformLocation(programID, "Time");

	GLuint DominoColorIDHandler = glGetUniformLocation(programID, "dominoColorID");
	//texture handler
	GLint TextureHandler = glGetUniformLocation(programID, "textureSampler");
	//-----UNIFORM HANDLES-----//

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	//zoado do site glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float) width / (float)height, 0.1f, 100.0f);
	//mat4 Projection; 
    //glm_perspective (glm_rad(45.0f), 4.0f / 3.0f, 0.1f, 100.0f, Projection);
	// Or, for an ortho camera :
	mat4 Projection; // = ortho(-10.0f,10.0f,-10.0f,10.0f,0.0f,100.0f); // In world coordinates
    glm_ortho(-20.0f,20.0f,-15.0f,15.0f,0.0f,100.0f, Projection);
    
	// Camera matrix
	mat4 View;
    glm_lookat
    (
        (vec3){0.0f,  0.0f,  -50.0f}, // Camera is at (x,y,z), in World Space
        (vec3){0.0f,  0.0f,  0.0f}, // and looks at the origin
        (vec3){0.0f,  1.0f,  0.0f},
        View // Head is up (set to 0,-1,0 to look upside-down)
    );
  
	// Model matrix : an identity matrix (model will be at the origin)
    
	mat4 Model;
    glm_mat4_copy(GLM_MAT4_IDENTITY, Model);
    glm_scale(Model, (vec3){2.0f,2.0f,2.0f});

	//getGameInput
    //Model = 
	// Our ModelViewProjection : multiplication of our 3 matrices
	
    mat4 mvp; // Remember, matrix multiplication is the other way around
    glm_mat4_mul(Projection, View, mvp);
    glm_mat4_mul(mvp, Model, mvp); 


	//-----VERTEX_BUFFER-----//
	GLuint vertexBuffer = getVertexBuffer(); //get quad geometry by default
	//-----VERTEX_BUFFER-----//

	//-----UV_BUFFER-----//
	GLuint uvBuffer = getUVBuffer();//quad uv
	//-----UV_BUFFER-----//



	//GAME DATA INIT//
	GObject backGround;
	OGLTextData* textData;
	initializeGObject(&backGround, mvp);
	backGround.textureID = loadBMPImage("Assets/background.bmp");
	glm_scale(backGround.MVP, (vec3){10.0f, 10.0f, 1.0f});
	glm_translate(backGround.MVP, (vec3){0.0f, 0.0f, 20.0f});

	initializeGameDominoesArray(s_getDominoesGObjects(), GAME_DOMINOES_AMOUNT, mvp);
	DominoGObject* dominoes = s_getDominoesGObjects();


	textData = s_getTextData();
	textData->scale = 1.5f;
	textData->textToDraw = "";
	textData->xPos = 0.0f;
	textData->yPos = 760.0f;
	//GAME DATA INIT//

	// Initialize glText
	if (!gltInit())
	{
		fprintf(stderr, "Failed to initialize glText\n");
		glfwTerminate();
		return EXIT_FAILURE;
	}


	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);

	double lastFrameTime = glfwGetTime();
	double lastTime = lastFrameTime;
	double currentTime = 0;
	double deltaTime = 0;
 	int nbFrames = 0;
	GLTtext *text = NULL;

	_firstFrameCallBack();
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	do
	{    			
    	// Swap buffers
    	glfwSwapBuffers(_window);
    	glfwPollEvents();
		
		//-----SET DELTA TIME-----//
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		//-----SET DELTA TIME-----//

		//-----DEBUG-----//
		debugFPS(&lastTime, &nbFrames);
		//-----DEBUG-----//

		//-----UPDATE INPUT-----//
		updateAllKeyStates(_window);
		//-----UPDATE INPUT-----//

		//-----GAME LOGIC UPDATE-----//
		_updateCallBack(deltaTime);
		//-----GAME LOGIC UPDATE-----//

    	// Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//-----DRAW CALLS START-----//

		//-----BACKGROUND-----//
		handleShader(programID, backGround.textureID, MVPHandler, 
						TextureHandler, TimeHandler, DominoColorIDHandler, backGround.MVP, (float)currentTime, 0);
		drawObject(vertexBuffer, uvBuffer);
		//-----BACKGROUND-----//


		//-----DOMINOES-----//
		for(int j = 0; j < GAME_DOMINOES_AMOUNT; j++)
		{
			DominoGObject currentDomino = dominoes[j];
			if(!currentDomino.visible) continue;
			//left
			handleShader(programID, currentDomino.left.textureID, MVPHandler, 
						TextureHandler, TimeHandler, DominoColorIDHandler, currentDomino.left.MVP, (float)currentTime, currentDomino.colorID);
			drawObject(vertexBuffer, uvBuffer);

			//right
			handleShader(programID, currentDomino.right.textureID, MVPHandler, 
						TextureHandler, TimeHandler, DominoColorIDHandler, currentDomino.right.MVP, (float)currentTime, currentDomino.colorID);
			drawObject(vertexBuffer, uvBuffer);
		}
		//-----DOMINOES-----//


		
		//-----TEXT-----//
		if(textData->textToDraw[0] != '\0')
		{
			// Enable depth test
			glDisable(GL_DEPTH_TEST);

			text = gltCreateText();
			gltSetText(text, textData->textToDraw);
			//glDisable(GL_DEPTH_TEST);
			// Begin text drawing (this for instance calls glUseProgram)
			gltBeginDraw();
			// Draw any amount of text between begin and end
			gltColor(1.0f, 1.0f, 1.0f, 1.0f);
			gltDrawText2D(text, textData->xPos, textData->yPos, textData->scale);
			// Finish drawing text
			gltEndDraw();
			//glEnable(GL_DEPTH_TEST);

			// Enable depth test
			glEnable(GL_DEPTH_TEST);
		}
		//-----TEXT-----//
		
		//-----DRAW CALLS END-----//

	} // Check if the ESC key was pressed or the window was closed
	while(glfwWindowShouldClose(_window) == 0 && !(*s_shouldExitGame()));

	
	// Deleting text
	gltDeleteText(text);
	gltTerminate();

	return 0;
}
//-----HEADER FUNCS-----//
bool* s_shouldExitGame()
{
	static bool exitGame = false;

	return &exitGame;
}
//Retorna um array de tamanho 28, com todos os dominos do jogo em ordem crescente
DominoGObject* s_getDominoesGObjects()
{
	static DominoGObject allGameDominoes[GAME_DOMINOES_AMOUNT];
	
	return allGameDominoes;
}
OGLTextData* s_getTextData()
{
	static OGLTextData textData;

	return &textData;
}

int startRender(CBRenderUpdate _updateCallBack, CBBeforeFirstFrame _firstFrameCallBack)
{	
	GLFWwindow* window;
	
	printf("\nCriando janela\n");
	if(createEmptyWindow(&window) == -1) return -1; //criacao de janela

	printf("\nesperando input de teclado\n");
	drawLoop(window, _updateCallBack, _firstFrameCallBack);
	return 0;
}