#ifndef PG1_VERTEXBUFFER_H
#define PG1_VERTEXBUFFER_H

#include <d3d9.h>
#include <cassert>

//---------------------------------------------------------------------------
class Renderer;
//---------------------------------------------------------------------------

class VertexBuffer
{
public:
	VertexBuffer(IDirect3DDevice9* pkDevice, unsigned int uiVertexSize, unsigned int uiFVF);
	~VertexBuffer ();

	bool create ();
	void bind ();
	void flush ();
	void draw (const void* pvVertices, D3DPRIMITIVETYPE ePrimitiveType, unsigned int uiVertexCount);
	void release ();

private:

	// Tama�o de Vertex Buffer
	static const unsigned int SIZE = 400;
	static const unsigned int FLUSH_COUNT = 200;

	unsigned int m_uiBase;
	unsigned int m_uiVertexToLock;
	unsigned int m_uiVertexSize;
	unsigned int m_uiFVF;

	D3DPRIMITIVETYPE m_ePrimitiveType;
	LPDIRECT3DVERTEXBUFFER9 m_pkVertexBuffer;
	IDirect3DDevice9 * m_pkDevice;
};
//---------------------------------------------------------------------------
#endif
