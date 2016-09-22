#include "Importador.h"

#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"
#pragma comment (lib, "assimp.lib")

Importador::Importador(){}

bool Importador::ImportMesh(std::string fileName, Mesh& _mesh){
	Assimp::Importer Importer;
	fileName = "Assets\\" + fileName;
	const aiScene* pScene = Importer.ReadFile(fileName, aiProcess_Triangulate);
	// aiProcess_CalcTangentSpace |aiProcess_Triangulate |	aiProcess_JoinIdenticalVertices |	aiProcess_SortByPType
	const aiMesh* mesh = pScene->mMeshes[0];

	CustomVertex* vertices = new CustomVertex[pScene->mMeshes[0]->mNumVertices];
	for (unsigned v_i = 0; v_i < mesh->mNumVertices; v_i++)
		{			
				CustomVertex* vertice = new CustomVertex();
				vertice->x = mesh->mVertices[v_i].x;
				vertice->y = mesh->mVertices[v_i].y;
				vertice->z = mesh->mVertices[v_i].z;
				vertice->color = D3DCOLOR_XRGB(50, 50, 50);
				vertices[v_i] = *vertice;
	}

	unsigned short* indices = new unsigned short[mesh->mNumFaces * 3];
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
		indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
		indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
	}
	_mesh.setMeshData(vertices, Primitive::TriangleList, mesh->mNumVertices, indices, mesh->mNumFaces * 3);
	return true;
}
