#include "Importador.h"

#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"
#pragma comment (lib, "assimp.lib")

Importador::Importador(){}

bool Importador::ImportMesh(std::string fileName, Mesh& _mesh){
	Assimp::Importer Importer;
	fileName = "Assets\\" + fileName;
	const aiScene* pScene = Importer.ReadFile(fileName, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	//aiProcess_CalcTangentSpace |aiProcess_Triangulate |	aiProcess_JoinIdenticalVertices |	aiProcess_SortByPType

	CustomVertex* vertices = new CustomVertex[pScene->mMeshes[0]->mNumVertices];
	const aiMesh* mesh = pScene->mMeshes[0];

	for (int v_i = 0; v_i < mesh->mNumVertices; v_i++)
		{			
				CustomVertex* vertice = new CustomVertex();
				vertice->x = mesh->mVertices[v_i].x;
				vertice->y = mesh->mVertices[v_i].y;
				vertice->z = mesh->mVertices[v_i].z;
				vertice->color = D3DCOLOR_XRGB(50, 50, 50);
				vertices[v_i] = *vertice;
	}

	// create index array
	size_t uiIndexCount = mesh->mNumFaces * 3;
	unsigned short* pausIndices = new unsigned short[uiIndexCount];
	for (unsigned int i = 0; i<mesh->mNumFaces; i++)
	{
		pausIndices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
		pausIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
		pausIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
	}

	_mesh.setMeshData(vertices, Primitive::TriangleList, mesh->mNumVertices, pausIndices, uiIndexCount);
	return true;
}
