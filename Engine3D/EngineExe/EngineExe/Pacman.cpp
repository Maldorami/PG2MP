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
float taurusRot = 0;
//---------------------------------------------------------------------------
bool Pacman::init(Renderer& rendi){
	// camera config
	cam = new Camera(rendi);
	cam->setRender(rendi);
	cam->update();

	piramide = new Mesh(rendi);
	importador->ImportMesh("valla.obj", *piramide);
	piramide->setPos(0, 500, -100);
	piramide->setScale(100, 100, 100);
	
	imp = new Mesh(rendi);
	importador->ImportMesh("taurus.obj", *imp);
	imp->setPos(0, 0, -100);
	imp->setScale(100, 100, 100);

	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){
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

	taurusRot += 0.001;
	imp->setRotation(taurusRot, 0, taurusRot);

	cam->update();
	piramide->draw();
	imp->draw();

	input.acquire();
}
//---------------------------------------------------------------------------