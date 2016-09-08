#ifndef PG2_INDEXBUFFER_H
#define PG2_INDEXBUFFER_H
//---------------------------------------------------------------------------
#include <cassert>
#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3d9.h"
#include "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include/d3dx9.h"
//---------------------------------------------------------------------------
class Renderer;
//---------------------------------------------------------------------------
class IndexBuffer
{
public:
	IndexBuffer (Renderer& rkRenderer, IDirect3DDevice9* pkDevice);
	~IndexBuffer ();

	void bind ();
	void setIndexData (const unsigned short* pausIndices, size_t uiIndexCount);
	
	size_t indexCount () const;

private:
	size_t m_uiIndexCount;

	D3DPRIMITIVETYPE m_ePrimitiveType;
	LPDIRECT3DINDEXBUFFER9 m_IndexBuffer;
	IDirect3DDevice9* m_pkDevice;
	Renderer& m_rkRenderer;
};
//---------------------------------------------------------------------------
#include "pg2_indexbuffer.inl"
//---------------------------------------------------------------------------
#endif  // PG2_INDEXBUFFER_H
//---------------------------------------------------------------------------
