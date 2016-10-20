#include "Importador.h"
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"
#include "Node.h"
#pragma comment (lib, "assimp.lib")

Importador::Importador(){}

bool Importador::importScene(std::string& fileName, Node& orkSceneRoot){
	Assimp::Importer Importer;
	fileName = "Assets\\" + fileName;
	const aiScene* pScene = Importer.ReadFile(fileName, aiProcess_Triangulate);
	// aiProcess_CalcTangentSpace |aiProcess_Triangulate |	aiProcess_JoinIdenticalVertices |	aiProcess_SortByPType
	for (int i = 0; i < pScene->mRootNode->mNumChildren; i++)
	{	
		getChild(*pScene->mRootNode->mChildren[i], *pScene);
	}
	return true;
}

void getChild( aiNode& node, const aiScene& scene){
	for (int i = 0; i < node.mNumMeshes; i++)
	{
		const aiMesh* mesh = scene.mMeshes[node.mMeshes[i]];

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
		//preguntar si tiene children y llamar la recursividad
		/*Mesh _mesh ;
		_mesh.setMeshData(verticesT, Primitive::TriangleList, mesh->mNumVertices, indices, mesh->mNumFaces * 3);*/
	}
}

