#include "Mesh.h"
#include "pg2_indexbuffer.h"
#include "pg2_vertexbuffer.h"
#include <iostream>

Mesh::Mesh(Renderer& rkRenderer)
:
indexB(NULL),
vertexB(NULL),
rendi(rkRenderer)
{}
using namespace std;

void Mesh::updateBV(){

	BV.pivot.x = posX();
	BV.pivot.y = posY();
	BV.pivot.z = posZ();

	BV.ActualxMax = (BV.xMax) * scaleX();
	BV.ActualxMin = (BV.xMin) * scaleX();

	BV.ActualyMax = (BV.yMax) * scaleY();
	BV.ActualyMin = (BV.yMin) * scaleY();

	BV.ActualzMax = (BV.zMax) * scaleY();
	BV.ActualzMin = (BV.zMin) * scaleY();

	BV.width = BV.ActualxMax - BV.ActualxMin;
	BV.height = BV.ActualyMax - BV.ActualyMin;
	BV.depth = BV.ActualzMax - BV.ActualzMin;

	if (drawBV){
		cout << "Nombre: " << getName() << endl;
		cout << "xMin: " << BV.ActualxMin << " | xMax: " << BV.ActualxMax << endl;
		cout << "yMin: " << BV.ActualyMin << " | yMax: " << BV.ActualyMax << endl;
		cout << "zMin: " << BV.ActualzMin << " | zMax: " << BV.ActualzMax << endl;
		cout << "Pivot x: " << BV.pivot.x << " - y: " << BV.pivot.y << " - z: " << BV.pivot.z;
		cout << endl << "Height: " << BV.height << " - Width: " << BV.width << " - Depth: " << BV.depth;
		cout << endl << "-----------------------------------------------------------" << endl;
		drawBV = false;
	}
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

void Mesh::draw(){
	rendi.setCurrentTexture(_texture);
	rendi.setMatrix(MatrixType::World, _WordtransformationMatrix);
	rendi.drawCurrentBuffers(primitive);
	updateBV();
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