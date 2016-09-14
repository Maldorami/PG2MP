#ifndef MESH_H
#define MESH_H
#include "Renderer.h"
#include "Entity3D.h"

#define DLLexport __declspec(dllexport)
class Mesh : public Entity3D{

	// constructor
public:
	DLLexport Mesh(Renderer& rkRenderer);
	DLLexport ~Mesh();

	// rendering
	DLLexport void setMeshData(const CustomVertex* pakVertices, Primitive ePrimitive,
					size_t uiVertexCount, const unsigned short* pusIndices,
					size_t uiIndexCount);
	DLLexport void draw();
	DLLexport void setTextureId(int iTextureId);

private:
	IndexBuffer* indexB;
	VertexBuffer* vertexB;
	Renderer rendi;
	Primitive primitive;
};
#endif