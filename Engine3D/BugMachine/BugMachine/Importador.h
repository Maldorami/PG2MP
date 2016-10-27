#ifndef IMPORTADOR_H
#define IMPORTADOR_H
#include "Node.h"
#include <vector>

#define DLLexport __declspec(dllexport)
class DLLexport Importador{
public:
	Importador(Renderer& rkRenderer);
	bool importScene(std::string rkFilename, Node& orkSceneRoot);
	Renderer rendi;

};
#endif IMPORTADOR_H
