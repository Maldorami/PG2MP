#ifndef PACMAN_H
#define PACMAN_H
#include "Game.h"

class Pacman : public Game{
public:
	bool init(Renderer& rendi);
	void frame(Renderer& rkRenderer,Input& input, Timer& timer);
	void deinit(){};

private:
	Animation walk;
	Animation iddle;
	Sprite player;
	Map mapa;
	Text timerText;

	Camera* cam;
};
#endif