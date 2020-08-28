#ifndef OGLMANAGER_HEADER
#define OGLMANAGER_HEADER

#include "gameObject.h"

#define INPUT_KEY1_PRESSED 1
#define INPUT_KEY2_PRESSED 2
#define INPUT_KEY3_PRESSED 3
#define INPUT_KEY4_PRESSED 4
#define INPUT_KEY5_PRESSED 5
#define INPUT_NO_KEY_PRESSED 0

typedef void (*CBRenderUpdate)(float _deltaTime, int _keyPress);
typedef void (*CBBeforeFirstFrame)();

typedef struct 
{
    char* textToDraw;
    float xPos;
    float yPos;
    float scale;
}OGLTextData;


DominoGObject* getDominoesGObjects();
OGLTextData* getTextData();
bool* shouldExitGame();
int startRender(CBRenderUpdate _updateCallBack, CBBeforeFirstFrame _firstFrameCallBack);

#endif