#include "Pacman.h"
#include "Camera.h"
#include <iostream>
#include <time.h>
//---------------------------------------------------------------------------
float speedCamera = 1;
float zoomCamera = 1;
float rotationCamera = 1;
float rot = 1;
//------------------------
void cameraControll(Input& input, Timer& timer, Camera* cam) {
	// Camera move
	if (input.keyDown(input.KEY_W)){
		cam->walk(zoomCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_S)){
		cam->walk(-zoomCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_Q)){
		cam->roll(rotationCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_E)){
		cam->roll(-rotationCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_D)){
		cam->strafe(speedCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_A)){
		cam->strafe(-speedCamera* timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_SPACE)){
		cam->fly(speedCamera * timer.timeBetweenFrames());
	}
	if (input.keyDown(input.KEY_LSHIFT)){
		cam->fly(-speedCamera * timer.timeBetweenFrames());
	}
	cam->yaw((float)input.mouseRelPosX() / 10);
	cam->pitch((float)input.mouseRelPosY() / 10);
}
//------------------------
float cubeRot = 0;
//---------------------------------------------------------------------------
bool Pacman::init(Renderer& rendi){

	// camera config
	cam = new Camera(rendi);
	cam->setRender(rendi);
	cam->update();
	///////////////////////////////

	cube1 = new Mesh(rendi);
	importador->ImportMesh("teapot.obj", *cube1);
	cube1->setTextureId(rendi.loadTexture("Assets\\teapotTexture.jpg", 0));
	cube1->setPos(0, 200, -100);
	cube1->setScale(5, 5, 5);

	cube2 = new Mesh(rendi);
	importador->ImportMesh("taurus.obj", *cube2);
	cube2->setTextureId(rendi.loadTexture("Assets\\taurusTexture.jpg", 0));
	cube2->setPos(0, 0, -100);
	cube2->setScale(100, 100, 100);


	nodo1 = new Node();
	nodo2 = new Node();

	nodo1->AddChild(cube1);
	nodo1->AddChild(nodo2);
	nodo2->AddChild(cube2);
	
	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){
	cameraControll(input, timer, cam);
	
	if (input.keyDown(input.KEY_1)){
		nodo1->setPos(nodo1->posX(), nodo1->posY() + 10, nodo1->posZ());
	}
	if (input.keyDown(input.KEY_2)){
		nodo1->setPos(nodo1->posX(), nodo1->posY() - 10, nodo1->posZ());
	}

	nodo1->draw();

	cam->update();
	input.acquire();
}
//---------------------------------------------------------------------------
