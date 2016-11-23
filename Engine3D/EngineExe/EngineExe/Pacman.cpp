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
	nodo1->setName("Root");
	importador = new Importador(rendi);
	importador->importScene("sceneFinal.dae", *nodo1);
	nodo1->setScale(100, 100, 100);
	nodo1->setPos(0, 0, 0);

	cube = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube);
	cube->setScale(10, 10, 10);

	cube2 = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube2);
	cube2->setScale(10, 10, 10);

	cube3 = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube3);
	cube3->setScale(10, 10, 10);


	cube4 = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube4);
	cube4->setScale(10, 10, 10);

	cube5 = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube5);
	cube5->setScale(10, 10, 10);

	cube6 = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube6);
	cube6->setScale(10, 10, 10);

	cube7 = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube7);
	cube7->setScale(10, 10, 10);

	cube8 = new Node();
	importador = new Importador(rendi);
	importador->importScene("cube.obj", *cube8);
	cube8->setScale(10, 10, 10);


	frustum = new Frustum(rendi);
	cam->setFrustum(frustum);


	_text.createText(0, 0, 1000, 1000, 20, "Arial","asdasdasd", rendi);
	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){

	float RotModif = 0.1f * timer.timeBetweenFrames();
	float ScaleModif = 1.001f /** timer.timeBetweenFrames()*/;
	float PosModif = 1 * timer.timeBetweenFrames();

	_text.setText("");

	// Modificar rotacion nodo1: O y P
	if (input.keyDown(input.KEY_O))	nodo1->setPos(nodo1->posX() - RotModif, nodo1->posY(), nodo1->posZ());
	if (input.keyDown(input.KEY_P)) nodo1->setPos(nodo1->posX() + RotModif, nodo1->posY(), nodo1->posZ());

	// Modificar rotacion nodo2: K y L
	if (input.keyDown(input.KEY_K)) nodo1->_childs[0]->setRotation(nodo1->_childs[0]->rotationX(), nodo1->_childs[0]->rotationY() + RotModif, nodo1->_childs[0]->rotationZ());
	if (input.keyDown(input.KEY_L)) nodo1->_childs[0]->setRotation(nodo1->_childs[0]->rotationX(), nodo1->_childs[0]->rotationY() - RotModif, nodo1->_childs[0]->rotationZ());

	// Modificar rotacion valla: N y M
	if (input.keyDown(input.KEY_N)) nodo1->_childs[1]->setRotation(nodo1->_childs[1]->rotationX(), nodo1->_childs[1]->rotationY() + RotModif, nodo1->_childs[1]->rotationZ());
	if (input.keyDown(input.KEY_M)) nodo1->_childs[1]->setRotation(nodo1->_childs[1]->rotationX(), nodo1->_childs[1]->rotationY() - RotModif, nodo1->_childs[1]->rotationZ());

	cam->update();
	cam->updateFrustum();
	nodo1->draw(renderer, cam->frustum->CheckCollision(nodo1->BV), *frustum , _text);
	nodo1->updateBV();

	cube8->setPos(nodo1/*->_childs[0]*/->BV.ActualxMax, nodo1/*->_childs[0]*/->BV.ActualyMin, nodo1/*->_childs[0]*/->BV.ActualzMin);
	 cube->setPos(nodo1/*->_childs[0]*/->BV.ActualxMax, nodo1/*->_childs[0]*/->BV.ActualyMax, nodo1/*->_childs[0]*/->BV.ActualzMax);
	cube2->setPos(nodo1/*->_childs[0]*/->BV.ActualxMin, nodo1/*->_childs[0]*/->BV.ActualyMin, nodo1/*->_childs[0]*/->BV.ActualzMax);
	cube3->setPos(nodo1/*->_childs[0]*/->BV.ActualxMin, nodo1/*->_childs[0]*/->BV.ActualyMax, nodo1/*->_childs[0]*/->BV.ActualzMax);
	cube4->setPos(nodo1/*->_childs[0]*/->BV.ActualxMax, nodo1/*->_childs[0]*/->BV.ActualyMin, nodo1/*->_childs[0]*/->BV.ActualzMax);
	cube5->setPos(nodo1/*->_childs[0]*/->BV.ActualxMax, nodo1/*->_childs[0]*/->BV.ActualyMax, nodo1/*->_childs[0]*/->BV.ActualzMin);
	cube6->setPos(nodo1/*->_childs[0]*/->BV.ActualxMin, nodo1/*->_childs[0]*/->BV.ActualyMin, nodo1/*->_childs[0]*/->BV.ActualzMin);
	cube7->setPos(nodo1/*->_childs[0]*/->BV.ActualxMin, nodo1/*->_childs[0]*/->BV.ActualyMax, nodo1/*->_childs[0]*/->BV.ActualzMin);

	 cube->draw(renderer,  CollisionResult::AllInside, *frustum);
	 cube2->draw(renderer, CollisionResult::AllInside, *frustum);
	 cube3->draw(renderer, CollisionResult::AllInside, *frustum);
	 cube4->draw(renderer, CollisionResult::AllInside, *frustum);
	 cube5->draw(renderer, CollisionResult::AllInside, *frustum);
	 cube6->draw(renderer, CollisionResult::AllInside, *frustum);
	 cube7->draw(renderer, CollisionResult::AllInside, *frustum);
	 cube8->draw(renderer, CollisionResult::AllInside, *frustum);

	 _text.draw(renderer);
	cameraControll(input, timer, cam);
	input.acquire();
}
//---------------------------------------------------------------------------
