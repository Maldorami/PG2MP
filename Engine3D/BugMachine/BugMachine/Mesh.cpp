#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"

Mesh::Mesh(Renderer& rkRenderer)
:
indexB(NULL),
vertexB(NULL),
rendi(rkRenderer)
{}

void Mesh::setMeshData(const CustomVertex* pakVertices, Primitive ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices,
	size_t uiIndexCount)
{
	vertexB = rendi.createVertexBuffer(sizeof(CustomVertex), CUSTOMFVF);
	indexB = rendi.createIndexBuffer();

	vertexB->setVertexData(pakVertices, uiVertexCount);
	indexB->setIndexData(pusIndices, uiIndexCount);

	rendi.setCurrentVertexBuffer(vertexB);
	rendi.setCurrentIndexBuffer(indexB);

	primitive = ePrimitive;
}

void Mesh::setMeshData(const CustomVertexZ* pakVertices, Primitive ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices,
	size_t uiIndexCount)
{
	vertexB = rendi.createVertexBuffer(sizeof(CustomVertexZ), CUSTOMFVFT);
	indexB = rendi.createIndexBuffer();

	vertexB->setVertexData(pakVertices, uiVertexCount);
	indexB->setIndexData(pusIndices, uiIndexCount);

	rendi.setCurrentVertexBuffer(vertexB);
	rendi.setCurrentIndexBuffer(indexB);

	primitive = ePrimitive;
}

void Mesh::draw(){
	rendi.setCurrentTexture(_texture);
	rendi.setMatrix(MatrixType::World, _transformationMatrix);
	rendi.drawCurrentBuffers(primitive);
}

void Mesh::setTextureId(Texture texturrah){
	_texture = texturrah;
}

Mesh::~Mesh(){
	delete indexB;
	delete vertexB;

	indexB = NULL;
	vertexB = NULL;
}