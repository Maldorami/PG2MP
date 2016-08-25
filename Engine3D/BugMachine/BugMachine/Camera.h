#ifndef CAMERA_H
#define CAMERA_H
#define DLLexport __declspec(dllexport)
#include "Renderer.h"
class Camera{
public:
	DLLexport Camera();
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
	float posX;
	float posY;
	float posZ;
	float LAposX;
	float LAposY;
	float LAposZ;
	float UPposX;
	float UPposY;
	float UPposZ;
	Vector3 _eye;
	Vector3 _at;
	Vector3 _up;
	Vector3 _right;
	Matrix _view;

};
#endif