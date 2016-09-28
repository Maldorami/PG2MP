#ifndef NODE_H
#define NODE_H

#include "Entity3D.h"
#include <vector>

class Node : public Entity3D{
public:
	DLLexport Node();
	DLLexport void AddChild(Entity3D* child);
	DLLexport void setParent(Node& parent);
	DLLexport void draw();

private:
	std::vector<Entity3D*> _childs;
};


#endif