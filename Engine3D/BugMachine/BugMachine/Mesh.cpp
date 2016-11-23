#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"
#include <iostream>

#include <d3d9.h>
#pragma comment (lib, "d3d9.lib")

#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

Mesh::Mesh(Renderer& rkRenderer)
:
indexB(NULL),
vertexB(NULL),
rendi(rkRenderer)
{}
using namespace std;

void Mesh::updateBV(){

	D3DXVECTOR3* wordScale = new D3DXVECTOR3();
	D3DXQUATERNION* wordRotation = new D3DXQUATERNION();
	D3DXVECTOR3* wordTranslation = new D3DXVECTOR3();

	Matrix wordTransf = new D3DXMATRIX();
	wordTransf = _WordtransformationMatrix;

	D3DXMatrixDecompose(wordScale, wordRotation, wordTranslation, wordTransf);

	BV.pivot.x = posX();
	BV.pivot.y = posY();
	BV.pivot.z = posZ();
	
	BV.ActualxMax = (BV.xMax + wordTranslation->x) * wordScale->x;
	BV.ActualxMin = (BV.xMin + wordTranslation->x) * wordScale->x;

	BV.ActualyMax = (BV.yMax + wordTranslation->y) * wordScale->y;
	BV.ActualyMin = (BV.yMin + wordTranslation->y) * wordScale->y;

	BV.ActualzMax = (BV.zMax + wordTranslation->z) * wordScale->z;
	BV.ActualzMin = (BV.zMin + wordTranslation->z) * wordScale->z;

	BV.width = BV.ActualxMax - BV.ActualxMin;
	BV.height = BV.ActualyMax - BV.ActualyMin;
	BV.depth = BV.ActualzMax - BV.ActualzMin;
}


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

void Mesh::draw(Renderer& rkRenderer, CollisionResult eParentResult, Frustum& rkFrustum){
	if (eParentResult != AllOutside)
	{
		rendi.setCurrentTexture(_texture);
		rendi.setMatrix(MatrixType::World, _WordtransformationMatrix);
		rendi.drawCurrentBuffers(primitive);
	}
}

void Mesh::draw(Renderer& rkRenderer, CollisionResult eParentResult, Frustum& rkFrustum, Text& _text){

	if (eParentResult != AllOutside)
	{
		rendi.setCurrentTexture(_texture);
		rendi.setMatrix(MatrixType::World, _WordtransformationMatrix);
		rendi.drawCurrentBuffers(primitive);

		_text.setText(_text._text + "\n   " + getName());
	}
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