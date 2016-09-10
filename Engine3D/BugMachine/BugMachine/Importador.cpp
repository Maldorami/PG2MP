#include "Importador.h"

#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"
#pragma comment (lib, "assimp.lib")

Importador::Importador(){}

bool Importador::ImportMesh(std::string fileName, Mesh& mesh){
	Assimp::Importer Importer;
	fileName = "Assets\\" + fileName;
	const aiScene* pScene = Importer.ReadFile(fileName, aiProcess_SortByPType | aiProcess_Triangulate);
	aiMesh* mesh1;
	mesh1 = pScene->mMeshes[0];
	const int size = mesh1->mNumVertices;

	CustomVertex* vertices = new CustomVertex[mesh1->mNumVertices];

	for (int i = 0; i < mesh1->mNumVertices; i++){
		CustomVertex* vertice = new CustomVertex();

		vertice->x = mesh1->mVertices[i].x;
		vertice->y = mesh1->mVertices[i].y;
		vertice->z = mesh1->mVertices[i].z;

		vertice->color = D3DCOLOR_XRGB(50, 50, 50);

		vertices[i] = *vertice;
	}

	mesh.setMeshData(vertices, Primitive::TriangleList,mesh1->mNumVertices, (unsigned short*)mesh1->mFaces->mIndices, mesh1->mFaces->mNumIndices);
	return true;
}
