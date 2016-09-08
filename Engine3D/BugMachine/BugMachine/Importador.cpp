#include "Importador.h"
#include "../include/assimp/Importer.hpp"
#include "../include/assimp/scene.h"
#include "../include/assimp/postprocess.h"

Importador::Importador(){}

bool Importador::ImportMesh(std::string fileName, Mesh& mesh){
	Assimp::Importer Importer;
	aiMesh* mesh1;
	const aiScene* pScene = Importer.ReadFile(fileName.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
	mesh1 = pScene->mMeshes[0];
	const int size = mesh1->mNumVertices;

	CustomVertex* vertices = new CustomVertex[mesh1->mNumVertices];
	for (int i = 0; i < mesh1->mNumVertices; i++){
		CustomVertex* vertice = new CustomVertex();
		vertice[i].x = mesh1->mVertices[i].x;
		vertice[i].y = mesh1->mVertices[i].y;
		vertice[i].z = mesh1->mVertices[i].z;
		
		vertices[i] = *vertice;
	}
	mesh.setMeshData(vertices, Primitive::TriangleList,mesh1->mNumVertices, (unsigned short*)mesh1->mFaces->mIndices, mesh1->mFaces->mNumIndices);
	return true;
}
