#include "Entity3D.h"
#include "Renderer.h"
#include <d3dx9.h>
#include <algorithm>
//---------------------------------------------------------------------------
Entity3D::Entity3D()
:
_posX(0.0f),
_posY(0.0f),
_posZ(0.0f),
_rotationX(0.0f),
_rotationY(0.0f),
_rotationZ(0.0f),
_scaleX(1.0f),
_scaleY(1.0f),
_scaleZ(1.0f),
_flipX(false),
_transformationMatrix(new D3DXMATRIX())
{
	updateLocalTransformation();
}
//---------------------------------------------------------------------------
Entity3D::~Entity3D(){
	delete _transformationMatrix;
	_transformationMatrix = NULL;
}
//---------------------------------------------------------------------------
void Entity3D::setPos(float posX, float posY, float posZ){
	_posX = posX;
	_posY = posY;
	_posZ = posZ;
	updateLocalTransformation();
}

//---------------------------------------------------------------------------
void Entity3D::setRotation(float rotationZ){
	_rotationZ = rotationZ;

	updateLocalTransformation();
}
//---------------------------------------------------------------------------
void Entity3D::setRotation(float fRotationX, float fRotationY, float fRotationZ){
	_rotationX = fRotationX;
	_rotationY = fRotationY;
	_rotationZ = fRotationZ;

	updateLocalTransformation();
}
//---------------------------------------------------------------------------
void Entity3D::setScale(float scaleX, float scaleY, float scaleZ){
	_scaleX = scaleX;
	_scaleY = scaleY;
	_scaleZ = scaleZ;

	updateLocalTransformation();
}
//---------------------------------------------------------------------------
float Entity3D::posX(){
	return _posX;
}
//---------------------------------------------------------------------------
float Entity3D::posY(){
	return _posY;
}
//---------------------------------------------------------------------------
float Entity3D::posZ(){
	return _posZ;
}
//---------------------------------------------------------------------------
float Entity3D::scaleX(){
	return _scaleX;
}
//---------------------------------------------------------------------------
float Entity3D::scaleY(){
	return _scaleY;
}
//---------------------------------------------------------------------------
float Entity3D::scaleZ(){
	return _scaleZ;
}
//---------------------------------------------------------------------------
float Entity3D::rotationX(){
	return _rotationX;
}
//---------------------------------------------------------------------------
float Entity3D::rotationY(){
	return _rotationY;
}
//---------------------------------------------------------------------------
float Entity3D::rotationZ(){
	return _rotationZ;
}
//---------------------------------------------------------------------------
void Entity3D::updateLocalTransformation(){

	D3DXMATRIX traslatrionMat;
	D3DXMatrixTranslation(&traslatrionMat, _posX, _posY, _posZ);

	D3DXMATRIX rotationMatX;
	D3DXMatrixRotationX(&rotationMatX, _rotationX);

	D3DXMATRIX rotationMatY;
	D3DXMatrixRotationY(&rotationMatY, _rotationY);

	D3DXMATRIX rotationMatZ;
	D3DXMatrixRotationZ(&rotationMatZ, _rotationZ);

	D3DXMATRIX scaleMat;
	D3DXMatrixScaling(&scaleMat, _scaleX, _scaleY, _scaleZ);

	D3DXMatrixIdentity(_transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &traslatrionMat, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationMatX, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationMatY, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &rotationMatZ, _transformationMatrix);
	D3DXMatrixMultiply(_transformationMatrix, &scaleMat, _transformationMatrix);
}
//---------------------------------------------------------------------------