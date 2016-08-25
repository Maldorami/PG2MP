#include "Camera.h"
#include "Renderer.h"
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Camera::Camera()
	:
	render(NULL),
	posX(0),
	posY(0),
	posZ(-0.1f),
	LAposX(0),
	LAposY(0),
	LAposZ(1.0f),
	UPposX(0),
	UPposY(1.0f),
	UPposZ(0),
	_eye(new D3DXVECTOR3),
	_up(new D3DXVECTOR3),
	_at(new D3DXVECTOR3),
	_right(new D3DXVECTOR3(1.0,0.0f,0.0f)),
	_view(new D3DXMATRIX)
	{}
Camera::~Camera(){

}
void Camera::update(){
	_eye->x = posX;
	_eye->y = posY;
	_eye->z = posZ;
	_at->x = LAposX;
	_at->y = LAposY;
	_at->z = LAposZ;
	_up->x = UPposX;
	_up->y = UPposY;
	_up->z = UPposZ;
	D3DXMatrixLookAtLH(_view, _eye, _at, _up);
	render->d3ddev->SetTransform(D3DTS_VIEW, _view);
}
void Camera::roll(float angle){

}
void Camera::pitch(float angle){
	
}
void Camera::yaw(float angle){
	D3DXMATRIX rotationMatrix;
	D3DXMatrixRotationY(&rotationMatrix, D3DXToRadian(angle));
	D3DXVECTOR4 result;
	D3DXVec3Transform(&result, _at, &rotationMatrix);
	_at->x = result.x;
	_at->y = result.y;
	_at->z = result.z;

	D3DXVECTOR3 target;
	target.x = posX + _at->x;
	target.y = posY + _at->y;
	target.z = posZ + _at->z;

	D3DXMatrixLookAtLH(_view, _eye, &target, _up);
	render->d3ddev->SetTransform(D3DTS_VIEW, _view);
}
void Camera::walk(float distance){
	posZ += distance;
	LAposZ += distance;
	update();
}

void Camera::strafe(float distance){
	posX += distance;
	LAposX += distance;
	update();
}

void Camera::fly(float distance){
	posY += distance;
	LAposY += distance;
	update();
} 
void Camera::setRender(Renderer& rendi){
	render = &rendi;
}