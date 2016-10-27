#include "Importador.h"
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"
#include "Mesh.h"
#include <stack>
#include <typeinfo>

using namespace std;

#pragma comment (lib, "assimp.lib")
void getChild(aiNode& node, const aiScene& scene, Node& orkSceneRoot,Renderer& rendi);
void reemparenting(Node& root);

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

	//reemparenting(orkSceneRoot);

	return true;
}

void reemparenting(Node& root){
	for (unsigned int i = 0; i < root._childs.size(); i++){
		if (root._childs.size() == 1){
			if (root._parent != NULL){

				string type = typeid(*root._childs[i]).name();
				if (type == "class Node"){
					Node* node = new Node();
					node = (Node*)root._childs[i];

					root._childs[0]->setParent(*root._parent);
					root._parent->removeChild(&root);

					reemparenting(*node);

					delete &root;
				}

				root._childs[0]->setParent(*root._parent);
				root._parent->removeChild(&root);
				delete &root;
			}
		}
		else{
			string type = typeid(*root._childs[i]).name();
			if (type == "class Node"){
				Node* node = new Node();
				node = (Node*)root._childs[i];
				reemparenting(*node);
			}
		}
	}
}

void getChild(aiNode& node, const aiScene& scene, Node& orkSceneRoot, Renderer& rendi){
	for (unsigned int i = 0; i < node.mNumMeshes; i++)
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
			vertice->v = -mesh->mTextureCoords[0][i].y;

			verticesT[i] = *vertice;
		}
		Mesh* _mesh = new Mesh(rendi);

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
			for (unsigned int x = 0; x < sizeStackFinal; x++){
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
				orkSceneRoot.AddChild(_node);

				/*aiVector3t<float> scale;
				aiQuaterniont<float> rotation;
				aiVector3t<float> position;
				node.mTransformation.Decompose(scale, rotation, position);
				_node->setScale(scale.x, scale.y, scale.z);
				_node->setRotation(rotation.x, rotation.y, rotation.z);
				_node->setPos(position.x, position.y, position.z);*/

				getChild(*node.mChildren[i],scene,*_node,rendi);
			}
		}
}

