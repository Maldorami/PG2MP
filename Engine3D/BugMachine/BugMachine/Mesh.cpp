#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"

Mesh::Mesh(Renderer& rkRenderer)
:
indexB(NULL),
vertexB(NULL),
rendi(rkRenderer)
{}

Mesh::~Mesh(){

}

void Mesh::setMeshData(const CustomVertex* pakVertices, Primitive ePrimitive,
	size_t uiVertexCount, const unsigned short* pusIndices,
	size_t uiIndexCount)
{

	vertexB = rendi.createVertexBuffer(sizeof(CustomVertex), CUSTOMFVF);
	indexB = rendi.createIndexBuffer();

	vertexB->setVertexData(pakVertices, uiVertexCount);
	indexB->setIndexData(pusIndices, uiIndexCount);

	rendi.setCurrentIndexBuffer(indexB);
	rendi.setCurrentVertexBuffer(vertexB);

	primitive = ePrimitive;
}
void Mesh::draw(){
	rendi.setMatrix(MatrixType::World, _transformationMatrix);
	rendi.drawCurrentBuffers(primitive);
}
void Mesh::setTextureId(int iTextureId){

}