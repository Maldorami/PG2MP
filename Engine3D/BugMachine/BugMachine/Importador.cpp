#include "Importador.h"
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"
#include <stack>
#include <typeinfo>

using namespace std;

#pragma comment (lib, "assimp.lib")
void getChild(aiNode& node, const aiScene& scene, Node& orkSceneRoot,Renderer& rendi);

Importador::Importador(Renderer& rkRenderer)
:
rendi(rkRenderer)
{}

bool Importador::importScene(std::string fileName, Node& orkSceneRoot){
	Assimp::Importer Importer;
	fileName = "Assets\\" + fileName;
	const aiScene* pScene = Importer.ReadFile(fileName, aiProcess_Triangulate);
	// aiProcess_CalcTangentSpace |aiProcess_Triangulate |	aiProcess_JoinIdenticalVertices |	aiProcess_SortByPType

	getChild(*pScene->mRootNode, *pScene, orkSceneRoot, rendi);
	return true;
}

void getChild(aiNode& node, const aiScene& scene, Node& orkSceneRoot, Renderer& rendi){
	for (unsigned int i = 0; i < node.mNumMeshes; i++){
		const aiMesh* mesh = scene.mMeshes[node.mMeshes[i]];

		unsigned short* indices = new unsigned short[mesh->mNumFaces * 3];
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			indices[i * 3 + 0] = mesh->mFaces[i].mIndices[0];
			indices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
			indices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
		}

		////AABB Values
		float xMin = 0, xMax = 0;
		float yMin = 0, yMax = 0;
		float zMin = 0, zMax = 0;
		CustomVertexZ* verticesT = new CustomVertexZ[mesh->mNumVertices];
		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			verticesT[i].x = mesh->mVertices[i].x;
			if (mesh->mVertices[i].x < xMin)
				xMin = mesh->mVertices[i].x;
			if (mesh->mVertices[i].x > xMax)
				xMax = mesh->mVertices[i].x;

			verticesT[i].y = mesh->mVertices[i].y;
			if (mesh->mVertices[i].y < yMin)
				yMin = mesh->mVertices[i].y;
			if (mesh->mVertices[i].y > yMax)
				yMax = mesh->mVertices[i].y;

			verticesT[i].z = mesh->mVertices[i].z;
			if (mesh->mVertices[i].z < zMin)
				zMin = mesh->mVertices[i].z;
			if (mesh->mVertices[i].z > zMax)
				zMax = mesh->mVertices[i].z;

			verticesT[i].u = mesh->mTextureCoords[0][i].x;
			verticesT[i].v = -mesh->mTextureCoords[0][i].y;
		}

		Mesh* _mesh = new Mesh(rendi);
		_mesh->setName(node.mName.C_Str());

		_mesh->BV.pivot.x = xMax - ((xMax - xMin) / 2);
		_mesh->BV.pivot.y = yMax - ((yMax - yMin) / 2);
		_mesh->BV.pivot.z = zMax - ((zMax - zMin) / 2);
		_mesh->BV.width = xMax - xMin;
		_mesh->BV.height = yMax - yMin;
		_mesh->BV.depth = zMax - zMin;
		_mesh->BV.xMax = xMax;
		_mesh->BV.xMin = xMin;
		_mesh->BV.yMax = yMax;
		_mesh->BV.yMin = yMin;
		_mesh->BV.zMax = zMax;
		_mesh->BV.zMin = zMin;

		aiVector3t<float> scale;
		aiQuaterniont<float> rotation;
		aiVector3t<float> position;
		node.mTransformation.Decompose(scale, rotation, position);
		_mesh->setScale(scale.x, scale.y, scale.z);
		_mesh->setRotation(rotation.x, rotation.y, rotation.z);
		_mesh->setPos(position.x, position.y, position.z);

		aiString path;
		if (scene.mMaterials[mesh->mMaterialIndex]->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS){

			string pathName = path.data;
			char tmp = ' ';
			bool ready = false;
			stack<char> stackFinal;

			for (unsigned int i = pathName.size(); i != -1; i--){
				tmp = pathName[i];

				if (tmp == '/') ready = true;
				
				if (!ready){
					stackFinal.push(tmp);
				}
			}

			string pathFinal = "Assets\\";
			int sizeStackFinal = stackFinal.size();
			for (int x = 0; x < sizeStackFinal; x++){
				pathFinal += stackFinal.top();
				stackFinal.pop();
			}
			_mesh->setTextureId(rendi.loadTexture(pathFinal, D3DCOLOR_XRGB(255, 0, 255)));
		}

		_mesh->setMeshData(verticesT, Primitive::TriangleList, mesh->mNumVertices, indices, mesh->mNumFaces * 3);
		orkSceneRoot.AddChild(_mesh);
		}

		if (node.mNumChildren > 0)
		{
				for (unsigned int i = 0; i < node.mNumChildren; i++)
				{
					Node* _node = new Node();

					aiVector3t<float> scale;
					aiQuaterniont<float> rotation;
					aiVector3t<float> position;
					node.mTransformation.Decompose(scale, rotation, position);
					_node->setScale(scale.x, scale.y, scale.z);
					_node->setRotation(rotation.x, rotation.y, rotation.z);
					_node->setPos(position.x, position.y, position.z);

					_node->setName(node.mName.C_Str());
					orkSceneRoot.AddChild(_node);
					getChild(*node.mChildren[i], scene, *_node, rendi);
				}
		}
}
