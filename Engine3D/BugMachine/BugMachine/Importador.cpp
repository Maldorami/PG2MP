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

	unsigned short* indices = new unsigned short[mesh->mNumFaces * 3];
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
		indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
		indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
	}

	CustomVertexZ* verticesT = new CustomVertexZ[mesh->mNumVertices];
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
			CustomVertexZ* vertice = new CustomVertexZ();
			vertice->x = mesh->mVertices[i].x;
			vertice->y = mesh->mVertices[i].y;
			vertice->z = mesh->mVertices[i].z;
			vertice->u = mesh->mTextureCoords[0][i].x;
			vertice->v = mesh->mTextureCoords[0][i].y;

			verticesT[i] = *vertice;						
	}

	_mesh.setMeshData(verticesT, Primitive::TriangleList, mesh->mNumVertices, indices, mesh->mNumFaces * 3);
	return true;
}
