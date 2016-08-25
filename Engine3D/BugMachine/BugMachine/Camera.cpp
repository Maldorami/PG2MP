#include "Camera.h"
#include "Renderer.h"

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

//#include <d3dx9math.h>
//#pragma comment (lib, "d3dx9math.lib")

Camera::Camera(Renderer& renderer)
	:
	render(NULL),
	posX(0),
	posY(0),
	posZ(-1),
	LAposX(0),
	LAposY(0),
	LAposZ(1.0f),
	UPposX(0),
	UPposY(1.0),
	UPposZ(0),
	_up(0.0f, 1.0f, 0.0f),
	_forward(0.0f, 0.0f, 1.0f),
	_right(1.0f, 0.0f, 0.0f),
	_lookAt(0.0f, 0.0f, 1.0f),
	_pos(0.0f, 0.0f, -1.0f),
	_localView(new D3DXMATRIX())
{
	setRender(renderer);
	update();
}
Camera::~Camera(){

}
void Camera::update(){
	_lookAt = _pos + _forward;

	// Calculate the new view matrix
	D3DXMatrixLookAtLH(_localView, &_pos, &_lookAt, &_up);

	// Set Transform
	render->d3ddev->SetTransform(D3DTS_VIEW, _localView);
}
void Camera::roll(float angle){

	if (angle == 0.0f)
	{
		return;
	}
	
	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &_forward, D3DXToRadian(angle));
	D3DXVec3TransformNormal(&_right, &_right, &rotation);
	D3DXVec3TransformNormal(&_up, &_up, &rotation);

	update();
}
void Camera::pitch(float angle){

	if (angle == 0.0f)
	{
		return;
	}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &_right, D3DXToRadian(angle));
	D3DXVec3TransformNormal(&_up, &_up, &rotation);
	D3DXVec3TransformNormal(&_forward, &_forward, &rotation);

	update();
}
void Camera::yaw(float angle){

	if (angle == 0.0f)
	{
		return;
	}

	D3DXMATRIX rotation;
	D3DXMatrixRotationAxis(&rotation, &_up, D3DXToRadian(angle));
	D3DXVec3TransformNormal(&_right, &_right, &rotation);
	D3DXVec3TransformNormal(&_forward, &_forward, &rotation);

	update();
}
void Camera::walk(float distance){
	_pos += _forward * distance;

	update();
}

void Camera::strafe(float distance){
	_pos += _right * distance;

	update();
}

void Camera::fly(float distance){
	_pos += _up * distance;

	update();
} 
void Camera::setRender(Renderer& rendi){
	render = &rendi;
}