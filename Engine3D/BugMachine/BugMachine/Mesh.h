#ifndef MESH_H
#define MESH_H
#include "Renderer.h"
#include "Entity2D.h"

#define DLLexport __declspec(dllexport)
class DLLexport Mesh : public Entity2D{

	// constructor
public:
	Mesh(Renderer& rkRenderer);
	~Mesh();

	// rendering
	void setMeshData(const CustomVertex* pakVertices, Primitive ePrimitive,
					size_t uiVertexCount, const unsigned short* pusIndices,
					size_t uiIndexCount);
	void draw();
	void setTextureId(int iTextureId);

private:
	IndexBuffer* indexB;
	VertexBuffer* vertexB;
	Renderer rendi;
	Primitive primitive;
};
#endif