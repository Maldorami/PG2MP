#include "Frustum.h"
//---------------------------------------------------------------------------
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <iostream>

Frustum::Frustum(Renderer& rkRenderer)
:
m_planes(NULL),
rendi(rkRenderer)
{
	const int planes = 6;
	m_planes = new Plane[planes];
	for (int i = 0; i < planes; i++)
	{
		m_planes[i] = new D3DXPLANE();
	}
	matrix = new D3DXMATRIX();
}

Frustum::~Frustum(){}

void Frustum::ConstructFrustum(float screenDepth, Matrix& projectionMatrix, Matrix& viewMatrix){
	float zMinimum;
	float r;

	// Calculate the minimum Z distance in the frustum.
	zMinimum = -projectionMatrix->_43 / projectionMatrix->_33;
	r = screenDepth / (screenDepth - zMinimum);
	projectionMatrix->_33 = r;
	projectionMatrix->_43 = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix.
	D3DXMatrixMultiply(matrix, viewMatrix, projectionMatrix);

	// Calculate near plane of frustum.
	m_planes[0]->a = matrix->_14 + matrix->_13;
	m_planes[0]->b = matrix->_24 + matrix->_23;
	m_planes[0]->c = matrix->_34 + matrix->_33;
	m_planes[0]->d = matrix->_44 + matrix->_43;
	D3DXPlaneNormalize(m_planes[0], m_planes[0]);

	// Calculate far plane of frustum.
	m_planes[1]->a = matrix->_14 - matrix->_13;
	m_planes[1]->b = matrix->_24 - matrix->_23;
	m_planes[1]->c = matrix->_34 - matrix->_33;
	m_planes[1]->d = matrix->_44 - matrix->_43;
	D3DXPlaneNormalize(m_planes[1], m_planes[1]);

	// Calculate left plane of frustum.
	m_planes[2]->a = matrix->_14 + matrix->_11;
	m_planes[2]->b = matrix->_24 + matrix->_21;
	m_planes[2]->c = matrix->_34 + matrix->_31;
	m_planes[2]->d = matrix->_44 + matrix->_41;
	D3DXPlaneNormalize(m_planes[2], m_planes[2]);

	// Calculate right plane of frustum.
	m_planes[3]->a = matrix->_14 - matrix->_11;
	m_planes[3]->b = matrix->_24 - matrix->_21;
	m_planes[3]->c = matrix->_34 - matrix->_31;
	m_planes[3]->d = matrix->_44 - matrix->_41;
	D3DXPlaneNormalize(m_planes[3], m_planes[3]);

	// Calculate top plane of frustum.
	m_planes[4]->a = matrix->_14 - matrix->_12;
	m_planes[4]->b = matrix->_24 - matrix->_22;
	m_planes[4]->c = matrix->_34 - matrix->_32;
	m_planes[4]->d = matrix->_44 - matrix->_42;
	D3DXPlaneNormalize(m_planes[4], m_planes[4]);

	// Calculate bottom plane of frustum.
	m_planes[5]->a = matrix->_14 + matrix->_12;
	m_planes[5]->b = matrix->_24 + matrix->_22;
	m_planes[5]->c = matrix->_34 + matrix->_32;
	m_planes[5]->d = matrix->_44 + matrix->_42;
	D3DXPlaneNormalize(m_planes[5], m_planes[5]);
}

CollisionResult Frustum::CheckCollision(const AABB& aabb){
	CollisionResult result;
	int resultCont = 0;
	int totalResult = 0;
	for (int i = 0; i < 6; i++){
		if (D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMin, aabb.ActualzMin)) >= 0.0f)
		{
			resultCont++;
		}
		if (D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMax, aabb.ActualzMax)) >= 0.0f)
		{
			resultCont++;
		}
		if(D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMin, aabb.ActualzMax)) >= 0.0f)
		{
			resultCont++;
		}
		if(D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMax, aabb.ActualzMin)) >= 0.0f)
		{
			resultCont++;
		}
		if(D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMax, aabb.ActualyMin, aabb.ActualzMin)) >= 0.0f)
		{
			resultCont++;
		}
		if(D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMin, aabb.ActualzMax)) >= 0.0f)
		{
			resultCont++;
		}
		if(D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMax, aabb.ActualzMax)) >= 0.0f)
		{
			resultCont++;
		}
		if(D3DXPlaneDotCoord(m_planes[i], &D3DXVECTOR3(aabb.ActualxMin, aabb.ActualyMax, aabb.ActualzMin)) >= 0.0f)
		{
			resultCont++;
		}
		if (resultCont == 8)
		{
			totalResult++;
			resultCont = 0;
		}
	}

	if (totalResult == 6)
	{		
		return AllInside;
	}
	else //if (totalResult == 0)
	{
		return AllOutside;
	}
	/*else
	{
		return PartiallyInside;
	}*/
	
    
}