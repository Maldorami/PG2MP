#ifndef IMPORTADOR_H
#define IMPORTADOR_H
#include "Mesh.h"
#define DLLexport __declspec(dllexport)
class DLLexport Importador{
public:
	Importador();
	bool ImportMesh(std::string fileName,Mesh& mesh);
};
#endif IMPORTADOR_H
