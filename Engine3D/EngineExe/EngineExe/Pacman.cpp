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

	scene1 = importador->ImportScene("asdasd.obj", rendi);
	

	teapot = new Mesh(rendi);
	importador->ImportMesh("teapot.obj", *teapot);
	teapot->setTextureId(rendi.loadTexture("Assets\\teapotTexture.jpg", 0));
	teapot->setPos(300, -200, 200);
	teapot->setScale(5, 5, 5);

	taurus = new Mesh(rendi);
	importador->ImportMesh("taurus.obj", *taurus);
	taurus->setTextureId(rendi.loadTexture("Assets\\taurusTexture.jpg", 0));
	taurus->setPos(0, -200, 0);
	taurus->setScale(100, 100, 100);

	valla = new Mesh(rendi);
	importador->ImportMesh("valla.obj", *valla);
	valla->setTextureId(rendi.loadTexture("Assets\\vallaTexture.jpg", 0));
	valla->setPos(-300, -200, 200);
	valla->setScale(100, 100, 100);


	nodo1 = new Node();
	nodo2 = new Node();

	nodo1->AddChild(valla);
	nodo1->AddChild(nodo2);
	nodo2->AddChild(teapot);
	nodo2->AddChild(taurus);
	
	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){
	cameraControll(input, timer, cam);

	float RotModif = 0.005f * timer.timeBetweenFrames();
	float ScaleModif = 1.001f /** timer.timeBetweenFrames()*/;
	float PosModif = 1 * timer.timeBetweenFrames();

	// Modificar rotacion nodo1: O y P
	if (input.keyDown(input.KEY_O))
		nodo1->setRotation(nodo1->rotationX(), nodo1->rotationY() + RotModif, nodo1->rotationZ());
	if (input.keyDown(input.KEY_P))	nodo1->setRotation(nodo1->rotationX(), nodo1->rotationY() - RotModif, nodo1->rotationZ());

	// Modificar rotacion nodo2: K y L
	if (input.keyDown(input.KEY_K)) nodo2->setRotation(nodo2->rotationX(), nodo2->rotationY() + RotModif, nodo2->rotationZ());
	if (input.keyDown(input.KEY_L))	nodo2->setRotation(nodo2->rotationX(), nodo2->rotationY() - RotModif, nodo2->rotationZ());

	// Modificar rotacion valla: N y M
	if (input.keyDown(input.KEY_N))	valla->setRotation(valla->rotationX(), valla->rotationY() + RotModif, valla->rotationZ());
	if (input.keyDown(input.KEY_M))	valla->setRotation(valla->rotationX(), valla->rotationY() - RotModif, valla->rotationZ());

	// Modificar escala nodo1: 1 y 2
	if (input.keyDown(input.KEY_1))	nodo1->setScale(nodo1->scaleX() / ScaleModif, nodo1->scaleY() / ScaleModif, nodo1->scaleZ() / ScaleModif);
	if (input.keyDown(input.KEY_2))	nodo1->setScale(nodo1->scaleX() * ScaleModif, nodo1->scaleY() * ScaleModif, nodo1->scaleZ() * ScaleModif);

	// Modificar escala valla: 3 y 4
	if (input.keyDown(input.KEY_3))	valla->setScale(valla->scaleX() / ScaleModif, valla->scaleY() / ScaleModif, valla->scaleZ() / ScaleModif);
	if (input.keyDown(input.KEY_4))	valla->setScale(valla->scaleX() * ScaleModif, valla->scaleY() * ScaleModif, valla->scaleZ() * ScaleModif);

	// Modificar posicion teapot: I y U
	if (input.keyDown(input.KEY_I))	teapot->setPos(teapot->posX(), teapot->posY() + PosModif, teapot->posZ());
	if (input.keyDown(input.KEY_U))	teapot->setPos(teapot->posX(), teapot->posY() - PosModif, teapot->posZ());

	// Modificar posicion nodo2: H y J
	if (input.keyDown(input.KEY_H))	nodo2->setPos(nodo2->posX(), nodo2->posY() + PosModif, nodo2->posZ());
	if (input.keyDown(input.KEY_J))	nodo2->setPos(nodo2->posX(), nodo2->posY() - PosModif, nodo2->posZ());

	// Modificar posicion valla: V y B
	if (input.keyDown(input.KEY_V))	valla->setPos(valla->posX(), valla->posY() + PosModif, valla->posZ());
	if (input.keyDown(input.KEY_B))	valla->setPos(valla->posX(), valla->posY() - PosModif, valla->posZ());

	/*if (input.keyDown(input.KEY_Y)) std::cout << "Nodo1.y = " << nodo1->posY() << " | " << "Cube1.y = " << teapot->posY() << std::endl;
	if (input.keyDown(input.KEY_U))	std::cout << "Nodo2.y = " << nodo2->posY() << " | " << "Cube2.y = " << taurus->posY() << std::endl;*/

	for (int i = 0; i < scene1.size(); i++)
	{
		scene1[i]->updateWordTransformation();
		scene1[i]->draw();
		scene1[i]->setTextureId(renderer.loadTexture("Assets\\teapotTexture.jpg", 0));
	}

	//nodo1->updateWordTransformation();
	//nodo1->draw();
	cam->update();
	input.acquire();
}
//---------------------------------------------------------------------------
