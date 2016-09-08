#include "Entity2D.h"
#include "Renderer.h"
#include <d3dx9.h>
#include <algorithm>
//---------------------------------------------------------------------------
Entity2D::Entity2D()
	:
	_posX(0.0f),
	_posY(0.0f),
	_posZ(0.0f),
	_rotation(0.0f),
	_scaleX(1.0f),
	_scaleY(1.0f),
	_scaleZ(1.0f),
	_flipX(false),
	_transformationMatrix(new D3DXMATRIX())
{
	updateLocalTransformation();
}
//---------------------------------------------------------------------------
Entity2D::~Entity2D(){
	delete _transformationMatrix;
	_transformationMatrix = NULL;
}
//---------------------------------------------------------------------------
void Entity2D::setPos(float posX, float posY, float posZ){
	_posX = posX;
	_posY = posY;
	_posZ = posZ;
	updateLocalTransformation();
}

//---------------------------------------------------------------------------
void Entity2D::setRotation(float rotation){
	_rotation = rotation;

	updateLocalTransformation();
}
//---------------------------------------------------------------------------
void Entity2D::setScale(float scaleX, float scaleY, float scaleZ){
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;

	updateLocalTransformation();
}
//---------------------------------------------------------------------------
float Entity2D::posX(){
	return _posX;
}
//---------------------------------------------------------------------------
float Entity2D::posY(){
	return _posY;
}
//---------------------------------------------------------------------------
float Entity2D::posZ(){
	return _posZ;
}
//---------------------------------------------------------------------------
float Entity2D::scaleX(){
	return _scaleX;
}
//---------------------------------------------------------------------------
float Entity2D::scaleY(){
	return _scaleY;
}
//---------------------------------------------------------------------------
float Entity2D::scaleZ(){
	return _scaleZ;
}
//---------------------------------------------------------------------------
float Entity2D::rotation(){
	return _rotation;
}
//---------------------------------------------------------------------------
void Entity2D::updateLocalTransformation(){

	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, _posX, _posY, _posZ);

	D3DXMATRIX rotationMat;
	D3DXMatrixRotationX(&rotationMat, _rotation);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, _scaleX, _scaleY, _scaleZ);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &traslatrionMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &scaleMat, _transformationMatrix);
}
//---------------------------------------------------------------------------