#ifndef IMPORTADOR_H
#define IMPORTADOR_H

#include "Mesh.h"
#include <vector>

#define DLLexport __declspec(dllexport)
class DLLexport Importador{
public:
	Importador();
	bool importScene(std::string& rkFilename, Node& orkSceneRoot);
};
#endif IMPORTADOR_H
