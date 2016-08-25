#include "Pacman.h"
#include "Camera.h"
#include <iostream>
//---------------------------------------------------------------------------
float speed = 0.2f;
float _timer = 0.f;
float speedCamera = 1;
float zoomCamera = 1;
float rotationCamera = 1;
//---------------------------------------------------------------------------
bool Pacman::init(Renderer& rendi){

	player.setPos(-550.0f, -188.0f);
	player.setScale(16.0f, 32.0f);

	cam = new Camera(rendi);

	cam->setRender(rendi);
	cam->update();

	Texture playerTexture = rendi.loadTexture("Assets/characters.png", COLOR_RGB(0, 255, 0));
	player.setTexture(playerTexture);

	walk.setLenght(450.f);
	walk.addFrame(512.0f, 512.0f, 24.0f, 112.0f, 18.0f, 32.0f);
	walk.addFrame(512.0f, 512.0f, 42.0f, 112.0f, 18.0f, 32.0f);
	walk.addFrame(512.0f, 512.0f, 61.0f, 112.0f, 18.0f, 32.0f);

	iddle.setLenght(400.0f);
	iddle.addFrame(512.0f, 512.0f, 6.0f, 112.0f, 18.0f, 32.0f);

	mapa.importMap(rendi, "Assets/marioMap.tmx");

	timerText.createText(0, 0, 1000, 100, 50, "Arial", "Timer: " + std::to_string((float)_timer), rendi);
	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){
	if (input.keyDown(input.KEY_LEFT)){
		player.flipX(true);
		player.setAnimation(&walk);
		player.setPos(player.posX() - (speed * timer.timeBetweenFrames()), player.posY());
	}
	else if (input.keyDown(input.KEY_RIGHT)){
		player.flipX(false);
		player.setAnimation(&walk);
		player.setPos(player.posX() + (speed * timer.timeBetweenFrames()), player.posY());
	}
	else if (input.keyDown(input.KEY_DOWN)){
		player.setPos(player.posX(), player.posY() - (speed * timer.timeBetweenFrames()));
	}
	else if (input.keyDown(input.KEY_UP)){
		player.setPos(player.posX(), player.posY() + (speed * timer.timeBetweenFrames()));
	}
	else if (input.keyDown(input.KEY_W)){
		cam->walk(zoomCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_S)){
		cam->walk(-zoomCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_Q)){
		cam->roll(rotationCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_E)){
		cam->roll(-rotationCamera* timer.timeBetweenFrames());
	}
	else
		player.setAnimation(&iddle);

	// Camera move
	 if (input.keyDown(input.KEY_D)){
		cam->strafe(speedCamera* timer.timeBetweenFrames());
	}
	 if (input.keyDown(input.KEY_A)){
		cam->strafe(-speedCamera* timer.timeBetweenFrames());
	}
	 if (input.keyDown(input.KEY_SPACE)){
		 cam->fly(speedCamera * timer.timeBetweenFrames());
	} 
	 if (input.keyDown(input.KEY_LCONTROL)){
		 cam->fly(-speedCamera * timer.timeBetweenFrames());
	}
	cam->yaw(input.mouseRelPosX() / 10);
	cam->pitch(input.mouseRelPosY() / 10);


	for (size_t j = 0; j < mapa._layers.size(); j++)
	{
		for (size_t i = 0; i < mapa._layers[j]->_collisionTiles.size(); i++){
			if (player.checkCollision(*mapa._layers[j]->_collisionTiles[i]) == Entity2D::CollisionHorizontal)
				player.returnToPoss(player.previousPosX(), player.posY());
		}

		for (size_t i = 0; i < mapa._layers[j]->_collisionTiles.size(); i++){
			if (player.checkCollision(*mapa._layers[j]->_collisionTiles[i]) == Entity2D::CollisionVertical)
				player.returnToPoss(player.posX(), player.previousPosY());
		}
	}

	_timer += timer.timeBetweenFrames() / 1000.f;
	std::string texto = "Timer: " + std::to_string((float)_timer);
	timerText.setText(texto);

	player.upDate(timer);	
	mapa.draw(renderer);
	player.draw(renderer);
	timerText.draw(renderer);
}
//---------------------------------------------------------------------------