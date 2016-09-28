#ifndef PACMAN_H
#define PACMAN_H
#include "Game.h"

class Pacman : public Game{
public:
	bool init(Renderer& rendi);
	void frame(Renderer& rkRenderer,Input& input, Timer& timer);
	void deinit(){};

private:
	Node* nodo1;
	Node* nodo2;

	Mesh* cube1;
	Mesh* cube2;
	Mesh* cube3;

	Importador* importador;

	Camera* cam;
};
#endif