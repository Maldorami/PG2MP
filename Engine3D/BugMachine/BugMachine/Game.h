#ifndef GAME_H
#define GAME_H

#include "Renderer.h"
#include "pg1_directinput.h"
#include "Quad.h"
#include "Sprite.h"
#include "Map.h"
#include "Text.h"
#include "Camera.h"

#define DLLexport __declspec(dllexport)

class Game{
public:
	DLLexport virtual bool init(Renderer& rendi) = 0;
	DLLexport virtual void frame(Renderer& rkRenderer,Input& input, Timer& timer) = 0;
	DLLexport virtual void deinit() = 0;
	bool isDone() const;
	DLLexport void setDone(bool bDone);
	Camera camera;

private:
	bool m_bDone;
};
#endif