#include "Pacman.h"
#include "Camera.h"
#include <iostream>
#include <time.h>
//---------------------------------------------------------------------------
float speedCamera = 10;
float zoomCamera = 10;
float rotationCamera = 10;
//---------------------------------------------------------------------------
bool Pacman::init(Renderer& rendi){
	// camera config
	cam = new Camera(rendi);
	cam->setRender(rendi);
	cam->update();

	// cube parameters
	#define CUBESIZE 5.0f;
	CustomVertex vertices[8];	
	vertices[0].x = -CUBESIZE;	vertices[0].y =  CUBESIZE;	vertices[0].z = -CUBESIZE;	vertices[0].color = D3DCOLOR_XRGB(0  ,	0  ,	255);    // vertex 0
	vertices[1].x =  CUBESIZE;	vertices[1].y =  CUBESIZE;	vertices[1].z = -CUBESIZE;	vertices[1].color = D3DCOLOR_XRGB(0  ,	255,	0  );    // vertex 1
	vertices[2].x = -CUBESIZE;	vertices[2].y = -CUBESIZE;	vertices[2].z = -CUBESIZE;	vertices[2].color = D3DCOLOR_XRGB(255,	0  ,	0  );	 // 2
	vertices[3].x =  CUBESIZE;	vertices[3].y = -CUBESIZE;	vertices[3].z = -CUBESIZE;	vertices[3].color = D3DCOLOR_XRGB(0  ,	255,	255);  // 3
	vertices[4].x = -CUBESIZE;	vertices[4].y =  CUBESIZE;	vertices[4].z =  CUBESIZE;	vertices[4].color = D3DCOLOR_XRGB(0  ,	0  ,	255);    // ...
	vertices[5].x =  CUBESIZE;	vertices[5].y =  CUBESIZE;	vertices[5].z =  CUBESIZE;	vertices[5].color = D3DCOLOR_XRGB(255,	0  ,	0  );
	vertices[6].x = -CUBESIZE;	vertices[6].y = -CUBESIZE;	vertices[6].z =  CUBESIZE;	vertices[6].color = D3DCOLOR_XRGB(0  ,	255,	0  );
	vertices[7].x =  CUBESIZE;	vertices[7].y = -CUBESIZE;	vertices[7].z =  CUBESIZE;	vertices[7].color = D3DCOLOR_XRGB(0  ,	255,	255);

	unsigned short indices[] =
	{
		0, 1, 2,    // side 1
		2, 1, 3,
		4, 0, 6,    // side 2
		6, 0, 2,
		7, 5, 6,    // side 3
		6, 5, 4,
		3, 1, 7,    // side 4
		7, 1, 5,
		4, 5, 0,    // side 5
		0, 5, 1,
		3, 7, 2,    // side 6
		2, 7, 6,
	};

	cube = new Mesh(rendi);
	int verticesSize = ARRAYSIZE(vertices);
	int indicesSize = ARRAYSIZE(indices);
	cube->setMeshData(vertices, Primitive::TriangleList, verticesSize, indices, indicesSize);
	cube->setPos(0, 0, 0);
	cube->setScale(300, 300, 300);

	// create the vertices using the CUSTOMVERTEX
	struct CustomVertex piramideVertices[] =
	{
		// base
		{ -3.0f, 0.0f, 3.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 3.0f, 0.0f, 3.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ -3.0f, 0.0f, -3.0f, D3DCOLOR_XRGB(255, 0, 0), },
		{ 3.0f, 0.0f, -3.0f, D3DCOLOR_XRGB(0, 255, 255), },

		// top
		{ 0.0f, 7.0f, 0.0f, D3DCOLOR_XRGB(0, 255, 0), },
	};
	// create the indices using an int array
	unsigned short piramideIndices[] =
	{
		0, 2, 1,    // base
		1, 2, 3,
		0, 1, 4,    // sides
		1, 3, 4,
		3, 2, 4,
		2, 0, 4,
	};
	piramide = new Mesh(rendi);
	piramide->setMeshData(piramideVertices, Primitive::TriangleStrip, ARRAYSIZE(piramideVertices), piramideIndices, ARRAYSIZE(piramideIndices));
	piramide->setPos(0, 0, 0);
	piramide->setScale(300, 300, 300);


	quad = new Mesh(rendi);
	struct CustomVertex quadVertices[4];
		vertices[0].x = -CUBESIZE;	vertices[0].y = CUBESIZE;	vertices[0].z = 0;	vertices[0].color = D3DCOLOR_XRGB(0, 0, 255);    // vertex 0
		vertices[1].x = CUBESIZE;	vertices[1].y = CUBESIZE;	vertices[1].z = 0;	vertices[1].color = D3DCOLOR_XRGB(0, 255, 0);    // vertex 1
		vertices[2].x = -CUBESIZE;	vertices[2].y = -CUBESIZE;	vertices[2].z = 0;	vertices[2].color = D3DCOLOR_XRGB(255, 0, 0);	 // 2
		vertices[3].x = CUBESIZE;	vertices[3].y = -CUBESIZE;	vertices[3].z = 0;	vertices[3].color = D3DCOLOR_XRGB(0, 255, 255);  // 3
	// create the indices using an int array
	unsigned short quadIndices[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	quad->setMeshData(quadVertices, Primitive::TriangleStrip, ARRAYSIZE(quadVertices), quadIndices, ARRAYSIZE(quadIndices));
	quad->setPos(0, 0);
	quad->setScale(150, 150);


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
	 if (input.keyDown(input.KEY_LCONTROL)){
		 cam->fly(-speedCamera * timer.timeBetweenFrames());
	}
	cam->yaw((float)input.mouseRelPosX() / 10);
	cam->pitch((float)input.mouseRelPosY() / 10);

	cam->update();
	cube->draw();
	//piramide->draw();
	//quad->draw();
}
//---------------------------------------------------------------------------