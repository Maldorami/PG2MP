#include "Pacman.h"
#include "Camera.h"
#include <iostream>
#include <time.h>
//---------------------------------------------------------------------------
float speedCamera = 1;
float zoomCamera = 1;
float rotationCamera = 1;
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
	cam->yaw((float)input.mouseRelPosX() * 0.05f);
	cam->pitch((float)input.mouseRelPosY() * 0.05f);
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

	nodo1 = new Node();
	importador = new Importador(rendi);
	importador->importScene("scene.dae", *nodo1);
	nodo1->setScale(100, 100, 100);
	
	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){

	float RotModif = 0.005f * timer.timeBetweenFrames();
	float ScaleModif = 1.001f /** timer.timeBetweenFrames()*/;
	float PosModif = 1 * timer.timeBetweenFrames();

	// Modificar rotacion nodo1: O y P
	if (input.keyDown(input.KEY_O))	nodo1->setRotation(nodo1->rotationX(), nodo1->rotationY() + RotModif, nodo1->rotationZ());
	if (input.keyDown(input.KEY_P)) nodo1->setRotation(nodo1->rotationX(), nodo1->rotationY() - RotModif, nodo1->rotationZ());

	// Modificar rotacion nodo2: K y L
	if (input.keyDown(input.KEY_K)) nodo1->_childs[0]->setRotation(nodo1->_childs[0]->rotationX(), nodo1->_childs[0]->rotationY() + RotModif, nodo1->_childs[0]->rotationZ());
	if (input.keyDown(input.KEY_L)) nodo1->_childs[0]->setRotation(nodo1->_childs[0]->rotationX(), nodo1->_childs[0]->rotationY() - RotModif, nodo1->_childs[0]->rotationZ());

	// Modificar rotacion valla: N y M
	if (input.keyDown(input.KEY_N)) nodo1->_childs[1]->setRotation(nodo1->_childs[1]->rotationX(), nodo1->_childs[1]->rotationY() + RotModif, nodo1->_childs[1]->rotationZ());
	if (input.keyDown(input.KEY_M)) nodo1->_childs[1]->setRotation(nodo1->_childs[1]->rotationX(), nodo1->_childs[1]->rotationY() - RotModif, nodo1->_childs[1]->rotationZ());

	nodo1->updateWordTransformation();
	nodo1->draw();
	cam->update();
	cameraControll(input, timer, cam);
	input.acquire();
}
//---------------------------------------------------------------------------
