#include "Pacman.h"
#include "Camera.h"
#include <iostream>
//---------------------------------------------------------------------------
float speed = 0.2f;
float _timer = 0.f;
float speedCamera = 0.1f;
float zoomCamera = 0.0001f;
float rotationCamera = 0.01f;
//---------------------------------------------------------------------------
bool Pacman::init(Renderer& rendi){

	player.setPos(-550.0f, -188.0f);
	player.setScale(16.0f, 32.0f);

	camera.setRender(rendi);
	camera.update();

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
		camera.strafe(-speedCamera* timer.timeBetweenFrames());
		player.flipX(true);
		player.setAnimation(&walk);
		player.setPos(player.posX() - (speed * timer.timeBetweenFrames()), player.posY());
	}
	else if (input.keyDown(input.KEY_RIGHT)){
		camera.strafe(speedCamera* timer.timeBetweenFrames());
		player.flipX(false);
		player.setAnimation(&walk);
		player.setPos(player.posX() + (speed * timer.timeBetweenFrames()), player.posY());
	}
	else if (input.keyDown(input.KEY_DOWN)){
		camera.fly(-speedCamera* timer.timeBetweenFrames());
		player.setPos(player.posX(), player.posY() - (speed * timer.timeBetweenFrames()));
	}
	else if (input.keyDown(input.KEY_UP)){
		camera.fly(speedCamera* timer.timeBetweenFrames());
		player.setPos(player.posX(), player.posY() + (speed * timer.timeBetweenFrames()));
	}
	else if (input.keyDown(input.KEY_W)){
		camera.walk(zoomCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_S)){
		camera.walk(-zoomCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_Q)){
		camera.yaw(rotationCamera * timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_E)){
		camera.yaw(-rotationCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_R)){
		camera.pitch(rotationCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_F)){
		camera.pitch(-rotationCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_A)){
		camera.roll(speedCamera* timer.timeBetweenFrames());
	}
	else if (input.keyDown(input.KEY_D)){
		camera.roll(-speedCamera* timer.timeBetweenFrames());
	}
	else
		player.setAnimation(&iddle);


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