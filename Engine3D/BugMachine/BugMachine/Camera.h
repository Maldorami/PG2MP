#ifndef CAMERA_H
#define CAMERA_H

#define DLLexport __declspec(dllexport)

#include "Renderer.h"

class Camera{
public:
	DLLexport Camera(Renderer& render);
	DLLexport ~Camera();
	//Rotation
	DLLexport void roll(float angle);
	DLLexport void pitch(float angle);
	DLLexport void yaw(float angle);

	//Movement
	DLLexport void walk(float distance);
	DLLexport void strafe(float distance);
	DLLexport void fly(float distance);

	DLLexport void update();

	DLLexport void setRender(Renderer& rendi);
	Renderer* render;

	//Camera Settings
	float posX;
	float posY;
	float posZ;
	float LAposX;
	float LAposY;
	float LAposZ;
	float UPposX;
	float UPposY;
	float UPposZ;

	D3DXVECTOR3 _up;
	D3DXVECTOR3 _lookAt;
	D3DXVECTOR3 _forward;
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _pos;

	Matrix	_localView;

};
#endif