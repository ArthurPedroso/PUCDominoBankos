#ifndef OGLMANAGER_HEADER
#define OGLMANAGER_HEADER

#include "gameObject.h"

typedef void (*CBRenderUpdate)(float _deltaTime, int _keyPress);

DominoGObject* getDominoesGObjects();
int startRender(CBRenderUpdate _callBack);

#endif