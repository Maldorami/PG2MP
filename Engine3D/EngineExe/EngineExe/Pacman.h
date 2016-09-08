#ifndef PACMAN_H
#define PACMAN_H
#include "Game.h"

class Pacman : public Game{
public:
	bool init(Renderer& rendi);
	void frame(Renderer& rkRenderer,Input& input, Timer& timer);
	void deinit(){};

private:	
	Mesh* cube;
	Mesh* piramide;
	Mesh* quad;
	Camera* cam;
};
#endif