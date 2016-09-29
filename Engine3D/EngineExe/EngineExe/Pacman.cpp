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
	cube2->setPos(0, -100, 0);
	cube2->setScale(100, 100, 100);

	cube3 = new Mesh(rendi);
	importador->ImportMesh("valla.obj", *cube3);
	cube3->setTextureId(rendi.loadTexture("Assets\\taurusTexture.jpg", 0));
	cube3->setPos(0, 0, 0);
	cube3->setScale(20, 20, 20);

	nodo1 = new Node();
	nodo2 = new Node();

	nodo1->AddChild(nodo2);
	nodo2->AddChild(cube1);
	nodo2->AddChild(cube2);
	nodo1->AddChild(cube3);
	
	
	return true;
}
//---------------------------------------------------------------------------
void Pacman::frame(Renderer& renderer, Input& input, Timer& timer){
	cameraControll(input, timer, cam);
	
	if (input.keyDown(input.KEY_O)){
		nodo1->setRotation(nodo1->rotationX() + 0.005f, nodo1->rotationY(), nodo1->rotationZ());
	}
	if (input.keyDown(input.KEY_P)){
		nodo1->setRotation(nodo1->rotationX() - 0.005f, nodo1->rotationY(), nodo1->rotationZ());
	}
	if (input.keyDown(input.KEY_K)){
		nodo2->setRotation(nodo2->rotationX() + 0.005f, nodo2->rotationY(), nodo2->rotationZ());
	}
	if (input.keyDown(input.KEY_L)){
		nodo2->setRotation(nodo2->rotationX() - 0.005f, nodo2->rotationY(), nodo2->rotationZ());
	}
	if (input.keyDown(input.KEY_N)){
		cube3->setRotation(cube3->rotationX() + 0.005f, cube3->rotationY(), cube3->rotationZ());
	}
	if (input.keyDown(input.KEY_M)){
		cube3->setRotation(cube3->rotationX() - 0.005f, cube3->rotationY(), cube3->rotationZ());
	}

	if (input.keyDown(input.KEY_I)){
		cube1->setPos(cube1->posX(), cube1->posY() + 1, cube1->posZ());
	}
	if (input.keyDown(input.KEY_U)){
		cube1->setPos(cube1->posX(), cube1->posY() - 1, cube1->posZ());
	}

	nodo1->updateWordTransformation();
	nodo1->draw();

	if (input.keyDown(input.KEY_Y)){
		std::cout << "Nodo1.y = " << nodo1->posY() << " | " << "Cube1.y = " << cube1->posY() << std::endl;
	}

	if (input.keyDown(input.KEY_U)){
		std::cout << "Nodo2.y = " << nodo2->posY() << " | " << "Cube2.y = " << cube2->posY() << std::endl;
	}

	

	cam->update();
	input.acquire();
}
//---------------------------------------------------------------------------
