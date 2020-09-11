#ifndef OGLMANAGER_HEADER
#define OGLMANAGER_HEADER

#include "gameObject.h"
#include "OGLUtilities.h"


typedef void (*CBRenderUpdate)(float _deltaTime);
typedef void (*CBBeforeFirstFrame)();

typedef struct 
{
    char* textToDraw;
    float xPos;
    float yPos;
    float scale;
}OGLTextData;


DominoGObject* s_getDominoesGObjects();
OGLTextData* s_getTextData();
bool* s_shouldExitGame();
int startRender(CBRenderUpdate _updateCallBack, CBBeforeFirstFrame _firstFrameCallBack);

#endif