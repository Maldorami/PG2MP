#ifndef MESH_H
#define MESH_H

#include "Entity3D.h"

class Mesh : public Entity3D{

	// constructor
public:
	DLLexport Mesh(Renderer& rkRenderer);
	DLLexport ~Mesh();

	// rendering
	DLLexport void setMeshData(const CustomVertex* pakVertices, Primitive ePrimitive,
					size_t uiVertexCount, const unsigned short* pusIndices,
					size_t uiIndexCount);

	DLLexport void setMeshData(const CustomVertexZ* pakVertices, Primitive ePrimitive,
		size_t uiVertexCount, const unsigned short* pusIndices,
		size_t uiIndexCount);

	DLLexport void draw();
	DLLexport void setTextureId(Texture _texture);

private:
	IndexBuffer* indexB;
	VertexBuffer* vertexB;
	Renderer rendi;
	Primitive primitive;
	Texture _texture;
};
#endif