#include "Frustum.h"
//---------------------------------------------------------------------------
#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

Frustum::Frustum(Renderer& rkRenderer) 
:
rendi(rkRenderer)
{}

Frustum::~Frustum(){}		

void Frustum::ConstructFrustum(float screenDepth, Matrix& projectionMatrix, Matrix& viewMatrix){
	float zMinimum;
	float r;
	Matrix matrix = new D3DXMATRIX();
	
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