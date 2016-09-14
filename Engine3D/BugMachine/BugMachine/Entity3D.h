#ifndef ENTITY3D_H
#define ENTITY3D_H

#include "Mat.h"
#include "Renderer.h"
#include "pg1_timer.h"

#define DLLexport __declspec(dllexport)

class Entity3D{
public:
	DLLexport Entity3D();
	DLLexport virtual ~Entity3D();
	DLLexport void setPos(float fPosX, float fPosY, float fPosZ);
	DLLexport void setRotation(float fRotation);
	DLLexport void setRotation(float fRotationX, float fRotationY, float fRotationZ);
	DLLexport void setScale(float scaleX, float scaleY, float scaleZ);

	DLLexport float posX();
	DLLexport float posY();
	DLLexport float posZ();
	DLLexport float rotationZ();
	DLLexport float rotationY();
	DLLexport float rotationX();
	DLLexport float scaleX();
	DLLexport float scaleY();
	DLLexport float scaleZ();

private:
	float _posX, _posY, _posZ;
	float _rotationX, _rotationY, _rotationZ;
	float _scaleX, _scaleY, _scaleZ;
	bool _flipX;

	void updateLocalTransformation();

protected:
	Matrix _transformationMatrix;
};
#endif