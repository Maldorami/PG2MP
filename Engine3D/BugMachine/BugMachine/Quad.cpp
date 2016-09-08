#include "Quad.h"
#include "Renderer.h"
//---------------------------------------------------------------------------
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")
//---------------------------------------------------------------------------
Quad::Quad()
:
Entity2D(),
m_vertices(new CustomVertex[4])
{
	m_vertices[0].x = -0.5;	m_vertices[0].y = 0.5;	m_vertices[0].z = 0.0f;
	m_vertices[1].x = 0.5;	m_vertices[1].y = 0.5;	m_vertices[1].z = 0.0f;
	m_vertices[2].x = -0.5;	m_vertices[2].y = -0.5;	m_vertices[2].z = 0.0f;
	m_vertices[3].x = 0.5;	m_vertices[3].y = -0.5;	m_vertices[3].z = 0.0f;

	m_vertices[0].color = D3DCOLOR_XRGB(0, 255, 255);
	m_vertices[1].color = D3DCOLOR_XRGB(0, 255, 255);
	m_vertices[2].color = D3DCOLOR_XRGB(0, 255, 255);
	m_vertices[3].color = D3DCOLOR_XRGB(0, 255, 255);
}
//---------------------------------------------------------------------------
Quad::~Quad()
{
	delete[] m_vertices;
	m_vertices = NULL;
}
//---------------------------------------------------------------------------
void Quad::draw(Renderer& rendi) const
{
	rendi.setCurrentTexture(NoTexture);
	rendi.setMatrix(World, _transformationMatrix);
	rendi.draw(m_vertices, D3DPT_TRIANGLESTRIP, 4);
}
//---------------------------------------------------------------------------