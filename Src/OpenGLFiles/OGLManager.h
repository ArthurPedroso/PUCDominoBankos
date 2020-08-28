#ifndef OGLMANAGER_HEADER
#define OGLMANAGER_HEADER

typedef void (*CBRenderUpdate)(float _deltaTime, int _keyPress);

DominoGObject* getGameDominoes();
int startRender(CBRenderUpdate _callBack);

#endif